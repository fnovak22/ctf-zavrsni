# Writeup
Zadatak se sastoji od jednog python programa koji očekuje korisnički ulaz kao naziv i vrijednost varijable.

S obzirom na ograničenu veličinu korisničkog ulaza, može se probati izraditi _bruteforce_ na sve moguće kombinacije brojeva:

```
import subprocess

def rjesiMisiju(prvi_input,drugi_input):
    ulaz = f"{prvi_input}\n{drugi_input}\n"
    rezultat = subprocess.run(
        ["python3", "misija.py"],
        input= ulaz,
        capture_output=True,
        text=True
    )
    output = rezultat.stdout.strip()
    return output

for broj in range(100000):
    output = rjesiMisiju("b",str(broj))
    print(f"Ulaz: {str(broj)} --> Izlaz: {output}")
    if "ERROR" not in output:
            print(f"Uspjeh: {str(broj)}")
            break
else:
    print("Nije pronaden ispravni broj!")

```

Ovaj pokušaj nije dao rješenje.
Najveći problem je ovaj uvjet:

```
if(eval(f"(({ime}*20) != (a * (-2 + (4 * 3) + 10 )))")):
        print("ERROR - Krivo 3")
        return False
```

Kada se on skrati, postane vrlo jednostavan:

```
if(eval(f"( {ime} != a)")):
        print("ERROR - Krivo 3")
        return False
```

To znači da vrijednost korisničke varijable i varijable ```a``` mora biti jednaka.
Trenutno je vrijednost varijable ```a``` postavljeno na početku programa na ```2```.
Ne postoji drugi dio programa koji mijenja vrijednost varijable ```a```.

Detaljnijim pregledom kod programa, može se uočiti jedan sumnjivi dio:

```
zabranjeni_znakovi = {"(",")","+","-","=","/","*","_",",",".","'",'"',"$",":"," ","\\","a"}
...
zabranjeni_znakovi = {"(",")","+","-","/","*","_",",",".","'",'"',"$",":"," ","\\"}
```

Razlika prikazanih skupova znakova je u tome da drugi skup znakova ne sadrži znakove ```=``` i ```a```.
Zapravo, kod drugog skupa znakova moguće je korištenje funkcije ```exec``` za manipuliranje vrijednosti varijable ```a```.
```
exec(f"{ime_varijable}={vrijednost_varijable}")
```

Kao korisnički ulaz vrijednosti varijable može se unijeti: ```a=123```.
Tako funkcija ```exec``` zapravo izvrši slijedeću naredbu: ```b=a=123```.
Ovim načinom obje varijable poprime istu vrijednost.

Može se preurediti prva _bruteforce_ skripta tako da provjerava sve moguće zajedničke vrijednosti korisničke varijable i varijable ```a```.

```
import subprocess

def rjesiMisiju(prvi_input,drugi_input):
    ulaz = f"{prvi_input}\n{drugi_input}\n"
    rezultat = subprocess.run(
        ["python3", "misija.py"],
        input= ulaz,
        capture_output=True,
        text=True
    )
    output = rezultat.stdout.strip()
    return output

for broj in range(1000):
    output = rjesiMisiju("b",str(broj))
    print(f"Ulaz: {str(broj)} --> Izlaz: {output}")
    if "ERROR" not in output:
            print(f"Uspjeh: {str(broj)}")
            break
else:
    print("Nije pronaden ispravni broj!")
```



Prvi broj koji je uspio rjesiti misiju je ```823```.
S korisničkim unosom ```b``` i ```a=823``` ispiše se flag: ```CTFFOI[3vAls_4nD_Ex3cs]```.

## Edukativne smjernice
- Nikada se ne preporuća koristiti ```exec``` ili ```eval``` na neprovjerenom korisničkom unosu jer korisnik tako može izvršiti proizvoljan kod.
- Umjesto korištenja ```exec```, preporuća se koristi sigurnije funkcije za parsiranje (npr. ```ast.literal_eval```).
- Potrebo je pažljivo definirati dozvoljeni skup znakova u korisničkom unosu. Dopuštanje jednog nepoželjnog znaka može rezultirati sigurnosnim propustom.
