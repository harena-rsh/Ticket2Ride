#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "clientAPI.h"
#include "TicketToRideAPI.h"
#include "main.h"
#include "route.h"
#define IN 999


int dijkstra_adapte(t_route*tabRoutes[NB_CITIES][NB_CITIES],int source, int target,int path[NB_CITIES]){ //On trouve source et target dans mon tableau d'objectifs
  int dist[NB_CITIES];
  int prev[NB_CITIES];
  int selected[NB_CITIES];//dist: tableau de distance, prev: tableau des visités
  int i,m,min,start,d,j;
  //int path[NB_CITIES]={0};

  /*Initialisation du tableau des distances*/
  for(i=0;i<NB_CITIES;i++){
    dist[i]=IN;
    prev[i]=-1;
    selected[i]=0;
    path[i]=IN; //J'initialise tout à 99 pour éviter les erreurs si la source de l'objectif est 0
  }
  start=source; //la ville de départ
  selected[start]=1;
  dist[start]=0;
  while(selected[target]==0){
    min=IN;
    m=0;
    for(i=0;i<NB_CITIES;i++){
      //printf("%d\n",i);
      //d=dist[start]+tabRoutes[start][i]->longeur;
      if(tabRoutes[start][i]!=NULL){
        d=dist[start]+tabRoutes[start][i]->longeur;
        if((d<dist[i])&&(selected[i]==0)){
          dist[i]=d;
          prev[i]=start;
        }
        if((min>dist[i])&&(selected[i]==0)){
          min=dist[i];
          m=i;
        }
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
  affichetab(path,NB_CITIES);
  printf("\n");
  return dist[target];
}

int routeAprendre(int path[],int Nb_cities,int*city1,int*city2,int source){
  int indice=0;
  for(int i=0;i<Nb_cities;i++){
    if(path[i]==source){
      *city1=path[i];
      *city2=path[i-1];
      indice=i;
    }
  }
  return indice;
}
/*A ce stade j'ai implicitement en retour de cette fonction le nombre de route que je dois prendre*/
int majRouteAprendre(int path[],int Nb_cities,int*city1,int*city2,int source){
  int indice=0;
  for(int i=0;i<Nb_cities;i++){
    if(path[i]==source){
      if(i!=0){
        *city1=path[i];
        *city2=path[i-1];
        indice=i;
      }
    }
  }
    return indice;
}

/*Fonction qui parcours mon tableau de cartes en main et qui donne l'indice de la couleur où on a le nb carte suffisant*/
int renvoieCouleur(int mesCartes[],int taille){
  int couleur=0;
  for(int i=0;i<taille;i++){
    if(mesCartes[i]==5){
      couleur=i;
    }
  }
  return couleur;
}
