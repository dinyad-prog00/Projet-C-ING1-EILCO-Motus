#include <stdio.h>
#include <stdlib.h>
#include "fonctions.h"

int main()
{
    Partie * partie = initialiser_partie(MOYEN,FRANCAIS,7,"MANGEES","Dinyad");
    strcpy(partie->mots_proposes[0],"MANGUES");
    interface_graphique(partie);

    return 0;

}
