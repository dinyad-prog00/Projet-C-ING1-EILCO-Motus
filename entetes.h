#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h> // Pour la fonction de pause sleep
#include "macros.h"
#include "structures.h"


#ifndef FONCTIONS_H_INCLUDED
#define FONCTIONS_H_INCLUDED


/////////////////////////////////////////////////////
//    Implémentées dans le fichier getters.c       //
/////////////////////////////////////////////////////

//Afficher le menu et recuperer un choix
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


//Demander un mot à l'utilisateur
char * recuperer_mot(Partie * partie);


// Fin getters
/////////////////////////////////////////////////////




/////////////////////////////////////////////////////
//    Implémentées dans le fichier fonctions.c     //
/////////////////////////////////////////////////////

//Initialiser une partie
Partie * initialiser_partie(int niveau, int dictionnaire,int type,int taille_mot,char * mot,char * joueur1,char * joueur2);


/*
    La fonction la plus importante du jeu
    Après l'initialisation de la partie, elle est envoyée à la cette fonction pour lancer le deroulement du jeu
*/
int jouer(Partie * partie);



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


//Sauvegarde une partie jouée
void sauvegarder_partie(Partie * partie );

//Charger une partie
Partie * charger_partie(int id);

//Liberer l'est aloué en memoire pour une partie
void free_partie(Partie * partie);

//Visualiser le deroulement d'une partie déjà jouée
void visualiser_une_partie(Partie * partie);


/*
    Revèle une lettre supplementaire du mot a trouver sur demande du joueur
    Pour une partie, il a droit à 3 lettre
*/
void affiche1lettre(Partie * partie);


//Stat
void statistique_partie(int id_partie);


//Statistique
void statistiques_globales(char * joueur);




// Fin focntions.c
/////////////////////////////////////////////////////



/////////////////////////////////////////////////////
//    Implémentées dans le fichier interface.c     //
/////////////////////////////////////////////////////

//Afficher le contenu d'un fichier sur console
void print_file(char *fichier);


//Les espace pour adaper la grille sellon la taille du mot
void print_espace(int taille);


//Afficher une ligne droite
void print_droite(int taille);

//Afficher une ligne vide
void print_vide(int taille);

//Afficher une ligne de la grille
void print_ligne(Evolution * evlt,int taille,char * mot_a_trouver);


//Netoyer la console
void clear_console();

//Interface graphque
void interface_graphique(Partie *partie);

//Fin interface.c
/////////////////////////////////////



/////////////////////////////////////////////////////
//    Implémentées dans le fichier ia.c     //
/////////////////////////////////////////////////////


//La fonction utilser par l'ordinateur pour jouer
char * ordi_trouve_coup(Partie * partie);

/*
 Verifie si le caractere etait deja proposé, present dans le mot mais mal placé
 On va supposer que l'ordi ne connait pas le mot  à trouver.
 Il va juste se baser sur l'evolution du jeu
*/
int presentSimple(Partie * partie, char c);




/*
    Verifie si le caractere est deja proposé mais non present dans le mont à trouver
    On va supposer que l'ordi ne connait pas le mot  à trouver.
    Il va juste se baser sur l'evolution du jeu
 */
int pasPresent(Partie * partie, char c);

/*
    Pour chaque mot, il determine le nombre de carecteres deja connus comme
     n'exisatnt pas dans le mot a trouver en se basant sur l'evolution du
*/
int nbPasPresent(Partie * partie,char * mot);

/*
    Pour chaque mot, il determine le nombre de carecteres bien place en se basant sur l'evolution du
*/
int nombre_correspondance(Partie * partie,char * mot,int *n);



//Verifie si le mot est deja propose
int deja_propose(char proposes[7][10],int nb_propos, char *mot);


//Fin ia.c
///////////////////////////////////////////////////


///////////////////////////////////////
//  LES AUXILIAIRES                    //
//////////////////////////////////////


//Fonction pour assurer l'attribution des id unique
//L'id est stocké dans un fichier id.txt et après lecture on écrase le contenu avec la valeur +1
int auto_incrementation();


////Donne le nombre de secondes écoulées depuis le 1er janvier 1970
double  nbActuelSecondes() ;

//Convertir une chaine en minuscule
char * tolower_case(char * ch);



//Convertir une chaine en majuscule
char * to_upper_case(char * ch);


//Sauvegarder d'id de la partie dans le fichier du joueur
void add_partie_joueur(char * joueur,int id);


//Affiche les id des parties jouées par un joueur
int print_parties_joueur(char * joueur);


//Verifie si la partie qui a pour id <id> existe dans le fichier du joueur
//Verifie si la partie était deja sauvegardee avant (reprise d'une partie)
int si_joue(char * joueur,int id);


#endif // FONCTIONS_H_INCLUDED
