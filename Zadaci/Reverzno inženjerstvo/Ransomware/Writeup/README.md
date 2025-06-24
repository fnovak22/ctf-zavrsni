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


