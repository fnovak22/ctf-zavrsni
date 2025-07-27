# Writeup
Preuzimanjem zip datoteke i njezinim raspakiravanjem dobi se direktorij ```pjesme``` koji sadrži razne datoteke čiji nazivi predstavljaju pjesme izvođača NCS (No Copyright Sound).

```
└─$ tree DJ_usb 
DJ_usb
└── pjesme
    ├── Alan Walker - Fade
    ├── Cartoon, Jéja - On & On
    ├── DEAF KEV - Invincible
    ├── Different Heaven & EH!DE
    ├── Disfigure - Blank
    ├── Electro-Light - Symbolism
    ├── Elektronomia - Sky High
    ├── Janji - Heroes Tonight
    ├── Janji - Spectrum
    └── Spektrem - Shine
```

Detaljnim pregledom imena pjesma, primjećuje se da pjesma ```Janji - Spectrum``` zapravo ne postoji.

Pošto datoteke nemaju označen datotečni nastavak, može se iskoristiti program ```file``` kako bi se provjerilo koje vrste je pojedina datoteka unutar direktorija.
```
└─$ file *
Alan Walker - Fade:        MPEG ADTS, layer III, v1, 128 kbps, 44.1 kHz, JntStereo
Cartoon, Jéja - On & On:   MPEG ADTS, layer III, v1, 128 kbps, 44.1 kHz, JntStereo
DEAF KEV - Invincible:     MPEG ADTS, layer III, v1, 128 kbps, 44.1 kHz, JntStereo
Different Heaven & EH!DE:  MPEG ADTS, layer III, v1, 128 kbps, 44.1 kHz, JntStereo
Disfigure - Blank:         MPEG ADTS, layer III, v1, 128 kbps, 44.1 kHz, JntStereo
Electro-Light - Symbolism: MPEG ADTS, layer III, v1, 128 kbps, 44.1 kHz, JntStereo
Elektronomia - Sky High:   MPEG ADTS, layer III, v1, 128 kbps, 44.1 kHz, JntStereo
Janji - Heroes Tonight:    MPEG ADTS, layer III, v1, 128 kbps, 44.1 kHz, JntStereo
Janji - Spectrum:          RIFF (little-endian) data, WAVE audio, Microsoft PCM, 16 bit, mono 44100 Hz
Spektrem - Shine:          MPEG ADTS, layer III, v1, 128 kbps, 48 kHz, JntStereo
```

Primjećujemo da su sve datoteke zvučne datoteke s ekstenzijom ```.mp3``` osim jedne datoteke ```Janji - Spectrum``` koja je zvučna datoteka s ekstenzijom ```.wav```

Dodavanjem ```.wav``` datotečnog nastavka na ```Janji - Spectrum``` i njenim otvaranjem u programu za reprodukciju zvuka, mogu se čuti neobične frekvencije koje definitivno nisu pjesma.
Prema sumnjivim frekvencijama i dijelu naziva pjesme _Spectrum_, može se posumnjati u **Spectrogram Steganography**. Može se koristiti program _Sonic Visualizer_ da bi se provjerilo ukoliko postoji skrivena poruka u spektrogramu zvučne datoteke.

Otvaranjem vizualnog prikaza u spomenutom programu, dobije se ovakav izgled spektrograma:

![slika](https://github.com/user-attachments/assets/46ad8b83-41f6-431c-8f6c-67727cbde345)

Jasno se vidi da se u spektrogramu slike nalazi flag ```CTFFOI[h1dd3n_sp3ctrum]```.

## Napomena
Postavljanjem pogrješne ekstenzije na _WAVE audio_ datoteku (npr. _MP3_), ne može se dobiti ispravan prikaz skrivene poruke u spektrogramu zbog prisutne kompresije kod nekih audio formata (konkretno _MP3_ formata). MP3 koristi kompresiju gdje se pri kodiranju _MP3_ datoteke gubi dio podataka, uključujući visokofrekvencijske komponente koje bi mogle biti potrebne za očuvanje skrivenih informacija unutar spektrograma.

## Edukativne smjernice
- Nikad se ne smije pretpostavljati format datoteke na temelju naziva. Uvijek je potrebno provijeri format datoteke (npr. s alatom _file_)
- Zvuk se može vidjeti kao slika kroz spektrogram. On se temelji na frekvencijskim uzorcima zvuka.
- Koristan online alatu u kojem se može isprobati proces skrivanja i otkrivanja slika u spektrogramu zvuka je https://nsspot.herokuapp.com/imagetoaudio/
- Treba paziti na kompresiju jer MP3 može _uništiti_ skrivene poruke u visokim frekvencijama
