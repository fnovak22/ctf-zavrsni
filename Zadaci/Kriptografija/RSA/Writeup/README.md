# Writeup

Sadržaj poruke je ovaj:
```
c = 7452354012553044732222211804379106889276076253506213039618031679443843953406
N = 57996576886940371380673626239229465537025538800923594942557511646751175693553
e = 17
```

Prema nazivu zadatka, može se zaključiti da se ovdje radi o RSA algoritmu enkripcije.

Značenje pojedine vrijednosti:
 - ```c``` predstavlja šifriranu poruku
 - ```N``` je javni ključ
 - ```e``` je privatni eksponent

Privatni ključ kod RSA tvore ```p``` i ```q```. 
To bi trebala biti dva jako velika prosta broja.
Javni ključ ```N``` je jednak umnošku ```p``` i ```q```.

Pregledom dane vrijednosti ```N```, može se zaključiti da je ona vrlo mala.
Radi toga, može se probati rastaviti na proste faktore (faktorizirati).
Često korišten alat za faktorizaciju velikih brojeva je [FactorDB](https://factordb.com).
To je internetska baza podataka koja pohranjuje faktorizacije velikih brojeva i omogućuje automatsko traženje njihovih prostih faktora.


Kada se u FactorDB unese ```N```, uspješno se pronađu njegovi faktori:
 - p = ```226720954803001339956417957096012760121```
 - q = ```255805983780078058582980500570307446393```

To znači da su pohranjeni u bazi ili da se oni mogu lako izračunati.

Sada se može napraviti jednostavna python skripta koja dešifrira dobivenu poruku:

```
c = 7452354012553044732222211804379106889276076253506213039618031679443843953406
N = 57996576886940371380673626239229465537025538800923594942557511646751175693553
e = 17

p = 226720954803001339956417957096012760121
q = 255805983780078058582980500570307446393

phi_n = (p - 1) * (q - 1)
d = pow(e,-1,phi_n)
m = pow(c, d, N)

def int_to_text(number):
    byte_length = (number.bit_length() + 7) // 8
    return number.to_bytes(byte_length, byteorder='big').decode('utf-8')
    
m = int_to_text(m)
print(m)
```

Dešifrirana poruka je flag: ```CTFFOI[G3t_B1gg3R_Pr1mes]```
