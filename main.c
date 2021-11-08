#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fonctions.h"

int main()
{

    //Juste un test
    Partie * partie = initialiser_partie(MOYEN,FRANCAIS,7,"MANGEES","Dinyad");
    char  mot[10];
    interface_graphique(partie);
    while(partie->nb_propos!=6 && partie->resultat != GAGNE)
    {
        printf("Mot : ");
        scanf("%s",mot);

        if(strcmp(mot,partie->mot_a_trouver)==0)
        {
            partie->resultat=GAGNE;
            printf("Bravoooo !!");
        }

        strcpy(partie->mots_proposes[partie->nb_propos],mot);
        partie->nb_propos++;
        interface_graphique(partie);
    }



    return 0;

}
