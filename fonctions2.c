#include "fonctions.h"



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

void statistiques_globales(char * joueur)
{
    int nbpartie_finie=0,nbpartie=0,nbp1j=0,nbp2j=0,nbpordi=0,nbgagner=0,nbcoup_max=0,nbcoup_min=6,tmp_max=0,tmp_min=10000;
    char nom[50];
    Partie * partie=NULL;
    int id;
    sprintf(nom,"joueurs/%s",to_upper_case(joueur));
    FILE * file=fopen(nom,"r");
    if(file)
    {

        while( !feof(file))
        {
            fscanf(file,"%d\n",&id);
            partie = charger_partie(id);
            //Nombre de parties
            nbpartie++;
            //Nombre de parties finies
            if(partie->etat==FINIE)
            {

                nbpartie_finie++;

                //Nombre de partie de type 1 joueur
                if(partie->type == _1_JOUEUR)
                    nbp1j++;

                //Nombre de partie de type 2 joueur
                if(partie->type == _2_JOUEURS)
                    nbp2j++;

                //Nombre de partie de type contre ordi
                if(partie->type == JOUEUR_ORDI)
                    nbpordi++;

                //Nombre de coups max
                if(partie->resultat == GAGNE || ( partie->resultat!=NONGAGNE && strcmp(to_upper_case(joueur), to_upper_case(partie->joueurs[partie->resultat-2]))==0))
                {
                    if( partie->nb_propos > nbcoup_max)
                        nbcoup_max=partie->nb_propos;

                    //Nombre de coups min
                    if(partie->nb_propos < nbcoup_min)
                        nbcoup_min=partie->nb_propos;


                    //Temps max
                    if(partie->duree > tmp_max)
                        tmp_max=partie->duree;

                    //Temps min
                    if( partie->duree < tmp_min)
                        tmp_min=partie->duree;
                }
            }



        }

        fclose(file);



        ////
        printf("\n\t\tNombre de parties total  : %d ",nbpartie);
        printf("\n\t\tNombre de parties finies : %d\n ",nbpartie_finie);
        if(nbpartie_finie != 0)
        {
            printf("\n\t\tStat sur les parties finies");
            printf("\n\t\t_________________________________________");
            printf("\n\t\tNombre de parties jouées seul : %d ",nbp1j);
            printf("\n\t\tNombre de parties jouées à deux : %d ",nbp2j);
            printf("\n\t\tNombre de parties jouées contre l'ordinateur : %d ",nbpordi);
            printf("\n\t\tNombre de parties gagnées : %d \n",nbgagner);
            if(nbgagner!=0)
            {
                printf("\n\t\tNombre de coups Max : %d ",nbcoup_min);
                printf("\n\t\tNombre coups Min : %d ",nbcoup_min);
                printf("\n\t\tTemps Max : %d secondes ",tmp_max);
                printf("\n\t\tTemps Min : %d  secondes",tmp_min);
            }
        }

    }
    else
    {
        printf("\t\tAucune partie trouvée pour ce joueur !!");
    }
}
