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
 <a href="https://github.com/user-attachments/assets/fbe7b4b1-fca3-46bb-a61c-1f53a74a2b8a?raw=true" target="_blank">
  <img src="https://github.com/user-attachments/assets/fbe7b4b1-fca3-46bb-a61c-1f53a74a2b8a"/>
  <a/>
<p/>

<p align="center">
 <a href="https://github.com/user-attachments/assets/f4fd1cdf-ec6b-4e2c-90f3-40a4cb59ef0f?raw=true" target="_blank">
  <img src="https://github.com/user-attachments/assets/f4fd1cdf-ec6b-4e2c-90f3-40a4cb59ef0f"/>
  <a/>
<p/>


Na početku main funkcije se deklaliraju lokalne varijabgle na stacku (do 22. linije).

Zatim se inicijaliziraju dva stringa: ```flag.txt``` i ```flag.en```. Oni vjerojatno služe da se odredi iz koje datoteke će se sadržaj pročitati i u koju datoteku će se kriptirani sadržaj zapisati.

Slijedeći dio izgledao kao ključ za šifriranje:

```
local_40 = "K3Ph.t6sd!Ua$#Ca";
```

Nakon toga se ponovo polavljuje polovica toga ključa što je malo sumnjivo:
```
  local_b8[8] = 'K';
  local_b8[9] = '3';
  local_b8[10] = 'P';
  local_b8[0xb] = 'h';
  local_b8[0xc] = '.';
  local_b8[0xd] = 't';
  local_b8[0xe] = '6';
  local_b8[0xf] = 's';
  local_b8[0] = '\x1c';
  local_b8[1] = '1';
  local_b8[2] = 0xe1;
  local_b8[3] = 'x';
  local_b8[4] = 0x9a;
  local_b8[5] = 'K';
  local_b8[6] = '=';
  local_b8[7] = 0xef;
```

Izgleda da se ovdje na početku polja ```local_b8``` postavlja hardkodirani IV i na drugoj polovici hardkodirani dio ključa.
