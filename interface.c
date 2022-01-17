#include "entetes.h"

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

//Les espace pour adaper la grille sellon la taille du mot
void print_espace(int taille)
{
    switch(taille)
    {
        case 6 :
            printf("\n    	                        ");
        break;
        case 7 :
            printf("\n    		             ");
        break;
        case 8 :
            printf("\n    		           ");
        break;
        case 9 :
            printf("\n    		        ");
        break;
    }
}



void print_droite(int taille)
{
    int i;
    print_espace(taille);
    printf("\033[34m");
    for(i=0;i<taille;i++)
        printf("______");
    printf("    \033[0m");
}

//Afficher une ligne vide de la grille
void print_vide(int taille)
{
    int i;
    print_droite(taille);

    print_espace(taille);
    printf("\033[34m|");
    for(i=0;i<taille;i++)
        printf("     |");

    printf("\033[0m");
}

//Afficher une ligne de la grille
void print_ligne(Evolution * evlt,int taille,char * mot_a_trouver)
{
    int i=0;
    if(evlt == NULL)
        print_vide(taille);
    else
    {
         print_droite(taille);

         print_espace(taille);
         printf("\033[34m|\033[0m");

         if(strcmp(evlt->mot_propose,mot_a_trouver)==0)
         {
            for(i=0;i<taille;i++)
                printf("\033[31m\033[5m  %c  \033[0m\033[34m|\033[0m",evlt->mot_propose[i]);
         }
        else
        {
            for(i=0;i<taille;i++)
            {
                if(evlt->correspondance[i]==2)
                    // \033[31m : couleur rouge
                    // \033[34m :c couleur bleue
                    // \033[0m : arreter l'effet de couleur pour la suite
                    printf("\033[31m  %c  \033[0m\033[34m|\033[0m",evlt->mot_propose[i]);
                else if(evlt->correspondance[i]==1)
                     // \033[0;43m : fond jaune
                    printf("\033[0;43m  %c  \033[0m\033[34m|\033[0m",evlt->mot_propose[i]);
                else if(evlt->mot_propose[i] != 0)
                    printf("  %c  \033[34m|\033[0m",evlt->mot_propose[i]);
                else
                    printf("     \033[34m|\033[0m");
            }
        }
    }

}


//Supprimer la console selon le SE
void clear_console()
{
    #if defined _WIN32
        //windows
        system("cls");
    #elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
        //Linux
        system("clear");
    #elif defined (__APPLE__)
        //Apple
        system("clear");
    #endif
}


//Affichage de l'interface graphique
void interface_graphique(Partie *partie)
{


    print_file("entete.txt");

    for(int i=0 ;i< COUP_MAX;i++)
    {


        print_ligne(partie->evlts[i],partie->taille_mot,partie->mot_a_trouver);

    }

    print_droite(partie->taille_mot);


    print_file("pied.txt");

    printf("\n                        ______________________________________________________");
    printf("\n                        | \033[36m#h(%d)\033[0m: aide-moi       \033[36m#q\033[0m: quitter       \033[36m#rl\033[0m: règles |",partie->help);
    printf("\n                        |    \033[36m#sv\033[0m: sauvegarder           \033[36m#st\033[0m: statistiques    |");
    printf("\n                        ______________________________________________________\n");

}






