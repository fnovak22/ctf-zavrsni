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
Da bi to bilo moguće, prvo se mora dobro razumijeti postupak šifriranja poruke.

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
def r(b):
    right = b >> 3
    left  = (b & ((1 << 3) - 1)) << 5
    return right | left
```

To znači da će npr. bajt ```0100 1110``` postati ```1100 1001```.

U drugom koraku se radi jednostavan XOR svakog bajta s bajtom ključa (ukoliko je ključ pre malen, tada se ponovo kreće od početka ključa):
```python
temp =  temp ^ key[i % len(key)]
```

U zadnjem koraku

```python
h = (temp >> 4) & 0xF 
        c.append(Z[h])
        l = temp & 0xF
        c.append(Z[l])
```

Flag je: ```CTFFOI[n3VeRREN0ugh_enCRYpt1nG]```.
