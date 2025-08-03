# Writeup

Pregledom sadržaja razgovora, izgleda da se u njemu nalazi flag koji nije u čitljivom formatu:
```
UMCCID[U4b3l4k_u1jćć_bk]
```

Može se uočiti kako je naziv jednog korisnika ```cezar85```.
Ovo može biti hint da se radi o Cezarovoj šifri (engl. _Caesar cipher_).

Znamo da je format flag-a ovakav ```CTFFOI[<znakovi>]```.

Sada je potrebno izračunati ključ.
To se može izračunati na način da se vidi udaljenost slova ```C``` (početak pravog flag-a) i ```U``` (početak kriptiranog flag-a).
Važan korak je da se primjeni ispravna abeceda.
Hrvatska abeceda ima nešto više znakova od engleske abecede.
Prema sadržaju razgovora, može se zaključiti da se radi o hrvatskoj abecedi jer kriptirani tekst sadrži znakove poput ```čć```.

Hrvatska abeceda: ```abcčćdđefghijklmnoprstšuvzž```.

Udaljenost ```C``` i ```U``` je jednako ```21``` (to je ključ).

Poruka se može dekriptirani na online web stranici za dekriptiranje Cezarove šifre: https://cryptii.com/pipes/caesar-cipher .

<p align="center">
 <a href="https://github.com/user-attachments/assets/04d141bc-0a21-442a-a3a0-5c9494e8ea68?raw=true" target="_blank">
  <img src="https://github.com/user-attachments/assets/04d141bc-0a21-442a-a3a0-5c9494e8ea68"/>
  <a/>
<p/>
  
Flag je ```CTFFOI[C4e3s4r_c1phh_er].```

## Edukativne smjernice
- Prilikom dešifriranja Cezarove šifre, treba obratiti pažnju na abecedu jer je ona različita kod različitih jezika. Bez točne abecede se ne može otkriti izvorna poruka.
- Ne preporučuje se koristiti Cezarovu šifru za zaštitu sadržaja poruka jer se ona vrlo lako probije. Umjesto nje, preporuča se koristiti jače metode šifriranja (npr. RSA) koje su otpornije na napade.
