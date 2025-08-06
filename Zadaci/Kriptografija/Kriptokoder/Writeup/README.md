# Writeup

U priloženoj zip arhivi se nalaze tri datoteke:

- cypher.txt
- key.txt
- kriptokoder.py

Datoteka ```cypher.txt``` sadrži poruku koja je kriptirana:

```
[==]0=-+|=!^_0oI°_|$+'I$I-+$0[_oo[$__|o+$+0]?+_+!'^-+^I_|]o_o+
```

Datoteka ```key.txt``` sadrži ključ koji se koristio prilikom kriptiranja poruke:
```
vaf5g-AZTFz65th/?.%

```



Datoteka ```kriptokoder.py``` sadrži algoritam pomoću kojeg se poruka kriptirala:

```python
import sys

def r(b):
    right = b >> 3
    left  = (b & ((1 << 3) - 1)) << 5
    return right | left

def enc(m, key):
    i = 0
    c = []
    Z = "![_°^?'I|o0]$+=-"
    for byte in m:
        temp = r(byte)
        temp =  temp ^ key[i % len(key)]
        i = i + 1
        h = (temp >> 4) & 0xF
        c.append(Z[h])
        l = temp & 0xF
        c.append(Z[l])
    return "".join(c)

if len(sys.argv) != 3:
    sys.exit(1)

m = sys.argv[1].encode("utf-8")
key = sys.argv[2].encode("utf-8")
c = enc(m, key)
print(c)
```

Cilj je izraditi program koji će dešifrirati kriptiranu poruku.
Da bi to bilo moguće, prvo se mora dobro razumjeti postupak šifriranja poruke.

Prvo se dohvate vrijednosti iz argumenta programa i zatim se poziva funkcija za kriptiranje:
```python
m = sys.argv[1].encode("utf-8")
key = sys.argv[2].encode("utf-8")
c = enc(m, key)
```

Na početku funkcije za kriptiranje se pripremaju neke varijable:
```python
def enc(m, key):
    i = 0
    c = []
    Z = "![_°^?'I|o0]$+=-"
```

Izgleda da se ovdje koristi hardkodirani string koji sadrži znakove kriptirane poruke.


Zatim slijedi petlja koja prolazi kroz svaki bajt poruke i kriptira ju:

```python
for byte in m:
        #1. korak
        temp = r(byte)

        #2. korak
        temp =  temp ^ key[i % len(key)] 
        i = i + 1

        #3. korak
        h = (temp >> 4) & 0xF 
        c.append(Z[h])
        l = temp & 0xF
        c.append(Z[l])
```

Kriptiranje se odvija u tri koraka.
Prvi korak je rotacija bitova unutar svakog bajta poruke za 3 bita udesno:

```python
temp = r(byte)
...
def r(b):
    right = b >> 3
    left  = (b & ((1 << 3) - 1)) << 5
    return right | left
```

To znači da će npr. bajt ```0100 1110``` postati ```1100 1001```.

U drugom koraku se radi jednostavan XOR svakog bajta s bajtom ključa (ako je ključ pre malen, tada se ponovo kreće od početka ključa):
```python
temp =  temp ^ key[i % len(key)]
```

U zadnjem koraku se od gledanog bajta uzima prva i druga polovica bajta. 
Radi se mapiranje prema vrijednostima polovica bajta. 
Vrijednosti za mapiranje se uzimaju iz hardkodiranog stringa ```Z```:

```python
Z = "![_°^?'I|o0]$+=-"
...
h = (temp >> 4) & 0xF 
c.append(Z[h])
l = temp & 0xF
c.append(Z[l])
```

<hr>

Sada kada je jasno kako radi algoritam za šifriranje može se napraviti algoritam za dešifriranje:

```python
def shift_inv(b):
    left  = (b << 3) & 0xFF
    right = (b >> 5) & 0x07
    return left | right

def decrypt(cipher, key):
    Z = "![_°^?'I|o0]$+=-"
    zmap = {ch: i for i,ch in enumerate(Z)}
    key_bytes = key.encode("utf-8")
    key_len = len(key_bytes)
    m = bytearray()
    
    for i in range(0, len(cipher), 2):

        #3. korak
        h = zmap[cipher[i]]
        l = zmap[cipher[i+1]]
        temp = (h << 4) | l

        #2. korak
        k_byte = key_bytes[(i//2) % key_len]
        temp2 = temp ^ k_byte

        #1. korak
        original = shift_inv(temp2)
        m.append(original)

    return m.decode('utf-8', errors='replace')

c = "[==]0=-+|=!^_0oI°_|$+'I$I-+$0[_oo[$__|o+$+0]?+_+!'^-+^I_|]o_o+"
key = "vaf5g-AZTFz65th/?.%"
m = decrypt(c, key)
print(m)

```

Flag je: ```CTFFOI[n3VeRREN0ugh_enCRYpt1nG]```.

## Edukativne smjernice
- Ne preporuča se implementacija vlastitih algoritma za šifriranje poruka jer oni često mogu sadržavati mnogo ranjivosti. Bolje je koristiti poznate i sigurne algoritme poput RSA.
- Sigurnost kriptirane poruke temelji se na sigurnosti ključa (Kerchoff princip). Važno je da ključ koji se koristio u šifriranju ostane tajan.
  
