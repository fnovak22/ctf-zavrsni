# Writeup

Zadatak daje jednu zip arhivu. Arhiva je zaključana lozinkom i ne može se raspakirati bez nje:

```
└─$ unzip disk.zip   
Archive:  disk.zip
[disk.zip] shema.png password:
```

Zanimljivo je da se može pregledati sadržaj zip arhive bez njenog otključavanja:

```
└─$ unzip -l disk.zip
Archive:  disk.zip
  Length      Date    Time    Name
---------  ---------- -----   ----
   336577  2025-03-03 20:36   shema.png
---------                     -------
   336577                     1 file
```

Kako nam u tekstu zadatka piše da lozinka sadrži najvjerojatnije 5 znakova, može se koristiti **brute force** metoda probijanja lozinke zip arhive.
Poznati program za probijanje lozinki koji uključuje i ovu metodu je ```john``` (_John The Reaper_).

Prije samog korištenja _john_, potrebno je koristiti alat ```zip2john``` kako bi se iz zip arhive izdvojili podaci koji se odnose na enkripcijski mehanizam.
Na kraju se ti podaci formatiraju u poseban oblik (hash format) koji je kompatibilan s _john_. (Izravno korištenje _john_-a nad izvornom zip arhivom nije mogće).

```
└─$ zip2john disk.zip > disk_hash.txt
ver 2.0 disk.zip/shema.png PKZIP Encr: cmplen=306040, decmplen=336577, crc=D07CEF99 ts=A48C cs=d07c type=8
```

Sadržaj početka disk_hash.txt datoteke (parametar ```c``` označava broj bajtova od početka datoteke):

```
└─$ head -c 100 disk_hash.txt
disk.zip/shema.png:$pkzip$1*1*2*0*4ab78*522c1*d07cef99*0*27*8*4ab78*d07c*f7647577b9a157ee93ce393f25b  
```

Potrebno je pokrenuti _brute force_ napad sa informacijom da je lozinka duljine 5 znakova:

```
└─$ john disk_hash.txt --min-length=5 --max-length=5
```

Nakon nekog vremena lozinka se uspješno probije:

```
Proceeding with incremental:ASCII, lengths: 5-5
@A5!b           (disk.zip/shema.png)     
1g 0:00:00:51 DONE 3/3 (2025-03-14 12:55) 0.01939g/s 36879Kp/s 36879Kc/s 36879KC/s @>mYz..@EaUe
Use the "--show" option to display all of the cracked passwords reliably
Session completed. 
```

Provijena lozinka zip arhive je ```@A5!b```.



