# Writeup

U prloženoj datoteci nalazi se nečitljiva poruka:
```
M2d4dzRuSk0yRVJzUTJSVFZpVzd6Q0NnczREemZ1Uml1QkthNkVtOThIUllTa3A2YUZqYTFVRHc1b1M5Z1lzUGoy
```

Prema sadržaju slova, izgleda da se koristi neki encoding.
Kod ovakvih situacija, preporuča se unijeti poruku u online alat za dekodiranje (i enkodiranje) poruka (npr. https://gchq.github.io/CyberChef/).
Taj alat može prepoznati o kojoj vrsti encodinga se radi. Tada će alat prikazati ikonu čarobnog štapića koja se može pritisnitu kako bi se automatski dekorirala poruka.

<p align="center">
 <a href="https://github.com/user-attachments/assets/6559fc0f-5e84-47e1-bf63-93cc18b2fdf2?raw=true" target="_blank">
  <img src="https://github.com/user-attachments/assets/6559fc0f-5e84-47e1-bf63-93cc18b2fdf2" width="400"/>
  <a/>
<p/>

Klikom na ikonu, alat je dekodirao poruku s Base64 formatom i dao izlaz:

```
3gxw4nJM2ERsQ2RTViW7zCCgs4DzfuRiuBKa6Em98HRYSkp6aFja1UDw5oS9gYsPj2
```

Sada je ponovo prepoznati novi encoding, Base58. 
Novi izlaz je:

```
INKEMRSPJFNUK3TDGBCGS3SHL5TDAUSSL5WDCZRTLU======
```

Ponovo je prepoznati novi encoding, Base32.
Konačan izlaz je flag:

```
CTFFOI[Enc0DinG_f0RR_l1f3]
```

<p align="center">
 <a href="https://github.com/user-attachments/assets/4e565867-6c1a-44a7-be93-cf70fad9a923?raw=true" target="_blank">
  <img src="https://github.com/user-attachments/assets/4e565867-6c1a-44a7-be93-cf70fad9a923"/>
  <a/>
<p/>


## Edukativne smjernice
- Prilikom susreta s nečitljivim nizom znakova, preporuča se prvo provjeriti ako se radi o nekoj vrsti kodiranja u alatu poput CyberChefa. On može automatski prepoznati vrstu i primjeniti odgovarajući dekoder.
