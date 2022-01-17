#include "entetes.h"

/*
Le but des fonction suivante est de faire jouer l'ordinateur

*/

/*
 Verifie si le caractere etait deja proposé, present dans le mot mais mal placé
 On va supposer que l'ordi ne connait pas le mot  à trouver.
 Il va juste se baser sur l'evolution du jeu
*/

int presentSimple(Partie * partie, char c)
{
    int i,j;
    for(i=0;i<partie->nb_propos;i++)
    {
        for(j=0;j<partie->taille_mot;j++)
        {
            if(c==partie->evlts[i]->mot_propose[j] && partie->evlts[i]->correspondance[j]==1)
                return 1;
        }
    }

    return 0;
}

/*
    Verifie si le caractere est deja proposé mais non present dans le mont à trouver
    On va supposer que l'ordi ne connait pas le mot  à trouver.
    Il va juste se baser sur l'evolution du jeu
 */

int pasPresent(Partie * partie, char c)
{
    int i,j;
    for(i=0;i<partie->nb_propos;i++)
    {
        for(j=0;j<partie->taille_mot;j++)
        {
            if(c==partie->evlts[i]->mot_propose[j] && partie->evlts[i]->correspondance[j]==0)
                return 1;
        }
    }

    return 0;

}

/*
    Pour chaque mot, il determine le nombre de carecteres deja connus comme
     n'exisatnt pas dans le mot a trouver en se basant sur l'evolution du
*/
int nbPasPresent(Partie * partie,char * mot)
{
    int i,nb=0;
    for(i=0;i<partie->taille_mot;i++)
    {
        if(pasPresent(partie,mot[i]))
            nb++;
    }
    return nb;
}

/*
    Pour chaque mot, il determine le nombre de carecteres bien place en se basant sur l'evolution du
*/
int nombre_correspondance(Partie * partie,char * mot,int *n)
{
    int i,nb=0,m=0;
    for(i=0;i<partie->taille_mot;i++)
    {
        if(partie->etat_lettres[i]==1 && mot[i]==partie->mot_a_trouver[i])
        {
            nb++;
        }

        if(presentSimple(partie,mot[i]))
            m++;
    }
    *n=m;
    return nb;
}


//Verifie si le mot est deja propose
int deja_propose(char proposes[7][10],int nb_propos, char *mot)
{
    int i=0;
    for(i=0;i<nb_propos;i++)
    {
        if(strcmp(proposes[i],mot) == 0)
            return 1;
    }

    return 0;
}



//Utilise les fonctions precedentes pour trouver un coup intelligent pour l'ordinateur
char * ordi_trouve_coup(Partie * partie)
{
    char * coup_ordi = malloc(sizeof(char)*(partie->taille_mot+1)),* debut_mot = malloc(sizeof(char)*(partie->taille_mot+1));
    char mot[10] , fichier[50];
    int i;

    if(partie->dictonnaire==FRANCAIS)
        sprintf(fichier,"dico/francais_%d.txt",partie->taille_mot);

    else
        sprintf(fichier,"dico/anglais_%d.txt",partie->taille_mot);

    for(i=0;i<partie->taille_mot;i++)
        if(partie->etat_lettres[i]==1)
            debut_mot[i]=partie->mot_a_trouver[i];
        else
            break;
    debut_mot[i]='\0';


    FILE * file = fopen(fichier,"r");
    rewind(file);
    int nb_max=0,nb=0,ps=0,ps_max=0,nonp=0,nonp_min=10;
    while( !feof(file))
    {
        fscanf(file,"%s",mot) ;
        //if(strncmp(mot,debut_mot,strlen(debut_mot)) == 0)
        //{
            nb=nombre_correspondance(partie,mot,&ps);
            nonp=nbPasPresent(partie,mot);
            if( deja_propose(partie->mots_proposes,partie->nb_propos,mot)==0 )
            {
                if(nb>nb_max)
                {
                    nb_max=nb;
                    ps_max=ps;
                    nonp_min=nonp;
                    strcpy(coup_ordi,mot);
                }
                else if(nb==nb_max)
                {
                    if(ps>ps_max)
                    {
                        nb_max=nb;
                        ps_max=ps;
                        nonp_min=nonp;
                        strcpy(coup_ordi,mot);
                    }
                    else if(nonp < nonp_min)
                    {
                        nb_max=nb;
                        ps_max=ps;
                        nonp_min=nonp;
                        strcpy(coup_ordi,mot);
                    }

                }


            }
    }
    free(debut_mot);
    return coup_ordi;
}


