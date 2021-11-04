#ifndef STRUCTURES_H_INCLUDED
#define STRUCTURES_H_INCLUDED

/*
    Dans le projet une partie du jeu consiste essayer de trouver successivement 10 mots.
    Le fait d'essayer avec 7 propositions au maximun de trouver un mot est appelé sous partie.

*/
typedef struct sousPartie{
	char mot_a_trouver[10];
	char mots_proposes[7][10];
	int joueurs[7];
	int nb_propos;
	double duree;
	int etat;
	int resultat;
} SousPartie;

typedef struct partieUnJoeur
{
	int id;
	int niveau;
	char joueur[50];
	SousPartie sparties[10];
	int score;
	int dictonnaire;
	int taille_mot;
	int nb_sous_partie;
	double duree;
	int etat;
} PartieUnJoueur;

typedef struct partieDeuxJoueurs
{
	int id;
	int niveau;
	char joueurs[2][50];
	SousPartie sparties[11];
	int scores[2];
	int dictonnaire;
	int taille_mot;
	int nb_sous_partie;
	int tour;
	double duree;
	int etat;

} PartieDeuxJoueurs;



#endif // STRUCTURES_H_INCLUDED
