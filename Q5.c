#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "clientAPI.h"
#include "TicketToRideAPI.h"
#include "main.h"
#include "route.h"
/*Fonction qui demande à l'utilisateur de saisir le coup  qu'il veut jouer et qui joue le coup demandé*/
/*Pour tester et débbuger le programme*/


void askMove(t_move* move){
  /*Quel coup?*/
  printf("Choose a move\n");
  printf("1.claim a route\n");
  printf("2.draw a blind card\n");
  printf("3. draw a card\n");
  printf("4. draw objectives\n");
  printf("5.choose objectives\n");
  scanf("%d",&move->type);

  /*Détails pour chaque ret*/
  if(move->type == CLAIM_ROUTE){
    printf("Give city1,city2,color and number of locomotives:");
    scanf("%d %d %d %d",&move->claimRoute.city1,&move->claimRoute.city2,&move->claimRoute.color,&move->claimRoute.nbLocomotives);
  }
  else if (move->type==DRAW_CARD){
    printf("Give the color");
    scanf("%d",&move->drawCard.card);
  }
  else if (move->type==CHOOSE_OBJECTIVES){
    printf("For each objectives, give 0 or 1");
    scanf("%d %d %d",&move->chooseObjectives.chosen[0],&move->chooseObjectives.chosen[1],&move->chooseObjectives.chosen[2]);
  }
}

t_return_code playOurMove(t_move* move, t_color* lastCard){
  t_return_code ret;
  t_color cards[4];
  int mesCartes[10];
  int Nb_cities;
  t_route* tabRoutes[Nb_cities][Nb_cities];

  switch(move->type){
    case CLAIM_ROUTE:
      ret=claimRoute(move->claimRoute.city1,move->claimRoute.city2,move->claimRoute.color,move->claimRoute.nbLocomotives);
      MAJtabRoutes(tabRoutes,move->claimRoute.city1,move->claimRoute.city2);
      *lastCard= NONE;
      break;

    case DRAW_BLIND_CARD:
      ret=drawBlindCard(&move->drawBlindCard.card);
      remplirCartes(mesCartes, cards);
      *lastCard=(*lastCard==NONE)? move->drawBlindCard.card : NONE;
      break;

    case DRAW_CARD:
      ret=drawCard(move->drawCard.card,move->drawCard.faceUp);
      remplirCartes(mesCartes, cards);
      *lastCard=(*lastCard==NONE && move->drawCard.card!=MULTICOLOR)? move->drawCard.card:NONE;
      break;

    case DRAW_OBJECTIVES:
      ret=drawObjectives(move->drawObjectives.objectives);
      affiche_t_objectives(move->drawObjectives.objectives,3);
      *lastCard=NONE;
      break;

    case CHOOSE_OBJECTIVES:
      ret=chooseObjectives(move->chooseObjectives.chosen);
      *lastCard=NONE;
      break;
  }
  return ret;
}


int needReplay(t_move* move, t_color lastCard){
	int replay = 0;

	if (move->type == DRAW_OBJECTIVES)
		replay = 1;
	else if (move->type == DRAW_BLIND_CARD && lastCard == NONE)
		replay = 1;
	else if (move->type == DRAW_CARD && lastCard == NONE && move->drawCard.card != MULTICOLOR)
		replay = 1;

	return replay;
}

void affiche_t_objectives(t_objective tab[],int taille){
  printf("Les objectifs tirés sont:\n");
  for(int i=0;i<taille;i++){
    printf("%d\t",tab[i].city1);
    printf("%d\t",tab[i].city2);
    printf("%d\n",tab[i].score );
  }
}

void affiche(int tab[], int taille){
  for(int i=0;i<taille;i++){
    if ((i%5==0)&&(i!=0)){
      printf("\n");
      printf("%d\t",tab[i]);
    }
    else{
    printf("%d\t",tab[i]);
  }
  }
  printf("\n");
}

void affiche_t_color(t_color tab[], int taille){
  for(int i=0;i<taille;i++){
    printf("%d\n",tab[i]);
  }
  printf("\n");
}
