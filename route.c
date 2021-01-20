#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "clientAPI.h"
#include "TicketToRideAPI.h"
#include "main.h"
#include "route.h"
#define NB_CITIES 100
#define IN 99

int Nb_cities;
t_route route;
t_color color1;
t_color color2=NONE;
int k=0;


/*Dijkstra Algorithm*/
  int dijkstra(int tabLongueurRoute[Nb_cities][Nb_cities],int source,int target){
  int dist[Nb_cities];
  int prev[Nb_cities];
  int selected[Nb_cities];//dist: tableau de distance, prev: tableau des visités
  int i,m,min,start,d,j;
  int path[Nb_cities];

  /*Initialisation du tableau des distances*/
  for(i=0;i<Nb_cities;i++){
    dist[i]=IN;
    prev[i]=-1;
    selected[i]=0;
    path[i]=0;
  }
  start=source; //la ville de départ
  selected[start]=1;
  dist[start]=0;
  while(selected[target]==0){
    min=IN;
    m=0;
    for(i=0;i<Nb_cities;i++){
      d=dist[start]+tabLongueurRoute[start][i];
      if((d<dist[i])&&(selected[i]==0)){
        dist[i]=d;
        prev[i]=start;
      }
      if((min>dist[i])&&(selected[i]==0)){
        min=dist[i];
        m=i;
      }
    }
    start=m;
    selected[start]=1;
  }
  start=target;
  j=0;
  while(start!=-1){
    path[j++]=start;
    start=prev[start];
  }
  printf("Le chemin qu'il faut faire est:\n");
  affichetab(path,Nb_cities);
  printf("\n");
  return dist[target];
}
/*Tableau pour gérer les routes*/

/*== Créer la variable de type t_route pour chaque route
Pour la map USA on a 78routes*/
void initTabRoutes(t_route* tabRoutes[NB_CITIES][NB_CITIES],int Nb_cities){
  for(int i=0;i<Nb_cities;i++){
    for(int j=0;j<Nb_cities;j++){
        tabRoutes[i][j]=NULL;
      //tabRoutes[i][j]=malloc(sizeof(t_route));
    }
  }
}

/*Remplir le tableau de route*/
void remplirTabRoutes(t_route* tabRoutes[NB_CITIES][NB_CITIES],int* tracks, int nb_tracks){
  for(int i=0;i<5*nb_tracks;i=i+5){
      tabRoutes[tracks[i]][tracks[i+1]]=malloc(sizeof(t_route));
      tabRoutes[tracks[i+1]][tracks[i]]=malloc(sizeof(t_route));
      //tabRoutes[tracks[i]][tracks[i+1]]=&p_route;
      (tabRoutes[tracks[i]][tracks[i+1]])->longeur=tracks[i+2];
      (tabRoutes[tracks[i+1]][tracks[i]])->longeur=tracks[i+2];
      (tabRoutes[tracks[i]][tracks[i+1]])->couleur1=tracks[i+3];
      (tabRoutes[tracks[i+1]][tracks[i]])->couleur1=tracks[i+3];
      (tabRoutes[tracks[i]][tracks[i+1]])->couleur2=tracks[i+4];
      (tabRoutes[tracks[i+1]][tracks[i]])->couleur2=tracks[i+4];
      (tabRoutes[tracks[i]][tracks[i+1]])->libre=0;
      (tabRoutes[tracks[i+1]][tracks[i]])->libre=0;
      //printf("%d\t%d\t%d\t%d\n",tracks[i], tracks[i+1],tracks[i+2],tracks[i+3],tracks[i+4]);
    //printf("%d\t%d\t%d\n",i,tracks[i],tracks[i+1]);

  }
}
/*void afficheRoute(t_route* tabRoutes[Nb_cities][Nb_cities],int city1,int city2){
  printf("%d\t%d\t%d\t%d\n",tabRoutes[city1][city2]->longeur,tabRoutes[city1][city2]->couleur1,tabRoutes[city1][city2]->couleur2,tabRoutes[city1][city2]->libre);
}*/
/*Fonction qui affiche les détails d'une route*/
void afficheRoute(t_route* tabRoutes[NB_CITIES][NB_CITIES],int Nb_cities){
  for(int i=0;i<NB_CITIES;i++){
    for(int j=0;j<NB_CITIES;j++){
      if(tabRoutes[i][j]!=NULL){
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",i,j,tabRoutes[i][j]->longeur,tabRoutes[i][j]->couleur1,tabRoutes[i][j]->couleur2,tabRoutes[i][j]->libre);
      }
    }
  }
}

void affichetab(int tab[],int taille){
  for(int i=0;i<taille;i++){
    printf("%d\t",tab[i]);
  }
}
/*Fonction qui mets à jour le tableau des routes surtout le status de la route
On appelle cette fonction lorsqu'un joueur joue CLAIM_ROUTE*/
void freeTabRoute(t_route*tabRoutes[NB_CITIES][NB_CITIES],int taille){
  for(int i=0;i<taille;i++){
    for(int j=0;j<taille;j++){
      free(tabRoutes[i][j]);
    }
  }
}
void MAJtabRoutes(t_route* tabRoutes[NB_CITIES][NB_CITIES],int city1,int city2){
  tabRoutes[city1][city2]->libre=1;
}
