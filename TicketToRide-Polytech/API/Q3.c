#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "clientAPI.h"
#include "TicketToRideAPI.h"
#include "main.h"

/*Programme qui remplit mon type stricturé t_joueur*/

/*Fonction qui affiche l'état actuel d'un joueur*/
void affiche_joueur(t_joueur*p_joueur){
  printf("nb wagons:%d\n",p_joueur->nb_wagons);
  printf("nb_cartes:%d\n",p_joueur->nb_cartes);
  printf("nb_objectifs:%d\n",p_joueur->nb_objectifs);
  //affiche_t_color(p_joueur->cartes,9);
  //affiche_t_objectives(p_joueur->objectifs,5);
}

void initCartes(t_color cards[],int cartes[]){
    int i=0;
    while(i<4){
    remplirCartes(cartes,cards);
    cards++;
    i++;
  }

  }
/*Fonction qui mets à jour le nombre de carte après chaque coup prendre une carte*/
void remplirCartes(int tab[],t_color* card){
  switch(*card){
    case NONE: tab[0]++;break;
  	case PURPLE: tab[1]++;break;
  	case WHITE:tab[2]++;break;
  	case BLUE: tab[3]++;break;
  	case YELLOW: tab[4]++;break;
  	case ORANGE:tab[5]++;break;
  	case BLACK: tab[6]++;break;
  	case RED:tab[7]++;break;
  	case GREEN:tab[8]++;break;
  	case MULTICOLOR:tab[9]++;break;
  }
}
