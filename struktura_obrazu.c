#include <stdio.h>
typedef sturct{
        int wym_x, wym_y,odcieni;
        void *piksele;
    } st_obraz;

int czytaj(FILE *plik_we, st_obraz *obraz){
    int i,j;
        ...
        fscanf(plik_we,"%d", &(obraz->wym_x));
      /* analogicznie wym_y *//* rezerwujemy odpowiednio duza tablice */
      obraz->piksele = malloc(obraz->wym_x*obraz->wym_y*sizeof(int));
      /* dopiero teraz definiujemy zmienna pomocnicza jako wskaznik na tablice */
      /* o znanych wymiarach, tylko przez nia bedziemy sie odwolywac do pola   */
      int (*piksele)[obraz->wym_x];          /* piksele w strukturze z obrazem */
      piksele=(int(*)[obraz->wym_x]) obraz->piksele; /*inicjujemy go jak trzeba*/
      for(i = 0; i < obraz->wym_y; i++)            /* i dzialamy!!! */
        for(j = 0; j < obraz->wym_x; j++)
            fscanf(plik_we, "%d", &(piksele[i][j]));
}
int main(){
    


}