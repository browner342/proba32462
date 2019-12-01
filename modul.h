//Prototypy funkcji eksportowanych
#define MAX 512            /* Maksymalny rozmiar wczytywanego obrazu */
#define DL_LINII 1024      /* Dlugosc buforow pomocniczych */
#define KONIEC 99

int czytaj(FILE *plik_we,int obraz_pgm[][MAX],int *wymx,int *wymy, int *szarosci);
int wypis(FILE *plik_wy,int obraz_pgm[][MAX],int wymx,int wymy, int szarosci);
void wyswietl(char *n_pliku);
void negatyw(int obraz_pgm[][MAX],int wymx, int wymy,int odcieni);
void progowanie(int obraz_pgm[][MAX],int wymx, int wymy,int odcieni);
void zmiana_poziomow(int obraz_pgm[][MAX],int wymx, int wymy,int odcieni);
void konturowanie(int obraz_pgm[][MAX],int wymx, int wymy,int odcieni);
void rozmywanie_poziome(int obraz_pgm[][MAX],int wymx, int wymy,int odcieni);
void rozciaganie_histogramu(int obraz_pgm[][MAX],int wymx, int wymy,int odcieni);