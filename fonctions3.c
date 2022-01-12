#include "fonctions.h"

// Amina

int valider(Partie * partie,char * mot)
{
    int i=0;
    //Contrainte de taille
    if( partie->taille_mot!=strlen(mot) )
        return 0;

    //La premiere lettre est respecté
    if(partie->mot_a_trouver[0]!=mot[0])
        return 0;

    //Pas de chiffre ou de caractères spéciaux ou d'accents
    for(i=0;i<partie->taille_mot;i++)
       if(mot[i]<'A' || mot[i]>'Z')
            return 0;

    //Déjà proposé
    for(i=0;i<partie->nb_propos;i++)
        if(strcmp(mot,partie->mots_proposes[i])==0)
            return 0;

    //Chaine bonne
    return 1;
}


char * recuperer_mot(Partie * partie)
{
    char * mot = malloc(sizeof(char)*11) ;
    printf("\n\t\tMot : ");
    scanf("%s",mot);
    if(mot[0]=='#')
        return mot;

    while(valider(partie,to_upper_case(mot)) != 1)
    {
        printf("\t\tMot non valide !\n\t\tNouveau mot : ");
        scanf("%s",mot);
        if(mot[0]=='#')
            return mot;
    }

    return to_upper_case(mot);
}



