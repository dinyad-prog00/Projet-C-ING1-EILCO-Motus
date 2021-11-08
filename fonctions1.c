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


//Afficher le contenu d'un fichier sur console
void print_file(char *fichier)
{
    char chaine[TAILLE_MAX] ;
    FILE * file = fopen(fichier,"r");
    printf("\n") ;
    while( !feof(file))
    {
        fgets(chaine , TAILLE_MAX - 2 , file) ;
        printf("%s" , chaine) ;
    }

}

/*Afficher un mot proposé en respectant les contraintes de couleur
 Les chaines de type \033[Nm permettant de changer la couleur d'affichage de printf ; par exemple
 \033[34m bascule la couleur vers le blue et \033[0m ramème à la couleur par défaut
*/
void print_mot(char * mot,char * a_touver)
{
    int present=0;

    printf("\n			##   \033[34m___________________________________________    \033[0m##");
    printf("\n			     \033[34m|\033[0m");
    for(int i = 0; i<7;i++)
    {
        if(mot[i]==a_touver[i])
        {
            printf("\033[31m  %c  \033[0m\033[34m|\033[0m",mot[i]); //Lettre bien positionnée, affichage en rouge
        }
        else
        {
            for(int j=0;j<7;j++)
                if(mot[i]==a_touver[j])
                    present = 1;
            if(present)
                printf("\033[0;43m  %c  \033[0m\033[34m|\033[0m",mot[i]); //Mal positionnée, affichage en jaune
            else
                printf("  %c  \033[34m|\033[0m",mot[i]); // Non présent affichage par défaut
        }

        present=0;

    }

}


//Afficher une ligne vide de la grille
void print_vide()
{
    printf("\n			##   \033[34m___________________________________________    \033[0m##");
    printf("\n			     \033[34m|     |     |     |     |     |     |     |\033[0m");

}


void interface_graphique(Partie *partie)
{


    print_file("entete.txt");

    for(int i=0 ;i<6;i++)
    {
        if(i< partie->nb_propos)
            print_mot(partie->mots_proposes[i],partie->mot_a_trouver);
        else
             print_vide();

    }

    printf("\n			## \033[34m  -------------------------------------------\033[0m    ##");


    print_file("pied.txt");
}
