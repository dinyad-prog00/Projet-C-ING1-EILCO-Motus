#include "macros.h"
#include "structures.h"

#ifndef FONCTIONS_H_INCLUDED
#define FONCTIONS_H_INCLUDED

// Fonctions à écrire

char * mot_aleatoire(int dictonnaire) ;

int recuperer_type_partie();// un joueur ou deux

int recuperer_niveau();

SousPartie * initialiser_spartie(char * mot); // continuer la partie

//void * initialiser_partie(int type); // initialisation des options,du type, partie de 10 mots à retrouver
PartieUnJoueur * initialiser_partie_un_joueur();
PartieDeuxJoueurs * initialiser_partie_2_joueurs();

char * recuperer_mot(); //

int valider(char * mot);

int verifier_correspondance(char * mots_propose,void * partie);

//void sauvegarder_partie(void * partie ,int type);

void sauvegarder_partie_deux_joueurs(PartieDeuxJoueurs * p);
void sauvegarder_partie_un_joueur(PartieUnJoueur * p);

//void * charger_partie(int id,int type);
PartieUnJoueur * charger_partie_un_joueur(int id);
PartieDeuxJoueurs * charger_partie_2_joueurs(int id);

void interface_graphique(void *partie,int type);

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
