# Writeup
Unutar preuzete zip arhive se nalazi izvršni program pogodi_broj.exe. 
On se može jednostavno pokrenuti.
Kada se pokrene, program traži korisnika da unese (pogodi) broj:

<p align="center">
 <a href="https://github.com/user-attachments/assets/443d64c8-cc0f-491d-a6de-e17f5e2a914d?raw=true" target="_blank">
  <img src="https://github.com/user-attachments/assets/443d64c8-cc0f-491d-a6de-e17f5e2a914d" width="500"/>
  <a/>
<p/>

Dekompajliranjem programa u Ghidr-a, dobi se slijedeći kod:


<p align="center">
 <a href="https://github.com/user-attachments/assets/dc025d35-bae5-4ae9-b303-c730916e246e?raw=true" target="_blank">
  <img src="https://github.com/user-attachments/assets/dc025d35-bae5-4ae9-b303-c730916e246e"/>
  <a/>
<p/>


Vidi se dio koda koji prepoznaje točan broj:

```
if (local_c * local_10 * local_14 == local_18) {
  poVar1 = std::operator<<((ostream *)&_ZSt4cout,"Tocan broj!");
  std::ostream::operator<<(poVar1,std::endl<>);
}
```

```local_18``` je varijabla koja sadrži korisnički unos, to se vidi iz linije ```std::istream::operator>>((istream *)&_ZSt3cin,&local_18);```.


Varijable ```local_c```, ```local_10``` i ```local_14``` poprimaju hardkodirane vrijednosti koje se mogu iščitati iz programa.

```
local_c = 0x14e4;
local_10 = 0xcc0;
dVar2 = (double)std::pow<int,int>(0xcc0,0);
local_14 = (int)dVar2;
```

Kada to prebacimo u dekatski brojevni sustav dobi se:

```
local_c = 5348
local_10 = 3264
local_14 = 1

local_c * local_10 * local_14 = 17455872
```


Pokušaj unosa toga broja potvrđuje da je ovaj broj točan:

<p align="center">
 <a href="https://github.com/user-attachments/assets/b4589395-c057-46cc-82a8-0cce18b0b56e?raw=true" target="_blank">
  <img src="https://github.com/user-attachments/assets/b4589395-c057-46cc-82a8-0cce18b0b56e"/>
  <a/>
<p/>

Prema tome, flag je ```CTFFOI[17455872]```.



## Edukativne smjernice
- Za zaštitu osjetljivih konstanti u programu, preporuča se koristiti obfuskaciju ili ih generirati dinamički umjesto hardkodirano.


