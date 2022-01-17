#include "entetes.h"

/*
Envoie un nombre aleatoire entre _min et _max
Utile pour tirer un mot aleatoire du dico
*/
int nombre_aleatoire(int _min,int _max)
{
    static int first = 0;

    if (first == 0)
    {
      srand(time(NULL)); //pour passer la valeur du temps courant comme graine
      first = 1;
    }

    // rand revois nombre est compris entre 0 et RAND_MAX(maccro)
    //return rand()%(_max-_min+1) +_min;
    return (int)(rand() / (double)RAND_MAX * (_max-_min +1)) + _min;
}

////Recuperer mot aleatoire d'un dico
char * get_mot_aleatoire(int taille,int langue)
{
    char * mot = malloc(sizeof(char)*(taille+1));
    char dico[50],m[10];
    int rang_mot,rang=1;

    if(langue==FRANCAIS)
    {
        rang_mot=nombre_aleatoire(1,2260);
        sprintf(dico,"dico/francais_%d.txt",taille);
    }

    else
    {
        rang_mot=nombre_aleatoire(1,7930);
        sprintf(dico,"dico/anglais_%d.txt",taille);
    }

    FILE * file = fopen(dico,"r");
    while( !feof(file))
    {
        if(rang_mot == rang)
        {
            fscanf(file,"%s",mot) ;
            break;
        }
        else
        {
            fscanf(file,"%s",m) ;
            rang++;
        }
    }


    return mot;
}



char * recuperer_mot(Partie * partie)
{
    char * mot = malloc(sizeof(char)*11) ;
    printf("\n\t\tMot (taille %d) : ",partie->taille_mot);
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


//Afficher le menu principal
int menu_principal()
{
    int choix;

    print_file("menuprincipal.txt");
    printf("\33[32mVotre choix : \33[0m");
    scanf("%d",&choix);
    while(choix < 1 || choix > 5)
    {
        printf("\t\tMauvais choix !!!\n\t\tRechoisissez :");
        scanf("%d",&choix);
    }

    return choix;

}

//Recuperer le niveau
int get_niveau()
{
    int choix;

    clear_console();
    print_file("niveau.txt");
    printf("\33[32mVotre choix : \33[0m");
    scanf("%d",&choix);
    while(choix < 1 || choix > 4)
    {
        printf("\t\tMauvais choix !!!\n\t\tRechoisissez :");
        scanf("%d",&choix);
    }

    return choix;

}

//Recuperer le type de jeu ( seul, contre ordi ou a deux)
int get_type()
{
    int choix;
    clear_console();
    print_file("type.txt");
    printf("\33[32mVotre choix : \33[0m");
    scanf("%d",&choix);
    while(choix < 1 || choix > 3)
    {
        printf("\t\tMauvais choix !!!\n\t\tRechoisissez :");
        scanf("%d",&choix);
    }

    return choix;

}

//Recuperer le dico (anglai ou français)
int get_langue_dico()
{
    int choix;
    clear_console();
    print_file("langue.txt");
    printf("\33[32mVotre choix : \33[0m");
    scanf("%d",&choix);
    while(choix < 1 || choix > 2)
    {
        printf("\t\tMauvais choix !!!\n\t\tRechoisissez :");
        scanf("%d",&choix);
    }

    return choix;

}

/*
Recuperer le nom des joueurs ou du joueus,
Dans le cas d'un seul joueur, j2 est RIEN
*/
void get_joueurs(char ** j1, char ** j2,int type)
{
    clear_console();
    print_file("entete.txt");
    printf("\n\n                                    ");
    if(type == _1_JOUEUR )
    {
        printf("Nom du joueur : ");
        scanf("%s",*j1);
        strcpy(*j2,"RIEN");
    }
    else if ( type == JOUEUR_ORDI)
    {
        printf("Nom du joueur : ");
        scanf("%s",*j1);
        strcpy(*j2,"ORDI");
    }
    else
    {
        printf("Nom du joueur 1 : ");
        scanf("%s",*j1);
        printf("                                    Nom du joueur 2 : ");
        scanf("%s",*j2);
    }
}


