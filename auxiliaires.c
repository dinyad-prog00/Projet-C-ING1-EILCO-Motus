#include <sys/time.h>
#include "entetes.h"


//Fonction pour assurer l'attribution des id unique
//L'id est stocké dans un fichier id.txt et après lecture on écrase le contenu avec la valeur +1
int auto_incrementation()
{
    int n;
    FILE * f = fopen("id.txt","r");
    fscanf(f,"%d",&n);
    fclose(f);
    f = fopen("id.txt","w"); //Pour ecraser l'ancien id stocké
    fprintf(f,"%d",n+1);
    fclose(f);

    return n;

}



//Donne le nombre de secondes écoulées depuis le 1er janvier 1970
double  nbActuelSecondes()
{
    struct timeval tv;
    struct timezone tz;
    gettimeofday(&tv,&tz);
    return tv.tv_sec;
}


//Majuscule
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
////Sauvegarder d'id de la partie dans le fichier du joueur
void add_partie_joueur(char * joueur,int id)
{
    char nom[50];
    sprintf(nom,"joueurs/%s",to_upper_case(joueur));
    FILE * file=fopen(nom,"a");
    fprintf(file,"%d\n",id);
    fclose(file);
}

//Affiche les id des parties jouées par un joueur
int print_parties_joueur(char * joueur)
{
    char nom[50];
    int id,s=0;
    sprintf(nom,"joueurs/%s",to_upper_case(joueur));
    FILE * file=fopen(nom,"r");
    if(file)
    {
        printf("\t\tVoici les id des parties jouées :\n\t\t");
        while( !feof(file))
        {
            fscanf(file,"%d\n",&id);
            printf("%d   ",id);
            s=1;
        }
        printf("\n");
        fclose(file);
    }
    else
    {
        printf("\t\t\033[5mAucune partie trouvée pour ce joueur !!\033[0m");
    }
    return s;
}


//Verifie si la partie était deja sauvegardee avant (reprise d'une partie)
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



