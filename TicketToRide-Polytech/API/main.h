#ifndef _MAIN_H_
#define _MAIN_H_

/*Création des types structurés pour suivre l'évolution du jeu*/
/*Structure t_joueur pour suivre les cartes d'un joueur avec :
  ==nombre de wagons disponibles
  ==nombre de cartes en main
  ==nombre d'objectifs
  ==un tableau des cartes en main (contient mes cartes en main)
  ==un tableau d'objectifs avec le type t_objectifs pas plus de 5objectifs (contient mes objectifs)*/

typedef struct {
  int nb_wagons;
  int nb_cartes;
  int nb_objectifs;
  t_color*cartes; //on a 10 couleurs et on utilise le même code couleur que dans TicketToRide cartes[1] pour les purples,...
  t_objective* objectifs;
}t_joueur;

/*Structure t_partie pour suivre les données de la partie avec:
  ==joueur qui est en train de jouer
  ==mon numéro de t_joueur
  ==carte face visible
  ==plateau de jeu
  ==tableau de deux joueurs*/
typedef struct {
  int joueur_actuel;
  int mon_joueur;
  t_color visible[5]; //Toujours 5 cartes visibles
  t_joueur joueurs[2];
} t_partie;

/*Fonction qui affiche les infos sur un joueur*/
void affiche_joueur(t_joueur*p_joueur);
void initCartes(t_color cards[],int cartes[]);
/*Fonction qui remplit le tableau des cartes en main*/
void remplirCartes(int tab[],t_color*card);

#endif
