# Writeup

Raspakiravanjem dobivene zip arhive dobe se sljedeće datoteke:

```
└─$ tree log 
log
├── LocaleMetaData
│   └── log_1050.MTA
└── log.evtx
```

Arhiva sadrži datoteku ```log.evtx``` koja predstavlja log datoteku u formatu koji koristi _Windows Event Viewer_ (često za praćenje sustavnih događaja).
Tu se nalazi i direktorij ```LocaleMetaData``` koji sadrži datoteku koja ima informacije o jeziku log datoteke.

Otvaranjem ```log.evtx``` datoteke u programu _Windows Event Viewer_ vidi se da ona sadrži podatke o 108 različitih događaja:
![slika](https://github.com/user-attachments/assets/fbe237f1-1a4d-46bc-8343-bf57b9c197ac)


Većina početnih događaja je uzrokovano od strane web preglednika Microsoft Edge (```msedge.exe```). Ovo se može prepoznati po polju ```Image:``` unutar pojedinog događaja:

```
Image: C:\Program Files (x86)\Microsoft\Edge\Application\msedge.exe
```


Događaji koji su povezani s mrežnim prometom su događaji povezani s DNS prometom. To su događaji čiji se Task category zove ```Dns query``` i imaju Event ID jednak ```22```.
Moguće je primijeniti filter za prikazivanje događaja s određenim ID-om:

![slika](https://github.com/user-attachments/assets/a22ee709-29e1-41e4-b2b9-4175b18a18e9)


Detaljnim pregledavanjem tih događaja, može se uočiti nekoliko sumnjivih događaja koji mogu biti povezani s krađom osjetljivih podataka. Sljedeći događaj sadrži DNS adresu s potencijalno sumnjivom poddomenom:

![slika](https://github.com/user-attachments/assets/3472b7fb-8084-41bd-a4bf-7285c4c4d63a)


Prolaskom kroz svih 21 DNS query događaja pronađe se ukupno 3 njih koji sadrže tu sumnjivu poddomenu:

```
Q1RGRk9JW0ROU19l.bestpracticesbanking.com
eEYxbHRyYXRpMG5f.bestpracticesbanking.com
YXR0NGNrS19d.bestpracticesbanking.com
```

Poddomene izgledaju kao poruka enkodirana pomoću Base64 formata. Spajanjem poddomena dobi se ```Q1RGRk9JW0ROU19leEYxbHRyYXRpMG5fYXR0NGNrS19d```.
Poruka se može najjednostavnije dekodirati pomoću nekog online alata.

Dekodirana poruka je flag ```CTFFOI[DNS_exF1ltrati0n_att4ckK_]```.


## Edukativne smjernice
 - DNS eksfiltracija je tehnika skrivanja i slanja podataka unutar DNS upita, pa izgleda kao običan DNS promet. Informacije se najčešće skrivaju unutar poddomena DNS upita.
 - S obzirom na nemogućnost zabranjenja DNS upita, za zaštitu od ove vrste napada se preporučuje:
    - Ograničiti veličinu i učestalost DNS upita (postaviti ograničenja)
    - Implementirati DNS filtering i blokirati nepoznate i sumnjive domene 
    - Koristiti sustave za detekciju anomalija u DNS prometu (SIEM/IDS)
    - Redovito provjeravati logove
