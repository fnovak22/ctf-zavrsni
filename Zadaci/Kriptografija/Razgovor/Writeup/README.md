# Writeup

Pregledom sadržaja razgovora, izgleda da se u njemu nalazi flag koji nije u čitljivom formatu:
```
XOAAJD[Rz4f_X4z3n4m_x1kcc_zm]
```

Može se uočiti kako je naziv jednog korisnika ```cezar85```.
Ovo može biti hint da se radi o Cezarovoj šifri (engl. _Caesar cipher_).

Znamo da je format flag-a ovakav ```CTFFOI[<znakovi>]```.

Sada je potrebno izračunati ključ.
To se može izračunati na način da se vidi udaljenost slova ```C``` (početak pravog flag-a) i ```X``` (početak kriptiranog flag-a).
Važan korak je da se primjeni ispravna abeceda.
Prema sadržaju razgovora, može se zaključiti da se radi o engleskoj abecedi jer kriptirani tekst ne sadrži znakove poput ```čć```.

Engleska abeceda: ```abcdefghijklmnopqrstuvwxyz```.

Udaljenost ```C``` i ```X``` je jednako ```21``` (to je ključ).

Poruka se može dekriptirani na online web stranici za dekriptiranje Cezarove šifre: https://cryptii.com/pipes/caesar-cipher .

<p align="center">
 <a href="https://github.com/user-attachments/assets/8299058c-f792-4694-8337-30c9e3fac72d?raw=true" target="_blank">
  <img src="https://github.com/user-attachments/assets/8299058c-f792-4694-8337-30c9e3fac72d"/>
  <a/>
<p/>

  
Flag je ```CTFFOI[C4e3s4r_c1phh_er].```

## Edukativne smjernice
- Prilikom dešifriranja Cezarove šifre, treba obratiti pažnju na abecedu jer se ona razlikuje kod različitih jezika. Bez točne abecede, ne može se otkriti izvorna poruka.
- Ne preporučuje se koristiti Cezarovu šifru za zaštitu sadržaja poruka jer se ona vrlo lako probije. Umjesto nje, preporuča se koristiti jače metode šifriranja (npr. RSA) koje su otpornije na napade.
