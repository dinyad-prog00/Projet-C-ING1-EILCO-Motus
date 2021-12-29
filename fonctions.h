#include "macros.h"
#include "structures.h"

#ifndef FONCTIONS_H_INCLUDED
#define FONCTIONS_H_INCLUDED

// Fonctions à écrire

char * mot_aleatoire(int dictonnaire) ;

int recuperer_niveau();

Partie * initialiser_partie(int niveau, int dictionnaire,int type,int taille_mot,char * mot,char * joueur1,char * joueur2);

char * recuperer_mot();

int valider(char * mot);

int verifier_correspondance(char * mot_propose,Partie * partie,double tmp);
char * tolower_case(char * ch);
void print_parties_joueur(char * joueur);
int si_joue(char * joueur,int id);
void sauvegarder_partie(Partie * partie );

Partie * charger_partie(int id);

void visualiser_une_partie(Partie * partie);

void print(char *fichier);
void clear_console();
void interface_graphique(Partie *partie);
int menu_principal();
int get_niveau();
int get_type();
int get_langue_dico();
void get_joueurs(char ** j1, char ** j2,int type);
int nombre_aleatoire(int _min,int _max);
char * get_mot_aleatoire(int taille,int langue);
int jouer(Partie * partie);

void affiche1lettre(Partie * partie);
double  nbActuelSecondes();

char * ordi_trouve_coup(Partie * partie);
 /*
if(type==0){
	PartieUnJoueur * p = (PartieUnJoueur *) partie;
}

else{
	PartieDeuxJoueurs * p = (PartieDeuxJoueur *) partie;

} */

void ajouter_mot_au_dic(char * mot,int dictonnaire);

void retirer_mot_du_dic(char *mot,int dictonnaire);

void statistique_partie(int id_partie);


void statistiques_globales();

int quitter();






#endif // FONCTIONS_H_INCLUDED
