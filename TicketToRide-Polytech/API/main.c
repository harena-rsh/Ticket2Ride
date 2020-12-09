#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "clientAPI.h"
#include "TicketToRideAPI.h"
#include "main.h"

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
    //printMap();

    /*DEFINITON DE LA BOUCLE DU JEU*/
    t_return_code coup=0; //On le mets à 0 pour être sûr que dès le début on a 0 et on rentre dans la boucle de jeu.
    t_drawBlindCard blindcard;
    t_color*card=malloc(sizeof(t_color));
    t_move move;
    move.type=2;
    move.drawBlindCard= blindcard; //Initialisation de move
    t_move*p_move=&move;
    int replay=0; //bolean pour savoir si l'adversaire rejoue ou pas
    int*p_replay=&replay;
    t_objective obj[3];
    int tab_objectif[3]={1,0,0};

    /*Création et initialisation d'une variable t_joueur*/
    t_joueur moi;
    t_joueur* p_joueur=&moi;
    int carte[10]={0};//Comment on le remplit??? avec une fonction comme quand on affiche avec des cas
    t_objective objectifs[5];

    p_joueur->nb_wagons=45; //45wagons au début du jeu
    p_joueur->nb_cartes=4; //4 premières cartes distribuées
    p_joueur->nb_objectifs=0; //3 premiers qu'on nous donne
    p_joueur->cartes=carte; //tableau de taille 9
    p_joueur->objectifs=objectifs;

    /*Initialiser cartes avec les 4 premières cartes*/

    affiche_joueur(p_joueur);
      //Tant que ce n'est pas un WINNING_MOVE ou LOOSING_MOVE on reste dans la boucel
      /*On ne fait que tirer deux cartes dans la pioche par tour*/
      /*Pour tirer une carte on utilise drawBlindCard*/
      /*while(coup==0){
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
    }*/
    //drawObjectives(obj);
    //p_joueur->nb_objectifs++;
    affiche_t_objectives(obj,3);

    initCartes(cards,carte);
    affiche(carte,10);
    /*coup=drawBlindCard(card);
    affiche_t_color(card,1);
    remplirCartes(carte,card);
    coup=drawBlindCard(card);
    affiche_t_color(card,1);
    remplirCartes(carte,card);
    affiche(carte,10);*/

    coup=drawObjectives(obj);
    coup=chooseObjectives(tab_objectif);
    p_joueur->nb_objectifs++;
    affiche_t_objectives(obj,3);

    printMap();
    free(tracks);
    free(gameName);
    free(card);
  closeConnection();
  return 0;
}
