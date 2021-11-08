#include "macros.h"
#include "structures.h"

#ifndef FONCTIONS_H_INCLUDED
#define FONCTIONS_H_INCLUDED

// Fonctions à écrire

char * mot_aleatoire(int dictonnaire) ;

int recuperer_niveau();

Partie * initialiser_partie(int niveau, int dictionnaire,int taille_mot,char * joueur, char * mot);

char * recuperer_mot(); //

int valider(char * mot);

int verifier_correspondance(char * mots_propose,void * partie);

void sauvegarder_partie(Partie * partie );

Partie * charger_partie(int id);

void print(char *fichier);

void interface_graphique(Partie *partie);

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
