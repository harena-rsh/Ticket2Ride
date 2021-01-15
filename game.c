#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "clientAPI.h"
#include "TicketToRideAPI.h"
#include "main.h"
#include "route.h"

int main(){
  /*Définition des paramètres pour connectToServer*/
    printf("Les paramètres du jeu\n");
    char* serverName="li1417-56.members.linode.com";
    unsigned int port=5678; //Ou 5678 si 1234 ne marche pas
    char*botName="harena";

    connectToServer(serverName,port,botName);

  /*Définition des paramètres pour waitForT2RGame*/
    int Nb_cities;
    int Nb_tracks;
    char* gameType="TRAINING PLAY_RANDOM map=small";
    char* gameName=malloc(sizeof(50));
    int*p_nbCities=&Nb_cities;
    int*p_nbTracks=&Nb_tracks;


    waitForT2RGame(gameType,gameName,p_nbCities,p_nbTracks);

    /*Afficher les paramètres du jeu*/
    printf("nb_citie:%d\n",Nb_cities);
    printf("nb_tracks:%d\n",Nb_tracks);
    printf("game name: %d\n",*gameName);

    int*tracks=malloc(sizeof(int)*5*Nb_tracks);
    t_color faceUp[5];
    t_color cards[4];
    t_color*card=malloc(sizeof(t_color));
    int player=0;
    int replay=0;
    t_return_code coup=0;
    t_move move;
    t_color lastCard=NONE;
    int mesCartes[10];
    t_route route;
    t_route* tabRoutes[Nb_cities][Nb_cities];
    //afficheRoute(tabRoutes,0,5);
    /*Remplir le tableau des routes*/
    player=getMap(tracks, faceUp,cards); //Renvoie qui commence le jeu

    initTabRoutes(tabRoutes,Nb_cities);
    //afficheRoute(tabRoutes,Nb_cities);
    remplirTabRoutes(tabRoutes,tracks,Nb_tracks);
    //remplirRoute(tabRoutes,tracks,Nb_tracks,&route);

    /*tabRoutes[0][6]=(t_route*)malloc(sizeof(t_route));
    printf("%s",tabRoutes[0][6]);
    tabRoutes[0][6]->longeur=9;
    tabRoutes[0][6]->couleur1=9;
    tabRoutes[0][6]->couleur2=0;
    tabRoutes[0][6]->libre=0;*/
    afficheRoute(tabRoutes,Nb_cities);

    initCartes(cards,mesCartes);

    /*Boucle de jeu*/

    //do {
      /*Afficher la map*/
      /*if(!replay)
        printMap();*/

      /*L'adversaire joue*/
      /*if(player==1){
        t_move* move;
        coup = getMove(&move,&replay);
        printf("L'adversaire a joué: %d\n",&move->type);
        if(&move->type==1){
          MAJtabRoutes(tabRoutes,move->claimRoute.city1,move->claimRoute.city2);
        }
      }
      else {*/
        /*C'est à nous de jouer*/
        /*Cas où l'on joue manuellement*/
        /*askMove(&move);
        replay=needReplay(&move,lastCard);
        coup=playOurMove(&move, &lastCard);*/

        /* Joue automatiquement mais ne fait que piocher des cartes
        coup=drawBlindCard(card);
        coup=drawBlindCard(card);*/
      //}
      /*Change de joueur*/
      /*if(coup == NORMAL_MOVE && !replay)
        player=!player;
    } while (coup == NORMAL_MOVE);*/

    /*Qui gagne??*/
    /*if ((coup == WINNING_MOVE && player==0)||(coup == LOOSING_MOVE && player ==1))
      printf("We are the best!\n");
    else
      printf("We are loosers!\n");*/
    //affiche(tracks,5*Nb_tracks);

    free(tracks);
    free(gameName);
    free(card);
    closeConnection();
    return 0;

}
