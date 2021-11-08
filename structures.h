#ifndef STRUCTURES_H_INCLUDED
#define STRUCTURES_H_INCLUDED

typedef struct Partie{
    int id;
    int niveau;
    int dictonnaire;
	int taille_mot;
	char mot_a_trouver[10];
	char joueur[50];
	char mots_proposes[7][10];
	int nb_propos;
	double duree;
	int etat;
	int resultat;

} Partie;



#endif // STRUCTURES_H_INCLUDED

