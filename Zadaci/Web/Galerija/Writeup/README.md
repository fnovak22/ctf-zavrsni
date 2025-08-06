# Writeup

Cilj u ovome zadatku je pregledati galeriju slika administratora.

Prvo se može registrirati novi korisnik s proizvoljnim podacima:

<p align="center">
 <a href="https://github.com/user-attachments/assets/4810c523-f7ff-4046-af20-bef020deae49?raw=true" target="_blank">
  <img src="https://github.com/user-attachments/assets/4810c523-f7ff-4046-af20-bef020deae49" width="400"/>
  <a/>
<p/>

Nakon prijave, vidi se prazna galerija slika.

<p align="center">
 <a href="https://github.com/user-attachments/assets/0b63952b-d654-463e-8e30-7c68545e5831?raw=true" target="_blank">
  <img src="https://github.com/user-attachments/assets/0b63952b-d654-463e-8e30-7c68545e5831" width="400"/>
  <a/>
<p/>

Link za pregled vlastite galerija slika izgleda sumnjivo:

<p align="center">
 <a href="https://github.com/user-attachments/assets/4770b43d-db4a-4483-90f2-9298f90b5cf8?raw=true" target="_blank">
  <img src="https://github.com/user-attachments/assets/4770b43d-db4a-4483-90f2-9298f90b5cf8" width="300"/>
  <a/>
<p/>


Ako se registriramo i prijavimo kao drugi korisnik, tada će se link za pregled vlastite galerije slika promijeniti u ```http://127.0.0.1:5000/galerija/4```.
Ovdje se primjećuje moguća ranjivost _IDOR (Insecure Direct Object Reference)_, gdje napadač može direktno mijenjati identifikator objekta i tako steći neovlašten pristup tuđim resursima.

Pretpostavlja se da je brij na kraju URL-a zapravo ID vlasnika galerije slika. Promjenom URL-a u  ```http://127.0.0.1:5000/galerija/1``` dobi se galerija slika korisnika _test_korisnik_:

<p align="center">
 <a href="https://github.com/user-attachments/assets/dfc1e4f5-a757-4d7f-9f0c-c8fecc44633a?raw=true" target="_blank">
  <img src="https://github.com/user-attachments/assets/dfc1e4f5-a757-4d7f-9f0c-c8fecc44633a"/>
  <a/>
<p/>


Ovdje nažalost nema flag-a.
Može se još pokušati korisnik s ID-em 2. 
Dobila se galerija administratora: 

<p align="center">
 <a href="https://github.com/user-attachments/assets/30fa4e6a-a82c-4238-ae02-249a95b10019?raw=true" target="_blank">
  <img src="https://github.com/user-attachments/assets/30fa4e6a-a82c-4238-ae02-249a95b10019"/>
  <a/>
<p/>


Vidi se jedna slika koja sadrži flag: ```CTFFOI[g4ll1ERy_iIiD0r]```.

## Edukativne smjernice
 - IDOR (engl. _Insecure Direct Object Reference_) je ranjivost u kojoj napadač mijenjanjem izloženog ID-ja u URL-u ili zahtjevu dobiva neovlašten pristup tuđim resursima.
 - Za zaštitu od ove vrste napada, preporučuje se:
   - Uvijek provjeriti valjano vlasništvo nad resursom prije njegovog prikaza
   - Bolje je koristiti nasumične tokene ili UUID (engl. _Universally Unique Identifier_) u URL-u za posluživanje resursa umjesto korištenja pravih internih ID-eva.




