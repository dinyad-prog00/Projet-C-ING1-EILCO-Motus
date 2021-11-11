#ifndef STRUCTURES_H_INCLUDED
#define STRUCTURES_H_INCLUDED

typedef struct partie{
    int id;
    int niveau;
    int dictonnaire;
	int taille_mot;
	char mot_a_trouver[10];
	char joueur[50];
	char mots_proposes[7][10];
	double tmp_proposes[7]; // temps de proposition d'un mot respectivement
	int nb_propos;
	double duree;
	int etat;
	int resultat;

} Partie;


//Format de sauvegarge d'une partie dans un fichier

/*
id  niveau  dictionnaire    taille_mot  joueur
mot_a_rouve  nb_propos   duree   etat    resultat
mot1    temp1
mot2    temp2
mot3    temp3
...      ...

*/




#endif // STRUCTURES_H_INCLUDED

