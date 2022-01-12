#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "macros.h"
#include "structures.h"


#ifndef FONCTIONS_H_INCLUDED
#define FONCTIONS_H_INCLUDED

// Fonctions à écrire

Partie * initialiser_partie(int niveau, int dictionnaire,int type,int taille_mot,char * mot,char * joueur1,char * joueur2);


//Demander un mot à l'utilisateur
char * recuperer_mot(Partie * partie);


/*
    Verifie si le mot respecte les critères de mots valables
    Retourne 1 si c'est valide 0 sinon
*/
int valider(Partie * partie,char * mot);


/*
    Verifie si le mot proposé par le joueur correspond au mot a trouver
    Retourne 1 si c'est valide 0 sinon
*/
int verifier_correspondance(char * mot_propose,Partie * partie,double tmp);

//Convertir une chaine en minuscule
char * tolower_case(char * ch);


//Convertir une chaine en majuscule
char * to_upper_case(char * ch);


//Affiche les id des parties jouées par un joueur
void print_parties_joueur(char * joueur);

//Verifie si la partie qui a pour id <id> existe dans le fichier du joueur
int si_joue(char * joueur,int id);

//Sauvegarde une partie jouée
void sauvegarder_partie(Partie * partie );

//Charger une partie
Partie * charger_partie(int id);

//Liberer l'est aloué en memoire pour une partie
void free_partie(Partie * partie);

//Visualiser le deroulement d'une partie déjà jouée
void visualiser_une_partie(Partie * partie);

//Afficher le contenu d'un fichier sur console
void print(char *fichier);

//Netoyer la console
void clear_console();

//
void interface_graphique(Partie *partie);


int menu_principal();

//Recuperer le niveau
int get_niveau();

//Recuperer  le type de jeu
int get_type();

//Recuperer  la langue
int get_langue_dico();

//Recuperer le nom des joueurs
void get_joueurs(char ** j1, char ** j2,int type);

//Nombre aleatoire entre _min et _max
int nombre_aleatoire(int _min,int _max);

//Recuperer un mot aleatoire du dictionnaire
char * get_mot_aleatoire(int taille,int langue);

/*
    La fonction la plus importante du jeu
    Après l'initialisation de la partie, elle est envoyée à la cette fonction pour lancer le deroulement du jeu
*/
int jouer(Partie * partie);


/*
    Revèle une lettre supplementaire du mot a trouver sur demande du joueur
    Pour une partie, il a droit à 3 lettre
*/
void affiche1lettre(Partie * partie);


//Affiche le nombre de secondes depuis
double  nbActuelSecondes();


//La fonction utilser par l'ordinateur pour jouer
char * ordi_trouve_coup(Partie * partie);

//Stat
void statistique_partie(int id_partie);


//Statistique
void statistiques_globales(char * joueur);


#endif // FONCTIONS_H_INCLUDED
