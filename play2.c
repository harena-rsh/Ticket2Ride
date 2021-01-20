#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "clientAPI.h"
#include "TicketToRideAPI.h"
#include "main.h"
#include "route.h"

/*Créer une variable monJoueur pour savoir ce que j'ai en main*/
t_joueur monJoueur;
/*On va faire la supposition que je prends tous les objectifs qui me sont proposés*/
int objectiveCards[3]={1,1,1};
/*Boucle de jeu*/
do {
  /*Afficher la map*/
  if(!replay)
    printMap();

  /*L'adversaire joue*/
  if(player==1){
    t_move* move;
    coup = getMove(&move,&replay);
    printf("L'adversaire a joué: %d\n",&move->type);
    /*Si il claim une route, je rempli mon tableau de route pour savoir que cette route est prise*/
    if(&move->type==1){
      tabRoutes[move->claimRoute.city1][move->claimRoute.city2]->libre=1;
    }
  }
  else {
    /*C'est à nous de jouer*/
    /*Premier coup au moment où j'ai 0 objectifs*/
    if (monJoueur.nb_objectifs==0){
      drawObjectives(mesObjectifs);
      chooseObjectives(objectiveCards);
      /*Calculer ma liste de chemin à prendre*/
      co1=dijkstra_adapte(tabRoutes,mesObjectifs[0][0],mesObjectifs[0][1]);
      co2=dijkstra_adapte(tabRoutes,mesObjectifs[1][0],mesObjectifs[1][1]);
      co3=dijkstra_adapte(tabRoutes,mesObjectifs[2][0],mesObjectifs[2][1]);
    }
    /*Cas où l'on joue manuellement*/
    /*askMove(&move);
    replay=needReplay(&move,lastCard);
    coup=playOurMove(&move, &lastCard,tabRoutes,mesCartes);*/

    /* Joue automatiquement mais ne fait que piocher des cartes
    coup=drawBlindCard(card);
    coup=drawBlindCard(card);*/
  }
  /*Change de joueur*/
  if(coup == NORMAL_MOVE && !replay)
    player=!player;
} while (coup == NORMAL_MOVE);

/*Qui gagne??*/
if ((coup == WINNING_MOVE && player==0)||(coup == LOOSING_MOVE && player ==1))
  printf("We are the best!\n");
else
  printf("We are loosers!\n");
