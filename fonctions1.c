#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h> // Pour la fonction de pause sleep
#include "fonctions.h"

// Donatien


//Fonction pour assurer l'attribution des id unique
int auto_inclementation(){
    int n;
    FILE * f = fopen("id.txt","r");
    fscanf(f,"%d",&n);
    fclose(f);
    f = fopen("id.txt","w"); //Pour ecraser l'ancien id stocké
    fprintf(f,"%d",n+1);
    fclose(f);

    return n;

}

Partie * initialiser_partie(int niveau, int dictionnaire,int taille_mot,char * mot,char * joueur)
{
    Partie * partie = malloc(sizeof(Partie));
    if(partie!=NULL)
    {
        partie->id=auto_inclementation();
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

void jouer(Partie * partie)
{
    char  mot[10];
    interface_graphique(partie);
    while(partie->nb_propos!=6 && partie->resultat != GAGNE)
    {
        printf("Mot : ");
        scanf("%s",mot);

        if(strcmp(mot,partie->mot_a_trouver)==0)
        {
            partie->resultat=GAGNE;
        }

        strcpy(partie->mots_proposes[partie->nb_propos],mot);
        partie->nb_propos++;
        clear_console();
        interface_graphique(partie);
    }

    if(partie->resultat==GAGNE)
    {
        printf("\033[5m\n\t\t\t\t#############\n\t\t\t\tBRAVOOOO !!! \n\t\t\t\t###########\033[0m \n\t\tPartie gagnée en %d coups.\n\t\tDuréé : %lf secondes\n",partie->nb_propos,partie->duree);
        printf("\t\tVoullez vous sauvegarder la partie?(0/1) : ");
        int resp;
        scanf("%d",&resp);
        if(resp==1)
        {
            sauvegarder_partie(partie);
            printf("\t\t\nPartie bien sauvegargée.");
        }
    }
}



void sauvegarder_partie(Partie * partie )
{
    char filename[100];
    sprintf(filename,"parties/%d.txt",partie->id);
    FILE * file = fopen(filename,"w");
    if(file)
    {
       fprintf(file,"%d %d %d %d %s\n",partie->id,partie->niveau,partie->dictonnaire,partie->taille_mot,partie->joueur);
       fprintf(file,"%s %d %lf %d %d\n",partie->mot_a_trouver,partie->nb_propos,partie->duree,partie->etat,partie->resultat);
       for(int i=0;i<partie->nb_propos;i++)
       {
        fprintf(file,"%s %lf\n",partie->mots_proposes[i],partie->tmp_proposes[i]);
       }

       fclose(file);

    }
    else
      printf("Erreur d'ouverture de fichier !");


}

Partie * charger_partie(int id)
{
    Partie * partie = malloc(sizeof(Partie));
    if(partie)
    {
        char filename[100];
        sprintf(filename,"parties/%d.txt",id);
        FILE * file = fopen(filename,"r");
        if(file)
        {
           fscanf(file,"%d %d %d %d %s",&partie->id,&partie->niveau,&partie->dictonnaire,&partie->taille_mot,partie->joueur);
           fscanf(file,"%s %d %lf %d %d",partie->mot_a_trouver,&partie->nb_propos,&partie->duree,&partie->etat,&partie->resultat);
           for(int i=0;i<partie->nb_propos;i++)
           {
            fscanf(file,"%s %lf",partie->mots_proposes[i],&partie->tmp_proposes[i]);
           }

           fclose(file);

        }
        else{
            printf("Désolé ! Aucune partie jouée n'a cet id!\n");
            return NULL;
        }

    }
    else
        printf("Erreur d'allocation mémoire !");

    return partie;
}

void visualiser_une_partie(Partie * partie)
{
    int nb_propos = partie->nb_propos;
    partie->nb_propos=0;

    printf("\nVous voulez visualiser une partie.\nTapez entrer pour commencez...");
    getchar();
    while(partie->nb_propos != nb_propos)
    {
        clear_console();
        interface_graphique(partie);
        printf("%s \033[5m propose\033[0m : \033[34m%s\033[0m\n",partie->joueur,partie->mots_proposes[partie->nb_propos]);
        sleep(4);

        partie->nb_propos++;


        if(partie->nb_propos==nb_propos)
        {
            clear_console();
            interface_graphique(partie);
            printf("\t\tFin de partie !\n\t\tEntrer pour quitter !");
            getchar();
        }

    }


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


//Afficher en le clignontant
void print_mot_succes(char * mot,char * a_touver)
{


    printf("\n			##   \033[34m___________________________________________    \033[0m##");
    printf("\n			     \033[34m|\033[0m");
    for(int i = 0; i<7;i++)
    {

        printf("\033[31m\033[5m  %c  \033[0m\033[34m|\033[0m",mot[i]);

    }


}


//Afficher une ligne vide de la grille
void print_vide()
{
    printf("\n			##   \033[34m___________________________________________    \033[0m##");
    printf("\n			     \033[34m|     |     |     |     |     |     |     |\033[0m");

}

void clear_console()
{
    #if defined _WIN32
        system("cls");
    #elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
        system("clear");
    #elif defined (__APPLE__)
        system("clear");
    #endif
}

void interface_graphique(Partie *partie)
{


    print_file("entete.txt");

    for(int i=0 ;i<6;i++)
    {
        if(i< partie->nb_propos)
        {
            if(strcmp(partie->mots_proposes[i],partie->mot_a_trouver)==0)
                print_mot_succes(partie->mots_proposes[i],partie->mot_a_trouver);
            else
                print_mot(partie->mots_proposes[i],partie->mot_a_trouver);
        }

        else
             print_vide();

    }

    printf("\n			## \033[34m  -------------------------------------------\033[0m    ##");


    print_file("pied.txt");
}

int menu()
{
    int choix;

    print_file("menuprincipal.txt");
    printf("Votre choix : ");
    scanf("%d",&choix);
    while(choix < 1 || choix > 3)
    {
        printf("\t\tMauvais choix !!!\n\t\tRechoisissez :");
        scanf("%d",&choix);
    }

    return choix;

}

