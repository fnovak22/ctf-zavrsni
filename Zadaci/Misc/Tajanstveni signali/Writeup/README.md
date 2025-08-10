# Writeup

Preuzimanjem zip datoteke i njezinim raspakiravanjem, dobi se nekoliko tekstualnih datoteka. 
Nazivi datoteka su od ```l1``` pa sve do ```l29```. Sadržaj datoteka je sličan, ali različit.

- l1.txt = ```????????0001110010010????????```
- l2.txt = ```????????1000101011111????????```
- l29.txt = ```????????0001110011101111100??```

Nazivi datoteka upućuju na to da se ovdje radi o linijama. 
Konkretno imamo 29 linija teksta. 
Može se izraditi kratka python skripta koja spaja sadržaj svih datoteka u jednu datoteku:

```
import os
from natsort import natsorted

def combine_files(input_dir, output_file):
    with open(output_file, 'w') as combined_file:
        txt_files = natsorted(f for f in os.listdir(input_dir) if f.endswith('.txt'))
        
        for i, filename in enumerate(txt_files):
            file_path = os.path.join(input_dir, filename)
            with open(file_path, 'r') as file:
                lines = file.readlines()
                combined_file.writelines(lines)
    
    print(f"Spajanje završeno - spremljeno kao '{output_file}'")

input_dir = 'signali'
output_file = 'combined_output.txt'
combine_files(input_dir, output_file)
```

U kodu se definirao naziv direktorija ```signali``` koji sadrži sve tekstualne datoteke. 
Također se definirao i naziv datoteke ```combined_output.txt``` koja će sadržavati spojen sadržaj svih datoteka. 
Ovdje se koristio _natsort_ za nazive datoteka kako bi se linije mogle prirodno sortirati.
Bez toga bi se ```l11.txt``` učitao prije ```l2.txt``` što ne bi odgovaralo ispravnom redoslijedu signala.
Rezultat izgleda ovako:

```
????????0001110010010????????
????????1000101011111????????
????????0101010001111????????
????????0100101000010????????
????????00111?????010????????
????????11000?????010????????
?????????????????????????????
????????10110?????111????????
000011?1001010100010101100010
011101?0000001111010011010110
100001?0100000011000110111001
10110??0101????????0101101000
10110??1011????????1010010000
111101?1010????????10101???00
010100?0101????????00110???01
110000?1111????????10000???11
001000?1111????????10101???10
111010?0110????????0010111100
001010?0011????????0010101101
000000?0111011000101100001011
111000?0010101100101?????0101
????????100100000010?????01??
????????101100110110?????01??
????????100????10011?????10??
????????111????11101?????11??
????????001????001101100100??
????????0001000011000010011??
????????0011000011001001100??
????????0001110011101111100??
```

Detaljnim pregledom rezultata spajanja, može se uočiti kako kutevi (dole lijevo, gore lijevo, gore desno) sadrže znakove ```?``` u obliku pravokutnika. 
Takav izgled upućuje na to da se ovdje radi o QR kodu.
Znak ```0``` može značiti da se radi o bijeloj boji, a znak ```1``` da se radi o crnoj boji.
No čemu služi znak ```?```? 
Može se izraditi python skripta koja generira sliku na temelju rezultata spajanja:

```
from PIL import Image
import os

input_file_path = 'combined_output.txt'
output_file = 'output_image.png'

def get_color(value):
    if value == '0':
        return (255, 255, 255)  # Bijela
    elif value == '1':
        return (0, 0, 0)  # Crna
    elif value == '?':
        return (255, 0, 0)  # Crvena
    return (255, 255, 255)  # Default, bijela ako je nešto drugo

with open(input_file_path, 'r') as file:
    lines = file.read().strip().split('\n')

    height = len(lines)
    width = len(lines[0])

    image = Image.new('RGB', (width, height), (255, 255, 255))
    pixels = image.load()


    for y in range(height):
        for x in range(width):
            color = get_color(lines[y][x])
            pixels[x, y] = color


    output_file_path = os.path.join(os.getcwd(), output_file)
    image.save(output_file_path)
    
    print(f"Generiranje zavrseno - spremljeno kao '{output_file}'")
```

Pokretanjem ove skripte se generirala slika koja je zamijenila znak ```0``` s bijelim pikselom, znak ```1``` s crnim pikselom i znak ```?``` s crvenim pikselom. 
Slika izgleda ovako:

<p align="center">
 <a href="https://github.com/user-attachments/assets/4da87226-a627-46cd-8742-77c83413d921?raw=true" target="_blank">
  <img src="https://github.com/user-attachments/assets/4da87226-a627-46cd-8742-77c83413d921" width="400"/>
  <a/>
<p/>


Ovo izgleda kao dio QR koda, ali on se ne može skenirati.
Pregledom pravila o formatiranju (standarda) QR koda, mogu se napraviti popravci QR koda koji mogu dovesti do mogućnosti njegova skeniranja.

Prvo se dodaju _Finder patterns_:
<p align="center">
 <a href="https://github.com/user-attachments/assets/cfbcd6d5-04ca-44d3-8a89-f190a220a85d?raw=true" target="_blank">
  <img src="https://github.com/user-attachments/assets/cfbcd6d5-04ca-44d3-8a89-f190a220a85d" width="400"/>
  <a/>
<p/>


Zatim se dodaju _Timing patterns_:


<p align="center">
 <a href="https://github.com/user-attachments/assets/37321bbb-8bca-4ac0-9723-b08d29d7f7bb?raw=true" target="_blank">
  <img src="https://github.com/user-attachments/assets/37321bbb-8bca-4ac0-9723-b08d29d7f7bb" width="400"/>
  <a/>
<p/>

Zatim se doda _Aligment pattern_:

<p align="center">
 <a href="https://github.com/user-attachments/assets/cbed5fab-0402-4443-8ab1-de8e2f5229cc?raw=true" target="_blank">
  <img src="https://github.com/user-attachments/assets/cbed5fab-0402-4443-8ab1-de8e2f5229cc" width="400"/>
  <a/>
<p/>



Zatim se doda _Quiet zone_:

<p align="center">
 <a href="https://github.com/user-attachments/assets/9166564a-ff2a-4e64-8a76-4312de4c146a?raw=true" target="_blank">
  <img src="https://github.com/user-attachments/assets/9166564a-ff2a-4e64-8a76-4312de4c146a" width="400"/>
  <a/>
<p/>


Nakon dodavanja stvari koje su stalno iste, kod se još uvijen ne može skenirati. 
Preostaje nam pogađanje dijela QR koda.
S lijeve strane gdje se nalaze dva crvena piksela je područje _Error correction_-a.
S obzirom na to da su samo dva piksela i svaki od njih može biti bijeli ili crni, postoji samo 4 mogućnosti koje se mogu ručno isprobati.

Kada se gornji crveni piksel poboja u bijelu boju i donji piksel poboja u crnu boju, QR kod se može skenirati:

<p align="center">
 <a href="https://github.com/user-attachments/assets/9bc2c023-ff7b-433a-8f0e-196de348930a?raw=true" target="_blank">
  <img src="https://github.com/user-attachments/assets/9bc2c023-ff7b-433a-8f0e-196de348930a" width="400"/>
  <a/>
<p/>

Kad se on skenira, dobi se flag: ```CTFFOI[QR_C0DEs_4r3_fun]```.

## Edukativne smjernice
- Ne preporuča se skenirati QR kodove iz nepoznati i neprovjerenih izvora jer oni mogu voditi na zlonamjerne web stranice, automatski pokrenuti preuzimanje zlonamjernog softvera ili ukrasti osjetljive podatke putem _phishing_-a.
- QR kod koji je djelomično oštećen ponekad se može skenirati zbog ugrađene korekcije pogrešaka (engl. _Error correction_).
- Neki dijelovi QR koda se mogu ručno popraviti na temelju standardizirane strukture QR koda. To može rezultirati ponovo ispravnim QR kodom.
