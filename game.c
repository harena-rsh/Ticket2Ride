#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "clientAPI.h"
#include "TicketToRideAPI.h"
#include "main.h"
#include "route.h"

#define IN 99
#define NB_CITIES 100

int main(){
  /*Définition des paramètres pour connectToServer*/
    printf("Les paramètres du jeu\n");
    /*char* serverName="li1417-56.members.linode.com";
    unsigned int port=1234; //Ou 5678 si 1234 ne marche pas
    char*botName="playerOne";*/


    connectToServer("li1417-56.members.linode.com",1234,"playerOne");
    //while(1){
    /*Définition des paramètres pour waitForT2RGame*/
    int Nb_cities;
    int Nb_tracks;
    char* gameType="TRAINING PLAY_RANDOM map=USA";
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
    t_objective mesObjectifs[20];
    int objectiveCards[3]={1,1,0};
    t_joueur monJoueur;
    int nb_wagons=0;
    int couleur=0;
    int path[NB_CITIES];
    int path2[NB_CITIES];
    monJoueur.nb_wagons=45; //45wagons au début du jeu
    monJoueur.nb_cartes=4; //4 premières cartes distribuées
    monJoueur.nb_objectifs=0; //3 premiers qu'on nous donne
    monJoueur.cartes=mesCartes; //tableau de taille 9
    monJoueur.objectifs=mesObjectifs;
    /*Variable pour Dijkstra*/
    int i,j,w,ch,co1,co2,co3;
    int city1,city2;
    int city11,city22;
    int*p_city11=&city11;
    int*p_city22=&city22;
    int*p_city1=&city1;
    int*p_city2=&city2;
    t_objective obj[3];
    int longueurRoute=0;
    int couleurRoute=0;
    int longueurRoute1=0;
    int couleurRoute1=0;
    int indice2=0;
    int ok2=0;
    int indice=0;
    int ok=0;

    t_route* tabRoutes[NB_CITIES][NB_CITIES];
    /*Remplir le tableau des routes*/
    player=getMap(tracks, faceUp,cards); //Renvoie qui commence le jeu

    initTabRoutes(tabRoutes,NB_CITIES);
    remplirTabRoutes(tabRoutes,tracks,Nb_tracks);

    //afficheRoute(tabRoutes,Nb_cities);

    /*Vérification de Dijkstra en entrant une source et une destination*/
    /*printf("Enter the source:\n");
    scanf("%d",&source);
    printf("Enter the destination\n");
    scanf("%d",&target);
    co1=dijkstra_adapte(tabRoutes,source,target);
    printf("The Shortest path is: %d\n",co1);
    initCartes(cards,mesCartes);*/

    /*Boucle de jeu à la main*/

    do {
      /*Afficher la map*/
      if(!replay)
        printMap();

      /*L'adversaire joue*/
      if(player==1){
        t_move* move;
        coup = getMove(&move,&replay);
        printf("L'adversaire a joué: %d\n",&move->type);
        if(&move->type==1){
          tabRoutes[move->claimRoute.city1][move->claimRoute.city2]->libre=1;
          tabRoutes[move->claimRoute.city2][move->claimRoute.city1]->libre=1;
        }
      }
      else {
        /*C'est à nous de jouer*/
        /*Cas où l'on joue manuellement*/
        /*askMove(&move);*/
        if(monJoueur.nb_objectifs==0){
          coup=drawObjectives(obj);
          coup=chooseObjectives(objectiveCards);
          monJoueur.nb_objectifs=monJoueur.nb_objectifs+3;
          /*Récupération des objectifs que l'on vient de piocher dans monJoueur.objectifs*/
          monJoueur.objectifs[0]=obj[0];
          monJoueur.objectifs[1]=obj[1];
          monJoueur.objectifs[2]=obj[2];
          affiche_t_objectives(monJoueur.objectifs,3);
          /*Etablir la liste des routes à prendre*/
          //printf("%d\t%d\n",monJoueur.objectifs[0].city1,monJoueur.objectifs[0].city2);
          co1=dijkstra_adapte(tabRoutes,monJoueur.objectifs[0].city1,monJoueur.objectifs[0].city2,path);
          co2=dijkstra_adapte(tabRoutes,monJoueur.objectifs[1].city1,monJoueur.objectifs[1].city2,path2);
          //co3=dijkstra_adapte(tabRoutes,monJoueur.objectifs[2].city1,monJoueur.objectifs[2].city2,path3);
          //affichetab(path,NB_CITIES);
          /*On essai de gérer nos objectifs*/
          indice=routeAprendre(path,NB_CITIES,p_city1,p_city2,monJoueur.objectifs[0].city1);
          indice2=routeAprendre(path2,NB_CITIES,p_city11,p_city22,monJoueur.objectifs[1].city1);
          /*A ce stade on a la première route qu'il faut qu'on fasse pour ateindre notre objectif*/
          printf("city1:%d\n",*p_city1);
          printf("city2:%d\n",*p_city2);
          /*On récupère les données de cette route*/
          longueurRoute=tabRoutes[city1][city2]->longeur;
          couleurRoute=tabRoutes[city1][city2]->couleur1;
          if(couleurRoute==9){
            couleurRoute=5;
          }
          longueurRoute1=tabRoutes[city11][city22]->longeur;
          couleurRoute1=tabRoutes[city11][city22]->couleur1;
          if(couleurRoute1==9){
            couleurRoute1=5;
          }
        }
        else{
          if(ok2==1){
            majRouteAprendre(path2,NB_CITIES,p_city11,p_city22,path2[indice2-1]);
            longueurRoute1=tabRoutes[city11][city22]->longeur;
            couleurRoute1=tabRoutes[city11][city22]->couleur1;
            ok2=0;
            if(couleurRoute==9){
              couleurRoute=5;
            }
            coup=drawBlindCard(cards);
            mesCartes[*cards]++;
            monJoueur.nb_cartes++;
            //printf("couleur de la carte piochée:%d\n",*cards);
            coup=drawBlindCard(cards);
            mesCartes[*cards]++;
            monJoueur.nb_cartes++;

          }
          else if(ok==1){
            majRouteAprendre(path,NB_CITIES,p_city1,p_city2,path[indice-1]);
            longueurRoute=tabRoutes[city1][city2]->longeur;
            couleurRoute=tabRoutes[city1][city2]->couleur1;
            if(couleurRoute==9){
              couleurRoute=5;
            }
            ok=0;
            coup=drawBlindCard(cards);
            mesCartes[*cards]++;
            monJoueur.nb_cartes++;
            //printf("couleur de la carte piochée:%d\n",*cards);
            coup=drawBlindCard(cards);
            mesCartes[*cards]++;
            monJoueur.nb_cartes++;

          }

          else if((mesCartes[couleurRoute]==longueurRoute)&&(tabRoutes[city1][city2]->libre==0)){
            coup=claimRoute(city1,city2,couleurRoute,0);
            tabRoutes[city1][city2]->libre=1;
            tabRoutes[city2][city1]->libre=1;
            mesCartes[couleurRoute]=mesCartes[couleurRoute]-longueurRoute;
            ok=1;

          }
          /*else if((mesCartes[couleurRoute1]==longueurRoute1)&&(tabRoutes[city11][city22]->libre==0)){
            coup=claimRoute(city11,city22,couleurRoute1,0);
            tabRoutes[city11][city22]->libre=1;
            tabRoutes[city22][city11]->libre=1;
            mesCartes[couleurRoute1]=mesCartes[couleurRoute1]-longueurRoute1;
            ok2=1;

          }*/
          else if((mesCartes[5]==6)&&(tabRoutes[19][9]->libre==0)){
            coup=claimRoute(19,9,5,0);
            tabRoutes[19][9]->libre=1;
            tabRoutes[9][19]->libre=1;
            mesCartes[5]=mesCartes[5]-6;
          }
          else if((mesCartes[1]==6)&&(tabRoutes[19][28]->libre==0)){
            coup=claimRoute(19,28,1,0);
            tabRoutes[19][28]->libre=1;
            tabRoutes[28][19]->libre=1;
            mesCartes[1]=mesCartes[1]-6;
          }
          else if((mesCartes[3]==3)&&(tabRoutes[12][16]->libre==0)){
            coup=claimRoute(12,16,3,0);
            tabRoutes[12][16]->libre=1;
            tabRoutes[16][12]->libre=1;
            mesCartes[3]=mesCartes[3]-3;
          }
          else if((mesCartes[8]==5)&&(tabRoutes[22][27]->libre==0)){
            coup=claimRoute(22,27,8,0);
            tabRoutes[22][27]->libre=1;
            tabRoutes[27][22]->libre=1;
            mesCartes[8]=mesCartes[8]-5;
          }
          else if((mesCartes[3]==6)&&(tabRoutes[2][7]->libre==0)){
            coup=claimRoute(2,7,3,0);
            tabRoutes[2][7]->libre=1;
            tabRoutes[7][2]->libre=1;
            mesCartes[3]=mesCartes[3]-6;
          }
          else if((mesCartes[7]==4)&&(tabRoutes[11][16]->libre==0)){
            coup=claimRoute(11,16,7,0);
            tabRoutes[11][16]->libre=1;
            tabRoutes[16][11]->libre=1;
            mesCartes[7]=mesCartes[7]-4;
          }
          else if((mesCartes[6]==3)&&(tabRoutes[26][33]->libre==0)){
            coup=claimRoute(26,33,6,0);
            tabRoutes[26][33]->libre=1;
            tabRoutes[33][26]->libre=1;
            mesCartes[6]=mesCartes[6]-3;
          }
          else if((mesCartes[1]==4)&&(tabRoutes[34][35]->libre==0)){
            coup=claimRoute(34,35,1,0);
            tabRoutes[34][35]->libre=1;
            tabRoutes[35][34]->libre=1;
            mesCartes[1]=mesCartes[1]-4;
          }
          else if((mesCartes[8]==6)&&(tabRoutes[13][14]->libre==0)){
            coup=claimRoute(13,14,8,0);
            tabRoutes[13][14]->libre=1;
            tabRoutes[14][13]->libre=1;
            mesCartes[8]=mesCartes[8]-6;
          }
          else if((mesCartes[9]==6)&&(tabRoutes[10][20]->libre==0)){
            coup=claimRoute(10,20,9,0);
            tabRoutes[10][20]->libre=1;
            tabRoutes[20][10]->libre=1;
            mesCartes[9]=mesCartes[9]-6;
          }
          else if((mesCartes[1]==3)&&(tabRoutes[7][9]->libre==0)){
            coup=claimRoute(7,9,1,0);
            tabRoutes[7][9]->libre=1;
            tabRoutes[9][7]->libre=1;
            mesCartes[1]=mesCartes[1]-3;
          }
          else if((mesCartes[8]==5)&&(tabRoutes[2][3]->libre==0)){
            coup=claimRoute(2,3,8,0);
            tabRoutes[2][3]->libre=1;
            tabRoutes[3][2]->libre=1;
            mesCartes[8]=mesCartes[8]-5;
          }
          else if((mesCartes[7]==4)&&(tabRoutes[13][15]->libre==0)){
            coup=claimRoute(13,15,7,0);
            tabRoutes[13][15]->libre=1;
            tabRoutes[15][13]->libre=1;
            mesCartes[7]=mesCartes[7]-4;
          }
          else if((mesCartes[2]==3)&&(tabRoutes[28][29]->libre==0)){
            coup=claimRoute(28,29,2,0);
            tabRoutes[28][29]->libre=1;
            tabRoutes[29][28]->libre=1;
            mesCartes[2]=mesCartes[2]-3;
          }
          else if((mesCartes[6]==6)&&(tabRoutes[4][13]->libre==0)){
            coup=claimRoute(13,4,6,0);
            tabRoutes[13][4]->libre=1;
            tabRoutes[4][13]->libre=1;
            mesCartes[6]=mesCartes[6]-6;
          }
          else if((mesCartes[9]==4)&&(tabRoutes[8][9]->libre==0)){
            coup=claimRoute(9,8,9,0);
            tabRoutes[8][9]->libre=1;
            tabRoutes[9][8]->libre=1;
            mesCartes[9]=mesCartes[9]-4;
          }
          else if((mesCartes[4]==4)&&(tabRoutes[24][25]->libre==0)){
            coup=claimRoute(24,25,4,0);
            tabRoutes[24][25]->libre=1;
            tabRoutes[25][24]->libre=1;
            mesCartes[4]=mesCartes[4]-4;
          }
          else if((mesCartes[2]==4)&&(tabRoutes[21][28]->libre==0)){
            coup=claimRoute(21,28,2,0);
            tabRoutes[21][28]->libre=1;
            tabRoutes[28][21]->libre=1;
            mesCartes[2]=mesCartes[2]-4;
          }

          else{
            coup=drawBlindCard(cards);
            mesCartes[*cards]++;
            monJoueur.nb_cartes++;
            //printf("couleur de la carte piochée:%d\n",*cards);
            coup=drawBlindCard(cards);
            mesCartes[*cards]++;
            monJoueur.nb_cartes++;
            //printf("couleur de la carte piochée:%d\n",*cards);
            //coup=drawBlindCard(cards);
            //affiche_t_color(mesCartes,10);
          }
        /* Joue automatiquement mais ne fait que piocher des cartes
        coup=drawBlindCard(card);
        coup=drawBlindCard(card);*/
      }
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
    //affiche(tracks,5*Nb_tracks);

    //freeTabRoute(tabRoutes[NB_CITIES][NB_CITIES],NB_CITIES);
    free(tracks);
    free(gameName);
    free(card);

  //}
    closeConnection();
    return 0;

}
