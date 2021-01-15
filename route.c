#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "clientAPI.h"
#include "TicketToRideAPI.h"
#include "main.h"
#include "route.h"

int Nb_cities;
t_route route;
t_color color1;
t_color color2=NONE;
int k=0;
/*Tableau pour gérer les routes*/

/*== Créer la variable de type t_route pour chaque route
Pour la map USA on a 78routes*/
void initTabRoutes(t_route* tabRoutes[Nb_cities][Nb_cities],int Nb_cities){
  for(int i=0;i<Nb_cities;i++){
    for(int j=0;j<Nb_cities;j++){
        tabRoutes[i][j]=NULL;
      //tabRoutes[i][j]=malloc(sizeof(t_route));
    }
  }
}

/*Remplir le tableau de route*/
void remplirTabRoutes(t_route* tabRoutes[Nb_cities][Nb_cities],int* tracks, int nb_tracks){
  for(int i=0;i<5*nb_tracks;i=i+5){
      tabRoutes[tracks[i]][tracks[i+1]]=malloc(sizeof(t_route));
      //tabRoutes[tracks[i]][tracks[i+1]]=&p_route;
      (tabRoutes[tracks[i]][tracks[i+1]])->longeur=tracks[i+2];
      (tabRoutes[tracks[i]][tracks[i+1]])->couleur1=tracks[i+3];
      (tabRoutes[tracks[i]][tracks[i+1]])->couleur2=tracks[i+4];
      (tabRoutes[tracks[i]][tracks[i+1]])->libre=0;
      //printf("%d\t%d\t%d\t%d\n",tracks[i], tracks[i+1],tracks[i+2],tracks[i+3],tracks[i+4]);
    //printf("%d\t%d\t%d\n",i,tracks[i],tracks[i+1]);

  }
}
/*void afficheRoute(t_route* tabRoutes[Nb_cities][Nb_cities],int city1,int city2){
  printf("%d\t%d\t%d\t%d\n",tabRoutes[city1][city2]->longeur,tabRoutes[city1][city2]->couleur1,tabRoutes[city1][city2]->couleur2,tabRoutes[city1][city2]->libre);
}*/
/*Fonction qui affiche les détails d'une route*/
void afficheRoute(t_route* tabRoutes[Nb_cities][Nb_cities],int Nb_cities){
  for(int i=0;i<Nb_cities;i++){
    for(int j=0;j<Nb_cities;j++){
      if(tabRoutes[i][j]!=NULL){
        printf("%d\t%d\t%d\t%d\t%d\n",i,j,tabRoutes[i][j]->longeur,tabRoutes[i][j]->couleur1,tabRoutes[i][j]->couleur2);
      }
    }
  }
}
/*Fonction qui mets à jour le tableau des routes surtout le status de la route
On appelle cette fonction lorsqu'un joueur joue CLAIM_ROUTE*/

void MAJtabRoutes(t_route* tabRoutesUSA[Nb_cities][Nb_cities],int city1,int city2){
  (tabRoutesUSA[city1][city2])->libre=1;
}
