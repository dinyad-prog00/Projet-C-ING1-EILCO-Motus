#ifndef STRUCTURES_H_INCLUDED
#define STRUCTURES_H_INCLUDED

//Structure definisant l'évolution du jeu.
//Utiliter essentiellement pour faire jouer l'ordi
typedef struct evolution {
	char mot_propose[10];
	int correspondance[10]; // 2 si existe et bien placée, 1 si existe et mal placéé et 0 si n'existe pas
	double tmp; // temps utilisé pour proposer le seul mot
} Evolution;


//Structure definisant une partie
typedef struct partie{
    int id;
    int niveau;
    int dictonnaire;
	int taille_mot;
	int type;
	char joueurs[2][50];
	char mot_a_trouver[10];
	char mots_proposes[7][10];
	int nb_propos;  // noombre de mots proposes
	int etat_lettres[10];  // 1 si trouvé, 0 sinon
	double duree;
	int etat;
	Evolution * evlts[COUP_MAX];
	int resultat;
	int help;
} Partie;





//Format de sauvegarge d'une partie dans un fichier

/*
id  niveau  dictionnaire    taille_mot  type  joueur1  joueur2
mot_a_rouve  nb_propos   duree   etat    resultat  help
etat_lettre
mot1    temp1
mot2    temp2
mot3    temp3
...      ...

*/

/*

Fonctions essentielles
---------------------
jouer ;
mot_aleatoire;
verifier_conrrespondance;
ordi_trouve_coup;





*/




#endif // STRUCTURES_H_INCLUDED

