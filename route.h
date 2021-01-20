#ifndef _ROUTE_H_
#define _ROUTE_H_

#define NB_CITIES 100

typedef struct {
  int longeur;
  t_color couleur1;
  t_color couleur2;
  int libre; /*Si la route est libre 0 sinon 1*/
}t_route;



void remplirTabRoutes(t_route* tabRoutes[NB_CITIES][NB_CITIES],int* tracks, int nb_tracks);
void initTabRoutes(t_route* tabRoutes[NB_CITIES][NB_CITIES],int Nb_cities);
void afficheRoute(t_route* tabRoutes[NB_CITIES][NB_CITIES],int Nb_cities);
void MAJtabRoutes(t_route*  tabRoutesUSA[NB_CITIES][NB_CITIES],int city1,int city2);
//int dijkstra(int cost[NB_CITIES][NB_CITIES],int source,int target);
void affichetab(int tab[],int taille);
int dijkstra_adapte(t_route*tabRoutes[NB_CITIES][NB_CITIES],int source, int target,int path[NB_CITIES]);
int renvoieCouleur(int mesCartes[],int taille);
int majRouteAprendre(int path[],int NB_cities,int*city1,int*city2,int source);
void freeTabRoute(t_route*tabRoutes[NB_CITIES][NB_CITIES],int taille);
#endif
