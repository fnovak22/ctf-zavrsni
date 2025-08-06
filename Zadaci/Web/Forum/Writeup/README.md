# Writeup

Cilj u ovome zadatku je prijaviti se kao administrator.

Prvo se može registrirati novi korisnik s proizvoljnim podacima:

<p align="center">
 <a href="https://github.com/user-attachments/assets/85fb7fb0-902e-47bc-a25a-6a0395bec0b0?raw=true" target="_blank">
  <img src="https://github.com/user-attachments/assets/85fb7fb0-902e-47bc-a25a-6a0395bec0b0" width="400"/>
  <a/>
<p/>

Pregledom sadržaja objavljenih poruka na forumu, može se zaključiti da je administrator foruma korisnik ```luka654```:

<p align="center">
 <a href="https://github.com/user-attachments/assets/06e5d9d5-632a-4824-80f4-ca6492559eb5?raw=true" target="_blank">
  <img src="https://github.com/user-attachments/assets/06e5d9d5-632a-4824-80f4-ca6492559eb5" width="400"/>
  <a/>
<p/>


Ovaj zadatak je vezan uz _Blind SQL Injection_.
U ovoj vrsti SQL injekcije, ne vide se detaljne poruke o pogrešci prilikom injektiranja upita.
Može se isprobati unijeti najjednostavniji SQL injection. U polje za korisničko ime se unosi ```'OR 1=1 --```, a u polje za lozinku se može unijeti bilo što.


<p align="center">
 <a href="https://github.com/user-attachments/assets/364ee27b-91bc-4eac-a0c5-603bc4e4f4ae?raw=true" target="_blank">
  <img src="https://github.com/user-attachments/assets/364ee27b-91bc-4eac-a0c5-603bc4e4f4ae" width="400"/>
  <a/>
<p/>
  
Nakon pokušaja prijave, uspješno se prijavljuje u aplikaciju kao korisnik ```2_pero_2```. Nažalost, taj korisnik nije administrator.

<p align="center">
 <a href="https://github.com/user-attachments/assets/cffb017b-5d0e-4580-8f34-664b1ba01e1e?raw=true" target="_blank">
  <img src="https://github.com/user-attachments/assets/cffb017b-5d0e-4580-8f34-664b1ba01e1e" width="400"/>
  <a/>
<p/>

S obzirom na prijašnji rezultat, pretpostavlja se da SQL upit izgleda slično kao ```SELECT * FROM users WHERE username = '{username}' AND password = '{password}'```.
Unos ```'OR 1=1 --``` stvori SQL upit koji vraća sve korisnike, ali izgleda da aplikacija uzima samo prvog korisnika.

Da bi se prijavilo kao korisnik ```luka654```, može se probati unijeti u polje za korisničko ime tekst ```luka654' --```.

<p align="center">
 <a href="https://github.com/user-attachments/assets/c6fda17d-4beb-456f-8ec4-98bb18871157?raw=true" target="_blank">
  <img src="https://github.com/user-attachments/assets/c6fda17d-4beb-456f-8ec4-98bb18871157" width="400"/>
  <a/>
<p/>

Ovaj puta se uspješno prijavilo kao korisnik ```luka654``` koji je administrator.
Na stranici _Moj profil_ prikazuje se flag: ```CTFFOI[SQ7_Inj3ct1NG__F0rUUm]```.


<p align="center">
 <a href="https://github.com/user-attachments/assets/894b8018-0eec-46b5-8b09-44e98c1959de?raw=true" target="_blank">
  <img src="https://github.com/user-attachments/assets/894b8018-0eec-46b5-8b09-44e98c1959de" width="400"/>
  <a/>
<p/>

## Edukativne smjernice
- _SQL injection_ je napad u kojem napadač ubacuje zlonamjerni SQL kod kao korisnički unos da bi mogao neautorizirano pristupiti ili izmijeniti neke podatke.
- Za zaštitu od ove vrste napada, preporučuje se:
  - Provjeravati i filtrirati svaki korisnički unos. To je potrebno raditi na klijentskoj strani i na serveru.
  - Koristiti parametrizirane ili pripremljene upite umjesto spajanja stringova.
  - Ne prikazivati detaljne poruke o greškama korisniku (sakriti poruke iz baze ili iznimki)
  - Postaviti ograničenja na duljinu korisničkog unosa.
  - Redovito pregledavati logove prijava i neobične pokušaje pristupa.
  - Primijeniti načelo najmanjih povlastica za korisničke račune i bazu podataka.


