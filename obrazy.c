#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "modul.h"

#define MAX 512            /* Maksymalny rozmiar wczytywanego obrazu */
#define DL_LINII 1024      /* Dlugosc buforow pomocniczych */
#define KONIEC 99


int main() {
  int obraz[MAX][MAX] ;
  int wymx,wymy,odcieni;       
  FILE *plik, *plikwy;   
  char nazwa[100],nazwawy[100];  /*nazwa plikow kolejno wczytywanego, wypisywanego*/
  char wybor1[2],wybor2[2],wybor3[2];      /*okresla wybor switch case */
  
  for(;;){
     printf("\nWitamy w programie do przetwarzania i wyswietlania obrazow!\n\n");
     printf("Co chcesz zrobic?(Wpisz numer polecenia)\n");
     printf("1.Wczytaj obraz aby zaczac przetwarzanie lub wyswieltic\n");
     printf("2.Zakonc prace\n");
     printf("Twoj wybor: ");
     scanf("%s",wybor1);
     printf("\n");

     switch(wybor1[0]){
     case '1':
       /* Wczytanie zawartosci wskazanego pliku do pamieci */
       printf("Podaj nazwe pliku:\n");
       scanf("%s",nazwa);
       plik=fopen(nazwa,"r");

       /* co spowoduje zakomentowanie tego warunku */
       if (plik != NULL) {      
	 czytaj(plik,obraz,&wymx,&wymy,&odcieni);
	 fclose(plik);
       }else{
	 printf("Obraz niepoprawny :(\n");
	 break;
       }
       for(;;){
	 printf("Co chcesz zrobic z wczytanym obrazem obrazem?(Wpisz numer polecenia)\n");
	 printf("1.Zapisz i wyswietl obraz\n");
	 printf("2.Rozciaganie histogramu\n");
	 printf("3.Rozmywanie poziome\n");
	 printf("4.Konturowanie\n");
	 printf("5.Zmiana poziomow\n");
	 printf("6.Progowanie\n");
	 printf("7.Negatyw\n");
	 printf("8.Koniec\n");
	 printf("Twoj wybor: ");
	 scanf("%s",wybor2);
	 printf("\n");
	 
	 switch(wybor2[0]){
	 case '1':
	   printf("Podaj nazwe pliku wypis:\n");
	   scanf("%s",nazwawy);
	   plikwy = fopen(nazwawy, "w");
	   wypis(plikwy,obraz,wymx,wymy,odcieni);
	   fclose(plikwy);
	   wyswietl(nazwawy);
	   printf("Czy chcesz kontynuwac prace nad obrazem?(y or n)\n");
	   printf("Twoj wybor: ");
	   scanf("%s",wybor3);
	   printf("\n");
	   if(wybor3[0] == 'n'){
	     printf("Program zakonczony.\n");
	     printf("Do zobaczenia :)\n");
	     return 0;
	   }
	 case '2':
	   rozciaganie_histogramu(obraz,wymx,wymy,odcieni);
	   printf("Rozciaganie histogramu zostalo wykonane\n");
	   break;
	 case '3':
	   rozmywanie_poziome(obraz,wymx,wymy,odcieni);
	   printf("Rozmywanie poziome zostalo wykonane\n");
	   break;
	 case '4':
	   konturowanie(obraz,wymx,wymy,odcieni);
	   printf("Konturowanie zostalo wykonane\n");
	   break;	 
	 case '5':
	   zmiana_poziomow(obraz,wymx,wymy,odcieni);
	   printf("Zmiana poziomow zostala wykonana\n");
	   break;
	 case '6':
	   progowanie(obraz,wymx,wymy,odcieni);
	   printf("Progowanie zostalo wykonane\n");
	   break;	 
	 case '7':
	   negatyw(obraz,wymx,wymy,odcieni);
	   printf("Negatyw zostal wykonany\n");
	   break;	 	 
	 case '8':
	   printf("Czy aby napewno chcesz wyjsc?(y or n)\n");
	   printf("Twoj wybor: ");
	   scanf("%s",wybor3);
	   printf("\n");
	   if(wybor3[0] == 'y'){
	     printf("Program zakonczony.\n");
	     printf("Do zobaczenia :)\n");
	     return 0;
	   }
	 default:
	   printf("Niestety opcja nie istnieje, prosimy wybrac ponownie :)\n");
	 }
	 wybor3[0] = '0';
	 printf("Czy chcesz kontynuowac akcje nad obrazem?(y or n)\n");
	 while(wybor3[0] != 'y' && wybor3[0] != 'n'){
	   printf("Twoj wybor: ");
	   scanf("%s",wybor3);
	 }
	 printf("\n");
	 if(wybor3[0] == 'n'){
	   wybor3[0] = '0';
	   printf("Czy chcesz zapisac i wyswietlic?(y or n)\n");

	   while(wybor3[0] != 'y' && wybor3[0] != 'n'){
	     printf("Twoj wybor: ");
	     scanf("%s",wybor3);
	   }
	   if(wybor3[0] == 'y'){
	     printf("Podaj nazwe pliku wypis:\n");
	     scanf("%s",nazwawy);
	     plikwy = fopen(nazwawy, "w");
	     wypis(plikwy,obraz,wymx,wymy,odcieni);
	     fclose(plikwy);
	     wyswietl(nazwawy);
	   }
	   printf("Program zakonczony.\n");
	   printf("Do zobaczenia :)\n");
	   return 0;
	 }

	   
	  
       }
     case '2':
       printf("Program zakonczony.\n");
       printf("Do zobaczenia :)\n");
       return 0;
     default:
       printf("Niestety opcja nie istnieje, prosimy wybrac ponownie :)\n");
     }
  }
  return 0;
}
