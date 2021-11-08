#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "fonctions.h"

// Donatien
Partie * initialiser_partie(int niveau, int dictionnaire,int taille_mot,char * mot,char * joueur)
{
    Partie * partie = malloc(sizeof(Partie));
    if(partie!=NULL)
    {
        partie->id=1;
        partie->niveau = niveau;
        partie->dictonnaire = dictionnaire;
        partie->taille_mot = taille_mot;
        strcpy(partie->mot_a_trouver ,mot);
        strcpy(partie->joueur ,joueur);
        partie->nb_propos=0;
        partie->duree=0;
        partie->etat = NONFINIE;
        partie->resultat = NONGAGNE;

    }

    return partie;
}

void interface_graphique(Partie *partie)
{

    //Juste un test d'accès au champ
    printf("id : %d\nNiveau : %d\nJoueur : %s\nMot : %s\nMotPropse 1 : %s",partie->id,partie->niveau,partie->joueur,partie->mot_a_trouver,partie->mots_proposes[0]);
}
