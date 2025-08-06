# Writeup

Unutar preuzete zip arhive se nalazi izvršna datoteka virusa ```rans.exe``` i kriptirana datoteka ```flag.enc```.

Izvršna datoteka je ELF 64-bit LSB executable:
```
└─$ file rans.exe
rans.exe: ELF 64-bit LSB executable, x86-64, version 1 (GNU/Linux), statically linked, BuildID[sha1]=f6aeb39fda76c8b8c63b7864261a61e3e6fa3136, for GNU/Linux 3.2.0, not stripped

```

To je standardni format za izvršne datoteke na Linux-u i sličnim Unix operativnim sustavima, tj. pokreće se na Linuxu.

Može se probati dekompajlirati ```rans.exe``` pomoću alata Ghidra.

<p align="center">
 <a href="https://github.com/user-attachments/assets/c58d74d6-9a28-4bc9-9740-cc070e3ba509?raw=true" target="_blank">
  <img src="https://github.com/user-attachments/assets/c58d74d6-9a28-4bc9-9740-cc070e3ba509"/>
  <a/>
<p/>

<p align="center">
 <a href="https://github.com/user-attachments/assets/cd0d8b9d-4f93-4fb0-9ec8-08af63476ab4?raw=true" target="_blank">
  <img src="https://github.com/user-attachments/assets/cd0d8b9d-4f93-4fb0-9ec8-08af63476ab4"/>
  <a/>
<p/>

Na početku main funkcije se deklariraju lokalne varijable na stacku (do 22. linije).

Zatim se inicijaliziraju dva stringa: ```flag.txt``` i ```flag.en```. Oni vjerojatno služe da se odredi iz koje datoteke će se sadržaj pročitati i u koju datoteku će se kriptirani sadržaj zapisati.

Slijedeći dio izgledao kao ključ za šifriranje:

```
local_30 = "K3Ph.t6sd!Ua$#Ca";
```

Nakon toga se ponovo pojavljuje polovica toga ključa što je malo sumnjivo:
```
local_a8[8] = 'K';
local_a8[9] = '3';
local_a8[10] = 'P';
local_a8[0xb] = 'h';
local_a8[0xc] = '.';
local_a8[0xd] = 't';
local_a8[0xe] = '6';
local_a8[0xf] = 's';
local_a8[0] = '\x1c';
local_a8[1] = '1';
local_a8[2] = 0xe1;
local_a8[3] = 'x';
local_a8[4] = 0x9a;
local_a8[5] = 'K';
local_a8[6] = '=';
local_a8[7] = 0xef;
```

Izgleda da se ovdje na početku polja ```local_a8``` postavlja hardkodirani IV i na drugoj polovici hardkodirani dio ključa.

Zatim se pretpostavlja da se čita sadržaj datoteke ```flag.txt``` i priprema se izlazni vektor:
```
readFile(local_c8);
std::vector<>::vector(local_e8);
```

Nakon toga slijedi kreiranje objekta za šifriranje:
```
CryptoPP::CipherModeFinalTemplate_CipherHolder<>::CipherModeFinalTemplate_CipherHolder(local_1f8);
```

Ovdje se ne vidi koji se algoritam točno koristio za šifriranje. Da bi se to saznalo, može se duplo pritisnuti na ```CipherModeFinalTemplate_CipherHolder```:

<p align="center">
 <a href="https://github.com/user-attachments/assets/051d66a7-5f1f-4998-9e99-d02078fe1556?raw=true" target="_blank">
  <img src="https://github.com/user-attachments/assets/051d66a7-5f1f-4998-9e99-d02078fe1556"/>
  <a/>
<p/>

Vidi se da je dekompajler shvatio da se radi o DES algoritmu šifriranja u načinu rada CBC.
DES je simetrični algoritam šifriranja koji koristi blokove. On koristi 8 bajtova za ključ i 8 bajtova za IV (inicijalizacijski vektor).
Kod CBC načina rada, svaki blok ovisi o prethodnom bloku. Samo prvi blok ovisi o IV-u (on se XOR-a s IV-em).


Slijedeći dio objektu šifriranja ```local_1f8``` dodjeljuje ključ i IV.

```
CryptoPP::SimpleKeyingInterface::SetKeyWithIV((SimpleKeyingInterface *)local_1f8, local_a8 + 8, 8, local_a8);
```

 - ```local_a8 + 8``` je druga polovica polja koja sadrži ključ
 - ```8``` je duljina ključa u bajtovima
 - ```local_a8``` pokazuje na početak polja gdje se nalazi IV


Dokumentacija: https://cryptopp.com/docs/ref/class_simple_keying_interface.html#a5b4e358c514fd743840967bc595a34c2

Ostatak koda samo šifrira izvorni sadržaj datoteke ```flag.txt```, zapisuje ga u kriptiranu datoteku ```flag.enc``` i briše datoteku ```flag.txt```. Sada se ima dovoljno informacija o radu ovog ransomware-a i može se pokušati napraviti skripta za dekriptiranje ```flag.enc```. 

Izrađena python skripta za dešifriranje:
```
from Crypto.Cipher import DES

key = b'K3Ph.t6s'
iv = bytes([0x1c, 0x31, 0xe1, 0x78, 0x9a, 0x4b, 0x3d, 0xef])

data = open('flag.enc', 'rb').read()
des = DES.new(key, DES.MODE_CBC, iv)

plaintext = des.decrypt(data)
print("Decrypted flag:", plaintext)
```

Pokretanjem skripte, ispiše se flag: ```CTFFOI[SuRv1v3d_R4ns0mWWare]```.

## Edukativne smjernice
- Ransomware je zlonamjerni program koji šifrira podatke na računalu i traži otkupninu da bi ih se ponovo dešifriralo.
- Za zaštitu od ove vrste napada, preporuča se uvijek imati rezervnu kopiju važnih podataka koji se ne smiju izgubiti.
- Ako se dogodi napad ransomware-om preporuča se:
  - Nikada ne platiti otkupninu jer nema garancije da će se vaši podaci vratiti. Također, na taj način se potiče zlonamjerne osobe da nastave napadati ransomware-om.
  - Ne smije se odmah ugasiti računalo jer postoji šansa da se u RAM memoriji računala nalaze bitne informacije (ključevi) koji su potrebni za ručno dešifriranje _izgubljenih_ podataka
  - Isključiti pristup internetu i mreži na zaraženom računalu kako bi se spriječila daljnja zaraza ostalih računala u mreži.


