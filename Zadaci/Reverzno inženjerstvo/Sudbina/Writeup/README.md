# Writeup

Unutar preuzete zip arhive se nalazi izvršni program ```ConsoleApp.exe```.
On se može jednostavno pokrenuti. Postoje dva moguća izlaza:
![slika]()

<p align="center">
 <a href="https://github.com/user-attachments/assets/16253f2f-f16f-4bf0-9317-73b181f66c41?raw=true" target="_blank">
  <img src="https://github.com/user-attachments/assets/16253f2f-f16f-4bf0-9317-73b181f66c41" width="400"/>
  <a/>
<p/>


<p align="center">
 <a href="https://github.com/user-attachments/assets/cb5b5d9a-8f92-4d1e-8c01-692432259ff4?raw=true" target="_blank">
  <img src="https://github.com/user-attachments/assets/cb5b5d9a-8f92-4d1e-8c01-692432259ff4" width="400"/>
  <a/>
<p/>

Potrebno je otkriti tajnu informaciju. Pošto je ovo ```.exe```datoteka, možemo ju otvoriti u IDA kako bismo vidjeli kako radi.



Prvo se otvara funkcija main:

![slika](https://github.com/user-attachments/assets/e5cb8daa-3d9f-4158-b654-a3188e8b3b9f)

Ovaj prikaz prikazuje tok rada programa u obliku instrukcija.
Program započinje u najgornjem bloku.
Na početku se rezervira memoristi prostor za varijable ```a``` i ```randomNum``` na stogu:

```
a= dword ptr -18h
randomNum= dword ptr -14h
```

Zatim izgleda da se postavlja _seed_ pomoću _srand_ i ispisuje se poruka ```= Magic Weather Ball = ```:

```
sub     rsp, 38h
xor     ecx, ecx        ; _Time
call    time
mov     ecx, eax        ; Seed
call    cs:__imp_srand
lea     rdx, _Val       ; "= Magic Weather Ball = "
mov     rcx, cs:__imp_?cout@std@@3V?$basic_ostream@DU?$char_traits@D@std@@@1@A ; _Ostr
call    ??$?6U?$char_traits@D@std@@@std@@YAAEAV?$basic_ostream@DU?$char_traits@D@std@@@0@AEAV10@PEBD@Z ; std::operator<<<std::char_traits<char>>(std::ostream &,char const *)
lea     rdx, ??$endl@DU?$char_traits@D@std@@@std@@YAAEAV?$basic_ostream@DU?$char_traits@D@std@@@0@AEAV10@@Z ; std::endl<char,std::char_traits<char>>(std::ostream &)
mov     rcx, rax
call    cs:__imp_??6?$basic_ostream@DU?$char_traits@D@std@@@std@@QEAAAEAV01@P6AAEAV01@AEAV01@@Z@Z ; std::ostream::operator<<(std::ostream & (*)(std::ostream &))
```

Nakon toga se u registar _eax_ stavi vrijednost 5 (HEX) i uspoređuje se s 64 (HEX):
```
mov     [rsp+38h+a], 5
mov     eax, [rsp+38h+a]
cmp     eax, 64h ; 'd'
```

Zatim provjerava za skok pomoću instrukcije ```jnz``` (ona znači znači Jump if Not Zero - tj. skok se dogodi ako prethodna usporedba nije bila jednaka):
```
jnz     short loc_14000123F
```

Vidimo da se prvi blok ovdje grana u dva smjera, ali prethodna provjera za skok će uvijek biti ista.
U ovome slučaju skok će se uvijek dogoditi.

Taj skok prelazi na drugi blok koji generira slučajni broj i provjerava uvjet za skok pomoću ```jge``` (Jump if Greather Than):

```
loc_14000123F:
call    cs:__imp_rand
cdq
mov     ecx, 0Bh
idiv    ecx
mov     eax, edx
mov     [rsp+38h+randomNum], eax
cmp     [rsp+38h+randomNum], 3
jge     short loc_140001280
```

Provjerava se ako je slučajni brojveći od 3 (HEX), ako jest tada se skače na desni blok, ako nije onda se ostaje na lijevom bloku.
Oba bloka su zadužena za ispis poruke (```Tomorrow will be a gloomy rainy day!``` ili ```Tomorrow will be a wonderful sunny day!```)
Poslije ovih blokova slijedi samo običan _system pause_ da program odma ne završi.

Ukoliko se nije dogodio prvi skok tada se ostaje na prvom lijevom bloku:

```
call    ?revealFlag@@YAXXZ ; revealFlag(void)
nop
jmp     short loc_1400012A4
```

Izgleda da ovaj blok ispisuje flag.

<p align="center">
 <a href="https://github.com/user-attachments/assets/d8ee40b3-7421-419b-b4f4-9691bb3ac464?raw=true" target="_blank">
  <img src="https://github.com/user-attachments/assets/d8ee40b3-7421-419b-b4f4-9691bb3ac464"/>
  <a/>
<p/>


I nakon toga slijedi ovo:

![slika](https://github.com/user-attachments/assets/ecebe1a1-a5ca-4919-a029-e5fe2be7c981)





Također, možemo probati i dekompajlirati kod:

![slika](https://github.com/user-attachments/assets/6a0b601f-6685-4c32-b96a-6fc0a85206fa)

No vidimo da on zapravo ne sadrži provjeru koja je uvijek istinita pa je stavio samo if(true).






U dek

TODO
