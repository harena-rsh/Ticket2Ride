#include <stdio.h>
#include <stdlib.h>

int taille;
typedef struct {
  int longueur;
  int couleur1;
  int couleur2;
  int libre;
}t_route;

void affiche(t_route* tab[taille][taille],int taille){
  for(int i=0;i<taille;i++){
    for(int j=0;j<taille;j++){
      if(tab[i][j]!=NULL)
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",i,j,tab[i][j]->longueur,tab[i][j]->couleur1,tab[i][j]->couleur2,tab[i][j]->libre);
    }
  }
}


int main(){

/*Tableau à deux dimensions de pointeurs sur des routes*/
t_route* tabRoute[4][4];

/*Initialisation du tableau de route*/

for(int i=0;i<4;i++){
  for(int j=0;j<4;j++){
    tabRoute[i][j]=NULL;
  }
}

t_route route1;
/*Initialisation de route1*/
route1.longueur=5;
route1.couleur1=9;
route1.couleur2=0;
route1.libre=0;
/*On complete le tableau*/
tabRoute[0][0]=&route1;

affiche(tabRoute,4);


}
