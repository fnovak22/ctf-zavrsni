#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "time.h"


typedef struct{
	char ime[50];
	int cijena;
} Stvar;

int novac;
int brojRacuna;
int ukupnoStvari = 5;

Stvar * dostupneStvari;

int inicijalizirajNovac(){
	return rand()%5005+100;
}

int inicijalizirajRacun(){
	return rand()%100000+1;
}

void pregledRacuna(){
	printf("Broj racuna:\t%d\n", brojRacuna);
	printf("Stanje novca:\t%dc\n", novac);
}

void ocistiUlazniBuffer() {
    while (getchar() != '\n'){};
}

void prikaziUpute(){
	printf("Ovaj program simulira ducan za novu igru koji Pero zeli isprogramirati\nPomozi mu testirati ovaj program kako bi bio sto bolji.\nPero jako voli kada dobi komentare na svoj rad jer se pomocu njih moze samo poboljsati.\n");
}

void pripremiStvari(){
	dostupneStvari = malloc(ukupnoStvari * sizeof(Stvar));
    if (dostupneStvari == NULL) {
        printf("Greska pri alokaciji memorije! Prekidanje programa...\n");
        exit(1);
    }
    
    strcpy(dostupneStvari[0].ime, "Laptop");
    dostupneStvari[0].cijena = 5000;

    strcpy(dostupneStvari[1].ime, "Telefon");
    dostupneStvari[1].cijena = 2000;

    strcpy(dostupneStvari[2].ime, "Slusalice");
    dostupneStvari[2].cijena = 300;

    strcpy(dostupneStvari[3].ime, "Mis");
    dostupneStvari[3].cijena = 150;

    strcpy(dostupneStvari[4].ime, "Super tajna stvar");
    dostupneStvari[4].cijena = 2232350;
}

void prikaziDostupneStvari(){
	printf("Dostupne stvari:\n");
	
	int i;
    for (i = 0; i < ukupnoStvari; i++) {
        printf(" [%d] %s - %dc\n", i + 1, dostupneStvari[i].ime, dostupneStvari[i].cijena);
    }
    
    printf("\n");
}

void ispisiFlag(){
    FILE *file = fopen("flag.txt", "r");
    if (file == NULL) {
        printf("Greska: Ne moze se otvoriti flag.txt\n");
        return;
    }
    
    char flag[100];
    if (fgets(flag, sizeof(flag), file) != NULL) {
        printf("%s\n", flag);
    } else {
        printf("Greska pri citanju flag.txt.\n");
    }
    
    fclose(file);
}

void tajnaStvarKupljena(){
	ispisiFlag();
}

void kupovinaStvari(){
	prikaziDostupneStvari();
	
	int opcija;
	printf("Odaberite stvar koju zelite kupiti (0 za izlaz):\n");
	int uspjesno = scanf("%d",&opcija);
	
	if(uspjesno != 1){
		printf("Neispravan unos! Pokusajte ponovo.\n");
        ocistiUlazniBuffer();
        return;
	}
	
	if(opcija == 0){
		return;
	}
	
	if((opcija-1)>=ukupnoStvari){
		printf("Nepostojeca stvar!.\n");
        return;
	}
	
	int kolicina;
	printf("Kolicina:\n");
	uspjesno = scanf("%d",&kolicina);
	
	if(uspjesno != 1){
		printf("Neispravan unos! Pokusajte ponovo.\n");
        ocistiUlazniBuffer();
        return;
	}
	
	if(kolicina <= 0){
		printf("Kolicina mora biti pozitivan broj!\n");
		return;
	}
	
	if(dostupneStvari[opcija-1].cijena * kolicina <= novac){
		novac-= dostupneStvari[opcija-1].cijena;
		printf("Kupljeno: %s (%dx)\n", dostupneStvari[opcija-1].ime,kolicina);
		
		if(opcija-1 == 4){
			tajnaStvarKupljena();
		}
		
		return;
	}
	else{
		printf("Nedovoljno novca!\n");
		return;
	}
	
	
}

int main(){
	srand(time(NULL));
	
	novac = inicijalizirajNovac();
	brojRacuna = inicijalizirajRacun();
	
	pripremiStvari();
	
	int opcija;
	printf("==== Ducan ====\n");
	do{
		printf("------------------------------\n");
		printf("1 - Upute\n");
		printf("2 - Vas racun\n");
		printf("3 - Kupovina stvari\n");
		printf("0 - Izlaz\n");
		printf("\n");
		
		printf("Odabir:\n");
		int uspjesno = scanf("%d",&opcija);
		
		printf("\n");
		
		
		if(uspjesno != 1){
			printf("Neispravan unos! Pokusajte ponovo.\n");
            ocistiUlazniBuffer();
            continue;
		}
		
		switch(opcija){
			case 1:
				prikaziUpute();
				break;
				
			case 2:
				pregledRacuna();
				break;
				
			case 3:
				kupovinaStvari();
				break;
				
			case 0:
				break;
				
			default:
				printf("Neispravan unos! Pokusajte ponovo.\n");
				break;
		}	
	}while(opcija != 0);
}

