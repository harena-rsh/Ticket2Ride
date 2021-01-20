#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "clientAPI.h"
#include "TicketToRideAPI.h"
#include "main.h"
#include "route.h"
#define IN 99
#define N 7
/*Dans cet exemple on a 6 noeuds soit 6 villes*/
/*Algorithme pour jouer:
** Etablir la liste des routes que l'on veut prendre
**On regrade si on a fini nos objectifs. Si oui on en prends de nouveau => Choose objectives
**Si on peut poser une route on la pose =>Claim route
Sinon on fait Draw card (si une carte nous interresse)
Sinon on fait Draw Blind Card*/

/*Affiche tab*/
void affichetab(int tab[],int taille){
  for(int i=0;i<taille;i++){
    printf("%d\t",tab[i]);
  }
}
/*Trouver le chemin le plus court entre deux villes*/

/*Algoithme de Dijkstra*/
//cost[][]: tableau du prix de chaque route, source+target: objectif qu'on veut remplir
int dijkstra(int cost[][N],int source,int target){
  int dist[N]={0};
  int prev[N]={0};
  int selected[N]={0};//dist: tableau de distance, prev: tableau des visités
  int i,m,min,start,d,j;
  int path[N]={0};

  /*Initialisation du tableau des distances*/
  for(i=0;i<N;i++){
    dist[i]=IN;
    prev[i]=-1;
  }
  start=source; //la ville de départ
  selected[start]=1;
  dist[start]=0;
  while(selected[target]==0){
    min=IN;
    m=0;
    for(i=0;i<N;i++){
      d=dist[start]+cost[start][i];
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
  affichetab(path,N);
  printf("\n");
  /*path[j]=;
  printf("%d\n",path);*/
  return dist[target];
}

int main(){
  int cost[N][N];
  int i,j,co;
  int source,target;
  printf("The Shortest Path Algorithm:\n");
  for(i=0;i<N;i++){
    for(j=0;j<N;j++){
      cost[i][j]=IN;
    }
  }
  /*Remplir le tableau de cost*/

  cost[1][2]=cost[2][1]=9;
  cost[1][3]=cost[3][1]=6;
  cost[1][4]=cost[4][1]=5;
  cost[2][3]=cost[3][2]=2;
  cost[2][5]=cost[5][2]=1;
  cost[3][5]=cost[5][3]=1;
  cost[5][6]=cost[6][5]=3;
  cost[4][6]=cost[6][4]=4;

  for (int i=0;i<N;i++){
    for(int j=0;j<N;j++){
      printf("%d\t",cost[i][j]);
    }
    printf("\n");
  }
  /*for(x=1;x<N;x++){
    for(y=1;y<N;y++){
      printf("Enter the weight of a path between nodes %d and %d\n",x,y);
      scanf("%d",&w);
      cost[x][y]=cost[y][x]=w;
    }
    printf("\n");
  }*/
  printf("Enter the source:\n");
  scanf("%d",&source);
  printf("Enter the destination\n");
  scanf("%d",&target);
  co=dijkstra(cost,source,target);
  printf("The Shortest path is: %d\n",co);
}
