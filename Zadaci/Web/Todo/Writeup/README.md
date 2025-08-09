# Writeup

Tekst zadatka otkriva mali hint prema kojem se može zaključiti da se važne informacije nalaze u datoteci ```robots.txt```. 
To je uobičajena datoteka koja služi kako bi se web crawlerima i botovima odredilo koje dijelove web aplikacije smiju posjećivati.


Pregledom sadržaja datoteke ```robots.txt``` može se uočiti kako je endpoint ```/admin/flag``` zabranjen za pristupanje.

```
User-agent: *
Disallow: /admin/flag
```


Prilikom posjeta ```/admin/flag``` dobi se informacija o tome kako je to nedozvoljen dio web aplikacije.

<p align="center">
 <a href="https://github.com/user-attachments/assets/d73563b1-9e04-425b-b954-516ccf4f40b4?raw=true" target="_blank">
  <img src="https://github.com/user-attachments/assets/d73563b1-9e04-425b-b954-516ccf4f40b4"/>
  <a/>
<p/>

Prema imenu endpointa, može se zaključiti kako je on dostupan samo administratorima.
Ako izradimo novi korisnički račun i ponovo pokušamo otići na ```/admin/flag```, dobi se ista informacija.

Nakon detaljnijeg pregleda web aplikacije, uočio se jedan sumnjivi dio:

<p align="center">
 <a href="https://github.com/user-attachments/assets/92ed70c1-9ff9-441d-ac58-2dccfa6ee7ba?raw=true" target="_blank">
  <img src="https://github.com/user-attachments/assets/92ed70c1-9ff9-441d-ac58-2dccfa6ee7ba"/>
  <a/>
<p/>

Izgleda da se u kolačićima sprema informacija o tome je li korisnik administrator.
Trenutno je vrijednost postavljena na ```0```.
Vrijednosti spremljene u kolačićima se mogu lako mijenjati na strani klijenta.

Postavljanjem navedene vrijednosti na ```1``` i pristupom na ```/admin/flag``` dobi se flag:

<p align="center">
 <a href="https://github.com/user-attachments/assets/ad66db05-1be5-440e-9de0-ab8cfe26c066?raw=true" target="_blank">
  <img src="https://github.com/user-attachments/assets/ad66db05-1be5-440e-9de0-ab8cfe26c066"/>
  <a/>
<p/>


Flag je ```CTFFOI[CcoOk1e_TamP_P3r1ng]```.

## Edukativne smjernice
- Manipulacija kolačićima (engl. _Cookie tampering_) je ranjivost u kojoj napadač mijenja vrijednosti u pohranjenim kolačićima na strani klijenta kako bi dobio neovlašteni pristup.
- Za zaštitu od ove vrste napada, preporučuje se:
  - Nikada ne pohranjivati osjetljive ili autorizacijske podatke (npr. uloge) direktno spremišta na strani klijenta.
  - Označiti kolačiće kao _HttpOnly_ i _Secure_ kako bi ih klijent teže mijenjao ili presretao.
  - Potpisivati ili šifrirati vrijednosti kolačića (npr. pomoću HMAC-a) i na serveru provjeravati potpis prije upotrebe.
  - Uvijek provjeravati prava pristupa na poslužitelju prije posluživanja zaštićenih resursa, ne oslanjati se na podatke iz kolačića.
- Preporuča se ne izlagati skrivene ili osjetljive URL-ove u datoteci robots.txt, jer ona mora biti javno dostupna.
