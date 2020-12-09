#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "clientAPI.h"
#include "TicketToRideAPI.h"

void affiche_t_objectives(t_objective tab[],int taille){
  for(int i=0;i<taille;i++){
    printf("%d\t",tab[i].city1);
    printf("%d\t",tab[i].city2);
    printf("%d\n",tab[i].score );
  }
}

void affiche(int tab[], int taille){
  for(int i=0;i<taille;i++){
    printf("%d\t",tab[i]);
  }
  printf("\n");
}

void affiche_t_color(t_color tab[], int taille){
  for(int i=0;i<taille;i++){
    printf("%d\t",tab[i]);
  }
  printf("\n");
}

int main(){
/*J'essaie de démarrer une partie USA contre le bot DO_NOTHING, récupère les données et ferme la partie*/

/*Définition des paramètres pour connectToServer*/
  printf("Les paramètres du jeu\n");
  char* serverName="li1417-56.members.linode.com";
  unsigned int port=1234; //Ou 5678 si 1234 ne marche pas
  char*botName="harena";  //Ici on veut juste jouer contre DO_NOTHING

/*On a tous les arguments on peut se connecter au serveur*/
  connectToServer(serverName,port,botName);

  /*Débuter une partie*/
  /*Définition des paramètres pour waitForT2RGame*/
    int Nb_cities;
    int Nb_tracks;
    char* gameType="TRAINING DO_NOTHING map=USA start=0";
    char* gameName=malloc(sizeof(50));
    int*p_nbCities=&Nb_cities;
    int*p_nbTracks=&Nb_tracks;

    printf("game name: %d\n",*gameName);

  /*On appelle la fonction pour créer une partie*/
    waitForT2RGame(gameType,gameName,p_nbCities,p_nbTracks);

    printf("nb_citie:%d\n",Nb_cities);
    printf("nb_tracks:%d\n",Nb_tracks);

    /*On veut résupérer les données de la partie*/
    /*Définition des paramètres pour récupérer les données de la partie*/
    int*tracks=malloc(sizeof(int)*5*Nb_tracks);   //tableau de int d'une taille de 5fois le nombre de routes*/
    t_color faceUp[5];    //tableaus qui montre les cartes wagons à découvert
    t_color cards[4];     //tableau qui représente les 4 premières cartes dans ma main
    int start=0;    //Variable qui dit qui commence

    start=getMap(tracks, faceUp,cards);

    affiche_t_color(faceUp,5);
    affiche_t_color(cards,4);
    printf("%d\n",start);
    //affiche(tracks,5*Nb_tracks);
    /*Affiche la map pou voir l'évolution*/
    printMap();

    /*DEFINITON DE LA BOUCLE DU JEU*/
    t_return_code coup=0; //On le mets à 0 pour être sûr que dès le début on a 0 et on rentre dans la boucle de jeu.
    t_drawBlindCard blindcard;
    t_color*card=malloc(sizeof(t_color)*150);
    t_move move;
    move.type=2;
    move.drawBlindCard= blindcard; //Initialisation de move
    t_move*p_move=&move;
    int replay=0; //bolean pour savoir si l'adversaire rejoue ou pas
    int*p_replay=&replay;

      //Tant que ce n'est pas un WINNING_MOVE ou LOOSING_MOVE on reste dans la boucel
      /*On ne fait que tirer deux cartes dans la pioche par tour*/
      /*Pour tirer une carte on utilise drawBlindCard*/
      while(coup==0){
        coup=drawBlindCard(card);
        coup=drawBlindCard(card);
        coup=getMove(p_move,p_replay);
        coup=getMove(p_move,p_replay);
      }
      if(coup==1){
      printf("Vous avez gagné!\n");
      }
    else{
      printf("Vous avez perdu!Dommage!\n");
    }

    free(tracks);
    free(gameName);
    free(card);
  closeConnection();
  return 0;
}
