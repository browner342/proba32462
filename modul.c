#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "modul.h"

#define MAX 512            /* Maksymalny rozmiar wczytywanego obrazu */
#define DL_LINII 1024      /* Dlugosc buforow pomocniczych */
#define KONIEC 99

/************************************************************************************
 * Funkcja wczytuje obraz PGM z pliku do tablicy       	       	       	       	    *
 *										    *
 * \param[in] plik_we uchwyt do pliku z obrazem w formacie PGM			    *
 * \param[out] obraz_pgm tablica, do ktorej zostanie zapisany obraz		    *
 * \param[out] wymx szerokosc obrazka						    *
 * \param[out] wymy wysokosc obrazka						    *
 * \param[out] szarosci liczba odcieni szarosci					    *
 * \return liczba wczytanych pikseli						    *
 ************************************************************************************/

int czytaj(FILE *plik_we,int obraz_pgm[][MAX],int *wymx,int *wymy, int *szarosci) {
  char buf[DL_LINII];      /* bufor pomocniczy do czytania naglowka i komentarzy */
  int znak;                /* zmienna pomocnicza do czytania komentarzy */
  int koniec=0;            /* czy napotkano koniec danych w pliku */
  int i,j;

  /*Sprawdzenie czy podano prawidlowy uchwyt pliku */
  if (plik_we==NULL) {
    fprintf(stderr,"Blad: Nie podano uchwytu do pliku\n");
    return(0);
  }

  /* Sprawdzenie "numeru magicznego" - powinien byc P2 */
  if (fgets(buf,DL_LINII,plik_we)==NULL)   /* Wczytanie pierwszej linii pliku do bufora */
    koniec=1;                              /* Nie udalo sie? Koniec danych! */

  if ( (buf[0]!='P') || (buf[1]!='2') || koniec) {  /* Czy jest magiczne "P2"? */
    fprintf(stderr,"Blad: To nie jest plik PGM\n");
    return(0);
  }

  /* Pominiecie komentarzy */
  do {
    if ((znak=fgetc(plik_we))=='#') {         /* Czy linia rozpoczyna sie od znaku '#'? */
      if (fgets(buf,DL_LINII,plik_we)==NULL)  /* Przeczytaj ja do bufora                */
	koniec=1;                   /* Zapamietaj ewentualny koniec danych */
    }  else {
      ungetc(znak,plik_we);                   /* Gdy przeczytany znak z poczatku linii */
    }                                         /* nie jest '#' zwroc go                 */
  } while (znak=='#' && !koniec);   /* Powtarzaj dopoki sa linie komentarza */
                                    /* i nie nastapil koniec danych         */

  /* Pobranie wymiarow obrazu i liczby odcieni szarosci */
  if (fscanf(plik_we,"%d %d %d",wymx,wymy,szarosci)!=3) {
    fprintf(stderr,"Blad: Brak wymiarow obrazu lub liczby stopni szarosci\n");
    return(0);
  }
  /* Pobranie obrazu i zapisanie w tablicy obraz_pgm*/
  for (i=0;i<*wymy;i++) {
    for (j=0;j<*wymx;j++) {
      if (fscanf(plik_we,"%d",&(obraz_pgm[i][j]))!=1) {
	fprintf(stderr,"Blad: Niewlasciwe wymiary obrazu\n");
	return(0);
      }
    }
  }
  return *wymx**wymy;   /* Czytanie zakonczone sukcesem    */
}                       /* Zwroc liczbe wczytanych pikseli */


int wypis(FILE *plik_wy,int obraz_pgm[][MAX],int wymx,int wymy, int szarosci) {
  int i,j= 0;
  /*Sprawdzenie czy podano prawidlowy uchwyt pliku */
  if (plik_wy==NULL) {
    fprintf(stderr,"Blad: Nie podano uchwytu do pliku\n");
    return(0);
  }

  /* Zapisanie "magicznego" znaku P2 */
  fprintf(plik_wy, "P2\n");

  /* Zapisanie wymiarow obrazu i liczby odcieni szarosci */
  fprintf(plik_wy,"%d %d %d\n",wymx,wymy,szarosci);

  /* Zapisanie w pliku obrazu z tablicy */
  for (i=0;i<wymy;i++) {
    for (j=0;j<wymx;j++) {
      fprintf(plik_wy,"%d ",obraz_pgm[i][j]);
    }
    fprintf(plik_wy, "\n");
  }
  
  return wymx*wymy;
 }                       


/* Wyswietlenie obrazu o zadanej nazwie za pomoca programu "display"   */
void wyswietl(char *n_pliku) {
  char polecenie[DL_LINII];      /* bufor pomocniczy do zestawienia polecenia */

  strcpy(polecenie,"display ");  /* konstrukcja polecenia postaci */
  strcat(polecenie,n_pliku);     /* display "nazwa_pliku" &       */
  strcat(polecenie," &");
  printf("%s\n",polecenie);      /* wydruk kontrolny polecenia */
  system(polecenie);             /* wykonanie polecenia        */
}

void negatyw(int obraz_pgm[][MAX],int wymx, int wymy,int odcieni){
  int i, j;
  
  for (i = 0;i < wymy;i++) {
    for (j = 0;j < wymx;j++) {
      obraz_pgm[i][j] = odcieni - obraz_pgm[i][j]; /*zmiana wart na przeciwna wzgledem max wart*/
    }
  }
}

void progowanie(int obraz_pgm[][MAX],int wymx, int wymy,int odcieni){
  int i, j, prog = 101; /*zmienia obraz na czarno bialy,okreslamy ilosc procentowo*/

  while(prog < 0 || prog > 100){
    printf("w ilu procentach ma sie odbyc progowanie(od 0 do 100):\n");
    scanf("%d",&prog);
  }
  prog *=odcieni;
  prog /= 100;
  for (i = 0;i < wymy;i++) {
    for (j = 0;j < wymx;j++) {
     if (prog <  obraz_pgm[i][j])
       obraz_pgm[i][j] = odcieni;
     else
       obraz_pgm[i][j] = 0;
    }
  }
}

void zmiana_poziomow(int obraz_pgm[][MAX],int wymx, int wymy,int odcieni){
  int i,j, biel , czern; /*okreslamy procentowo ilsoc czarnego i bialego*/

  printf("Pamietaj, ze czern ma byc mniejsza niz biel ;)\n");
  do{
    printf("Podaj procentowo czern:\n");
    scanf("%d",&czern);
    printf("Podaj procentowo biel:\n");
    scanf("%d",&biel);
  }while((czern < 0) || (biel > 100) || (biel < czern));
  
  biel*=odcieni;                 /*zamieniamy wart procentowa na progi w zaleznosci od odcieni*/
  czern*=odcieni;
  biel/=100;
  czern/=100;

  for (i = 0;i < wymy;i++) {
   for (j = 0;j < wymx;j++) {
     if (obraz_pgm[i][j] <= czern)
       obraz_pgm[i][j] = 0;
     else if(obraz_pgm[i][j] >= biel)
       obraz_pgm[i][j] = odcieni;
     else
       obraz_pgm[i][j] = (obraz_pgm[i][j] - czern)*(odcieni/(biel - czern));
   }
  }
  
}

void konturowanie(int obraz_pgm[][MAX],int wymx, int wymy,int odcieni){
  int i,j,xp,yp;        /*xp,yp zmienne pomocnicze, przyjmujace wart dwoch pixeli*/
  int xt[MAX], yt[MAX]; /*xt,yt tablice pomocnicze, wart pierwszego wiersza i kolumny*/
                        /*potrzebne przy wartosciach granicznych*/
  for (i = 0;i < wymy;i++) { /*wart pierwszej kolumny do tab pomocniczej*/
    xt[i] = obraz_pgm[i][0];
  }
  for (j = 0;j < wymx;j++) {/*wart pierwszego wiersza do tab pomocniczej*/
    yt[j] = obraz_pgm[0][j];
  }
  
  for (i = 0;i < wymy;i++) {
    for (j = 0;j < wymx;j++) {
      if(i == wymy - 1){
	if(j == wymx - 1){
	  /*wartosc krancowo krancowa*/
	  yp = yt[j] - obraz_pgm[i][j];
	  xp = xt[i] - obraz_pgm[i][j];
	}else{
	  /*wart krancowa dolna*/
	  yp = yt[j] - obraz_pgm[i][j];
	  xp = obraz_pgm[i][j+1] - obraz_pgm[i][j];
	}
      }else if(j == wymx - 1){
	/*wart krancowa boczna*/
	yp = obraz_pgm[i+1][j] - obraz_pgm[i][j];
	xp = xt[i] - obraz_pgm[i][j];

      }else{
	/*wart w srodku*/
	yp = obraz_pgm[i+1][j] - obraz_pgm[i][j];
	xp = obraz_pgm[i][j+1] - obraz_pgm[i][j];
      }
      obraz_pgm[i][j] = ((xp<0?xp*(-1):xp)+(yp<0?yp*(-1):yp))/2;
    }
  }
}

void rozmywanie_poziome(int obraz_pgm[][MAX],int wymx, int wymy,int odcieni){
  int i, j, r, k; /*r-promien rozmycia, k-pomoc liczenie pix*/

  do{
    printf("Podaj promien rozmycia poziomego od 1 do %d:\n",wymy - 1);
     scanf("%d",&r);
  }while(r < 1 || r > wymy); 

  int tabpo[MAX][MAX+2*r]; /*tabpo-tablica pomocnicza, wartosci stale*/
  
  for (i = 0;i < wymy;i++){
    for (j = 0;j < wymx + 2*r;j++){
      if(j - r <= 0)/*pierwsze r kolumn wart takich jak 0 kolumna w obrazie*/
	tabpo[i][j] = obraz_pgm[i][0];
      else if(j - r >= wymx)/*ostatnie r kolumn takich jak ostatnia kolumna w obrazie*/
	tabpo[i][j] = obraz_pgm[i][wymx-1];
      else
	tabpo[i][j] = obraz_pgm[i][j-r];
    }
  }

   for (i = 0;i < wymy;i++) {
     for (j = 0;j < wymx;j++){
       obraz_pgm[i][j] = 0;
       for(k = 0; k <= 2*r; k++){ /*dodajemy do siebie wart r w tyl siebie i r do przodu*/
	 obraz_pgm[i][j] += tabpo[i][j+k]; 
       }
       obraz_pgm[i][j] /= 2*r+1;
     }
   }
 }

void rozciaganie_histogramu(int obraz_pgm[][MAX],int wymx, int wymy,int odcieni){
  int i, j, max, min;
  
  max = min = obraz_pgm[0][0];
  
  for (i = 0;i < wymy;i++) {
    for (j = 0;j < wymx;j++){
      max = (obraz_pgm[i][j] > max)?obraz_pgm[i][j]:max;
      min = (obraz_pgm[i][j] < min)?obraz_pgm[i][j]:min;
    }
  }
   for (i = 0;i < wymy;i++) {
    for (j = 0;j < wymx;j++){
      obraz_pgm[i][j] = (obraz_pgm[i][j] - min)*odcieni/(max - min);/*wzor na rozciaganie histogramu*/
    }
  }
}
