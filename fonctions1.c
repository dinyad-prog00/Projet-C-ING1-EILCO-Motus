#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h> // Pour la fonction de pause sleep
#include "fonctions.h"
#include <time.h>
#include <sys/time.h>

// Donatien


//Fonction pour assurer l'attribution des id unique
//L'id est stocké dans un fichier id.txt et après lecture on écrase le contenu avec la valeur +1
int auto_incrementation(){
    int n;
    FILE * f = fopen("id.txt","r");
    fscanf(f,"%d",&n);
    fclose(f);
    f = fopen("id.txt","w"); //Pour ecraser l'ancien id stocké
    fprintf(f,"%d",n+1);
    fclose(f);

    return n;

}

Partie * initialiser_partie(int niveau, int dictionnaire,int type,int taille_mot,char * mot,char * joueur1,char * joueur2)
{
    Partie * partie = malloc(sizeof(Partie));
    int i=0;
    if(partie!=NULL)
    {
        partie->id=auto_incrementation();
        partie->niveau = niveau;
        partie->dictonnaire = dictionnaire;
        partie->type = type;
        partie->taille_mot = taille_mot;
        strcpy(partie->mot_a_trouver ,mot);
        strcpy(partie->joueurs[0] ,joueur1);
        strcpy(partie->joueurs[1] ,joueur2);
        partie->nb_propos=0;
        partie->duree=0;
        partie->etat = NONFINIE;
        partie->resultat = NONGAGNE;
        if(type ==_1_JOUEUR)
            partie->help=3;
        else
            partie->help=0;

        partie->evlts[0] = malloc(sizeof(Evolution));

        // première lettre revelée
        partie->evlts[0]->correspondance[0]=2;
        partie->evlts[0]->mot_propose[0]=partie->mot_a_trouver[0];
        partie->etat_lettres[0]=1;

        for(i=1;i<partie->taille_mot;i++)
        {
             partie->evlts[0]->correspondance[i]=0;
             partie->evlts[0]->mot_propose[i]=0;
             partie->etat_lettres[i]=0;
        }



        for(i=1;i<COUP_MAX;i++)
            partie->evlts[i]=NULL;
    }

    return partie;
}


int jouer(Partie * partie)
{
    char  mot[10],tour=partie->nb_propos%2;
    int resp;
    double beginTimeG,endTimeG,beginTime,endTime;
    interface_graphique(partie);

    beginTimeG = nbActuelSecondes();
    while(partie->nb_propos!=6 && partie->resultat != GAGNE)
    {
        beginTime = nbActuelSecondes();
        if(partie->type == _1_JOUEUR)
        {
            printf("%s joue\nMot : ",partie->joueurs[0]);
            scanf("%s",mot);
            endTime = nbActuelSecondes();
        }

        else if( partie->type == JOUEUR_ORDI)
        {
            if(tour == 0)
            {
                printf("Tour de %s \nMot : ",partie->joueurs[0]);
                scanf("%s",mot);
                endTime = nbActuelSecondes();
                tour=1;
            }
            else
            {
                strcpy(mot,ordi_trouve_coup(partie));
                endTime = nbActuelSecondes();
                printf("Tour de l'ORDI => mot proposé : %s \n",mot);
                tour=0;
                sleep(4);
            }
        }
        else
        {
            if(tour == 0)
            {
                printf("Tour de %s \nMot : ",partie->joueurs[0]);
                scanf("%s",mot);
                endTime = nbActuelSecondes();
                tour=1;
            }
            else
            {
                printf("Tour de %s \nMot : ",partie->joueurs[1]);
                scanf("%s",mot);
                endTime = nbActuelSecondes();
                tour=0;
            }
        }

        if(strcmp(mot,"#help")==0)
        {
            if( partie->type==1 && partie->help )
                affiche1lettre(partie);
            else
                printf("\t\t\033[5mAide impossible !!\033[0m");

        }

        else if(strcmp(mot,"#quit")==0)
        {
            printf("\t\tVoullez vous sauvegarder la partie?(0/1) : ");
            int resp;
            scanf("%d",&resp);
            if(resp==1)
            {
                sauvegarder_partie(partie);
                printf("\t\t\nPartie bien sauvegargée.");
            }
            return 0;
        }

        else if(strcmp(mot,"#save")==0)
        {
           sauvegarder_partie(partie);
            printf("\t\t\n               \033[5mPartie bien sauvegargée\033[0m");
            return 2;
        }

        else if(strcmp(mot,"#stat")==0)
        {

        }

        else if(strcmp(mot,"#rules")==0)
        {

        }


        else
        {
            if(verifier_correspondance(mot,partie,endTime-beginTime)==1)
            {
                partie->resultat=GAGNE;
            }

            strcpy(partie->mots_proposes[partie->nb_propos],mot);
            partie->nb_propos++;
            getchar();

        }
        clear_console();
        interface_graphique(partie);

    }

    endTimeG = nbActuelSecondes();

    partie->duree = endTimeG - beginTimeG;

    if(partie->resultat==GAGNE)
    {
        printf("\033[5m\n\t\t\t\t#############\n\t\t\t\tBRAVOOOO !!! \n\t\t\t\t###########\033[0m \n\t\tPartie gagnée en %d coups.\n\t\tDurée : %lf secondes\n",partie->nb_propos,partie->duree);
        for(int i=0;i<COUP_MAX;i++)
            if(partie->evlts[i] !=NULL)
                printf("\n=> %f",partie->evlts[i]->tmp);
    }
    else
    {
        printf("\n\t\t\t\t#############\n\t\t\t\tPerdu !!! \n\t\t\t\t###########\033[0m \n\t\tDurée : %lf secondes\n",partie->duree);

        printf("\n\t\tLe mot était : %s \n\n",partie->mot_a_trouver);
    }

        printf("\t\tVoullez vous sauvegarder la partie?(0/1) : ");

        scanf("%d",&resp);
        if(resp==1)
        {
            sauvegarder_partie(partie);
            printf("\t\t\nPartie bien sauvegargée.");
        }



    return 1;

}



double  nbActuelSecondes()
{
    struct timeval tv;
    struct timezone tz;
    gettimeofday(&tv,&tz);
    return tv.tv_sec;
}



void affiche1lettre(Partie * partie)
{
    Evolution * evlt  = malloc(sizeof(Evolution));
    int i;
    for(i=0;i<partie->taille_mot;i++)
        if(partie->etat_lettres[i] !=1)
            break;
    partie->etat_lettres[i]=1;

    for(i=0;i<partie->taille_mot;i++)
        if(partie->etat_lettres[i]==1)
        {
            evlt->mot_propose[i]=partie->mot_a_trouver[i];
            evlt->correspondance[i]=2;
        }


    partie->evlts[partie->nb_propos]= evlt;
    partie->help--;

}
char * to_upper_case(char * ch)
{
    char * chaine = malloc(sizeof(char)*(strlen(ch)+1));
    int i;
    for(i=0;i<strlen(ch);i++)
        if('a' <=  ch[i] && ch[i] <= 'z')
            ch[i]='A'-'a'+ch[i];
    strcpy(chaine,ch);
    return chaine;
}

void add_partie_joueur(char * joueur,int id)
{
    char nom[50];
    sprintf(nom,"joueurs/%s",to_upper_case(joueur));
    FILE * file=fopen(nom,"a");
    fprintf(file,"%d\n",id);
    fclose(file);
}

void print_parties_joueur(char * joueur)
{
    char nom[50];
    int id;
    sprintf(nom,"joueurs/%s",to_upper_case(joueur));
    FILE * file=fopen(nom,"r");
    if(file)
    {
        printf("\t\tVoici les id des parties jouées :\n\t\t");
        while( !feof(file))
        {
            fscanf(file,"%d\n",&id);
            printf("%d   ",id);
        }
        printf("\n");
        fclose(file);
    }
    else
    {
        printf("\t\tAucune partie trouvée pour ce joueur !!");
    }

}

int si_joue(char * joueur,int id)
{
    char nom[50];
    int i;
    sprintf(nom,"joueurs/%s",to_upper_case(joueur));
    FILE * file=fopen(nom,"r");
    if(file)
    {

        while( !feof(file))
        {
            fscanf(file,"%d\n",&i);
            if(i==id)
            {
             fclose(file);
             return 1;
            }


        }

        fclose(file);

    }

    return 0;
}

void sauvegarder_partie(Partie * partie )
{
    char filename[100];
    int i;
    sprintf(filename,"parties/%d.txt",partie->id);
    FILE * file = fopen(filename,"w");
    if(file)
    {
       fprintf(file,"%d %d %d %d %d %s %s\n",partie->id,partie->niveau,partie->dictonnaire,partie->taille_mot,partie->type, partie->joueurs[0],partie->joueurs[1]);
       fprintf(file,"%s %d %lf %d %d %d\n",partie->mot_a_trouver,partie->nb_propos,partie->duree,partie->etat,partie->resultat,partie->help);

       for(i=0;i<partie->taille_mot;i++)
       {
            fprintf(file,"%d ",partie->etat_lettres[i]);
       }
       fprintf(file,"\n");

       for(i=0;i<partie->nb_propos;i++)
       {
        fprintf(file,"%s %lf\n",partie->evlts[i]->mot_propose,partie->evlts[i]->tmp);
       }

       fclose(file);

    }
    else
      printf("Erreur d'ouverture de fichier !");


    if(partie->type==_2_JOUEURS)
    {
        if(!si_joue(partie->joueurs[0],partie->id))
            add_partie_joueur(partie->joueurs[0],partie->id);

        if(!si_joue(partie->joueurs[1],partie->id))
            add_partie_joueur(partie->joueurs[1],partie->id);
    }
    else
        if(!si_joue(partie->joueurs[0],partie->id))
            add_partie_joueur(partie->joueurs[0],partie->id);


}


Partie * charger_partie(int id)
{
    Partie * partie = malloc(sizeof(Partie));
    if(partie)
    {
        char filename[100],mot[10];
        double tmp;
        int i,nb;
        sprintf(filename,"parties/%d.txt",id);
        FILE * file = fopen(filename,"r");
        if(file)
        {
           fscanf(file,"%d %d %d %d %d %s %s\n",&partie->id,&partie->niveau,&partie->dictonnaire,&partie->taille_mot,&partie->type, partie->joueurs[0],partie->joueurs[1]);
           fscanf(file,"%s %d %lf %d %d %d\n",partie->mot_a_trouver,&partie->nb_propos,&partie->duree,&partie->etat,&partie->resultat,&partie->help);

           for(i=0;i<partie->taille_mot;i++)
           {
                fscanf(file,"%d ",&partie->etat_lettres[i]);
           }
           nb=partie->nb_propos;
           partie->nb_propos=0;
           for(i=0;i<nb;i++)
           {
            fscanf(file,"%s %lf\n",mot,&tmp);

            strcpy(partie->mots_proposes[i],mot);
            verifier_correspondance(mot,partie,tmp);
            partie->nb_propos++;
           }

           fclose(file);



        }
        else{
            printf("Désolé ! Aucune partie sauvegardée n'a cet id!\n");
            return NULL;
        }

    }
    else
        printf("Erreur d'allocation mémoire !");

    return partie;
}

/*
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

*/

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


/*void print_entete(int taille)
{
    int i;
    printf("\n			#####");
    for(i=0;i<taille;i++)
        printf("######");

}*/

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
//Afficher une ligne vide de la grille
void print_droite(int taille)
{
    int i;
    print_espace(taille);
    printf("\033[34m");
    for(i=0;i<taille;i++)
        printf("______");
    printf("    \033[0m");
}
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

void print_ligne(Evolution * evlt,int taille)
{
    int i=0;
    if(evlt == NULL)
        print_vide(taille);
    else
    {
         print_droite(taille);

         print_espace(taille);
         printf("\033[34m|\033[0m");

        for(i=0;i<taille;i++)
        {
            if(evlt->correspondance[i]==2)
                printf("\033[31m  %c  \033[0m\033[34m|\033[0m",evlt->mot_propose[i]);
            else if(evlt->correspondance[i]==1)
                printf("\033[0;43m  %c  \033[0m\033[34m|\033[0m",evlt->mot_propose[i]);
            else if(evlt->mot_propose[i] != 0)
                printf("  %c  \033[34m|\033[0m",evlt->mot_propose[i]);
            else
                printf("     \033[34m|\033[0m");
        }
    }

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

    //printf("\n%s\n",partie->mot_a_trouver);
    print_file("entete.txt");

    for(int i=0 ;i< COUP_MAX;i++)
    {


        print_ligne(partie->evlts[i],partie->taille_mot);

    }

    print_droite(partie->taille_mot);


    print_file("pied.txt");

    printf("\n                        ______________________________________________________");
    printf("\n                        | \033[36m#help(%d)\033[0m: aide-moi  \033[36m#quit\033[0m: quitter  \033[36m#rules\033[0m: règles |",partie->help);
    printf("\n                        |    \033[36m#save\033[0m: sauvegarder       \033[36m#stat\033[0m: statistiques    |");
    printf("\n                        ______________________________________________________\n");

}


/*if(i< partie->nb_propos)
        {
            if(strcmp(partie->mots_proposes[i],partie->mot_a_trouver)==0)
                print_mot_succes(partie->mots_proposes[i],partie->mot_a_trouver);
            else
                print_mot(partie->mots_proposes[i],partie->mot_a_trouver);
        }

        else
             print_vide();*/


int menu_principal()
{
    int choix;

    print_file("menuprincipal.txt");
    printf("Votre choix : ");
    scanf("%d",&choix);
    while(choix < 1 || choix > 4)
    {
        printf("\t\tMauvais choix !!!\n\t\tRechoisissez :");
        scanf("%d",&choix);
    }

    return choix;

}

int get_niveau()
{
    int choix;

    clear_console();
    print_file("niveau.txt");
    printf("Votre choix : ");
    scanf("%d",&choix);
    while(choix < 1 || choix > 4)
    {
        printf("\t\tMauvais choix !!!\n\t\tRechoisissez :");
        scanf("%d",&choix);
    }

    return choix;

}
int get_type()
{
    int choix;
    clear_console();
    print_file("type.txt");
    printf("Votre choix : ");
    scanf("%d",&choix);
    while(choix < 1 || choix > 3)
    {
        printf("\t\tMauvais choix !!!\n\t\tRechoisissez :");
        scanf("%d",&choix);
    }

    return choix;

}

int get_langue_dico()
{
    int choix;
    clear_console();
    print_file("langue.txt");
    printf("Votre choix : ");
    scanf("%d",&choix);
    while(choix < 1 || choix > 2)
    {
        printf("\t\tMauvais choix !!!\n\t\tRechoisissez :");
        scanf("%d",&choix);
    }

    return choix;

}

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

//Faire jouer l'ordinateur

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
    int nb_max=0,nb=0,ps=0,ps_max=0;
    while( !feof(file))
    {
        fscanf(file,"%s",mot) ;
        //if(strncmp(mot,debut_mot,strlen(debut_mot)) == 0)
        //{
            nb=nombre_correspondance(partie,mot,&ps);
            if( deja_propose(partie->mots_proposes,partie->nb_propos,mot)==0 )
            {
                if(nb>nb_max)
                {
                    nb_max=nb;
                    ps_max=ps;
                    strcpy(coup_ordi,mot);
                }
                else if(nb==nb_max && ps > ps_max)
                {
                    nb_max=nb;
                    ps_max=ps;
                    strcpy(coup_ordi,mot);
                }

            }

        //}
        //else
        /*{
            strcpy(coup_ordi,"MANGUES");
             break;
        //}*/

    }

    printf("\n%d---%d\n",nb_max,ps_max);
    return coup_ordi;
}

