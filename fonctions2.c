#include "fonctions.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


// Tafrize

int verifier_correspondance(char * mot_propose,Partie * partie,double tmp)
{
    Evolution * evlt = malloc(sizeof(Evolution));
    int i,j,retour = 1,present=0;
    char lettres[10]={0,0,0,0,0,0,0,0,0,0};
    int nb_occur_lettre[10],l=0,p=0;

    for(i=0;i<partie->taille_mot;i++)
    {
        for(j=0;j<l;j++)
        {
            if(lettres[j]==partie->mot_a_trouver[i])
            {
                nb_occur_lettre[j]++;
                p=1;
                break;
            }
        }

        if(p==0)
        {
            lettres[l]=partie->mot_a_trouver[i];
            nb_occur_lettre[l]=1;
            l++;
        }
        p=0;
    }

    strcpy(evlt->mot_propose,mot_propose);
    evlt->tmp =tmp;

    //Les biens placés
    for(i=0;i< partie->taille_mot;i++)
    {
        if(mot_propose[i] == partie->mot_a_trouver[i])
        {
            partie->etat_lettres[i]=1;
            evlt->correspondance[i]=2;

            for(j=0;j<l;j++)
            {
                if(lettres[j]==mot_propose[i])
                {
                    nb_occur_lettre[j]--;
                    break;
                }
            }

        }
    }

    //Sinon
    for(i=0;i< partie->taille_mot;i++)
    {
        if(mot_propose[i] != partie->mot_a_trouver[i])
        {

            for(j=0;j<partie->taille_mot;j++)
                if(mot_propose[i]==partie->mot_a_trouver[j])
                    present = 1;

            if(present)
            {
                for(j=0;j<l;j++)
                {
                    if(lettres[j]==mot_propose[i])
                    {
                        if(nb_occur_lettre[j]!=0)
                        {
                            evlt->correspondance[i]=1;
                            nb_occur_lettre[j]--;
                        }
                        else
                            evlt->correspondance[i]=0;

                        break;
                    }
                }

            }

            else
                evlt->correspondance[i]=0;
            retour=0;
        }

        present=0;
    }

    partie->evlts[partie->nb_propos]=evlt;
    return retour;
}
