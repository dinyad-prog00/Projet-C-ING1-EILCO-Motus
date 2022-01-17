#include "entetes.h"


//Inittialisation d'une partie
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

        // Evolution garde l'etat d'une ligne de la grille
        // Initialement la première lettre est revelée
        partie->evlts[0] = malloc(sizeof(Evolution));

        // première lettre revelée
        partie->evlts[0]->correspondance[0]=2;
        partie->evlts[0]->mot_propose[0]=partie->mot_a_trouver[0];
        partie->etat_lettres[0]=1;

        // Les autres cachées
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


/*
    La fonction la plus importante du jeu
    Après l'initialisation de la partie, elle est envoyée à la cette fonction pour lancer le deroulement du jeu
*/
int jouer(Partie * partie)
{
    char  *mot;
    int jr,tour=partie->nb_propos%2;
    int resp;
    double beginTimeG,endTimeG,beginTime,endTime;
    interface_graphique(partie);

    //On recupère l'heure de depart
    beginTimeG = nbActuelSecondes();

    //Tant que la partie n'est pas gagnée et le nombre de mots proposés est < 6
    while(partie->nb_propos!=6 && partie->resultat == NONGAGNE)
    {
        //L'heure de depart pour gerer le temps utilisé pour proposer un mot
        beginTime = nbActuelSecondes();
        if(partie->type == _1_JOUEUR)
        {
            printf("\t\t%s joue",partie->joueurs[0]);
            mot=recuperer_mot(partie);
            //L'heure de fin de proposition d'un mot
            endTime = nbActuelSecondes();

        }

        else if( partie->type == JOUEUR_ORDI)
        {
            if(tour == 0)
            {
                printf("\t\tTour de %s",partie->joueurs[0]);
                mot=recuperer_mot(partie);
                //L'heure de fin de proposition d'un mot
                endTime = nbActuelSecondes();
                tour=1;
            }
            else
            {
                strcpy(mot,ordi_trouve_coup(partie));
                endTime = nbActuelSecondes();
                printf("\t\tTour de l'ORDI => mot proposé : %s \n",mot);
                tour=0;
                sleep(4);
            }
        }
        else
        {
            if(tour == 0)
            {
                printf("\t\tTour de %s ",partie->joueurs[0]);
                mot=recuperer_mot(partie);
                //L'heure de fin de proposition d'un mot
                endTime = nbActuelSecondes();
                tour=1;
            }
            else
            {
                printf("\t\tTour de %s ",partie->joueurs[1]);
                mot=recuperer_mot(partie);
                //L'heure de fin de proposition d'un mot
                endTime = nbActuelSecondes();
                tour=0;
            }
        }

        //Reveler une lettre
        if(strcmp(to_upper_case(mot),"#H")==0)
        {
            if( partie->type==1 && partie->help )
                affiche1lettre(partie);
            else
                printf("\t\t\033[5mAide impossible !!\033[0m");

        }

        //quitter
        else if(strcmp(to_upper_case(mot),"#Q")==0)
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

        //save
        else if(strcmp(to_upper_case(mot),"#SV")==0)
        {
           sauvegarder_partie(partie);
            printf("\t\t\n               \033[5mPartie bien sauvegargée\033[0m");
            return 2;
        }

        //statistiques
        else if(strcmp(to_upper_case(mot),"#ST")==0)
        {
          if(partie->type==_1_JOUEUR)
            statistiques_globales(partie->joueurs[0]);
          else
          {
            if(tour==0)
            {
                jr=1;
                tour=1;
            }

            else
            {
                jr=0;
                tour=0;
            }


            statistiques_globales(partie->joueurs[jr]);
          }

           printf("Entrez pour continuer \n");
           getchar();
           getchar();

        }

        //règles du jeu
        else if(strcmp(to_upper_case(mot),"#RL")==0)
        {
            clear_console();
            print_file("RegleDujeu.txt");

            printf("\n\t\t\tFin\033[5m\t\t\tEntrez pour quitter !\033[0m\n");
            getchar();
            getchar();
        }

        else if(mot[0]=='#')
        {
            printf("\n\\t\tPas d'action associée !!\n");
        }


        else
        {
            // on verifie correspondance
            // endTime-beginTime : duree de proposition d'un mot (différente de  endTimeG - beginTimeG duree de la partie)
            if(verifier_correspondance(mot,partie,endTime-beginTime)==1)
            {

                if(partie->type==_1_JOUEUR)
                {
                    partie->resultat=GAGNE;
                }
                else
                {
                    if(tour==0)
                        partie->resultat=J2_GAGNE;
                    else
                        partie->resultat=J1_GAGNE;
                }
            }

            strcpy(partie->mots_proposes[partie->nb_propos],mot);
            partie->nb_propos++;
            getchar();


        }
        clear_console();
        interface_graphique(partie);

    }
    //On recupère l'heure de fin de partie
    endTimeG = nbActuelSecondes();
    partie->etat=FINIE;
    //On ajoute (au cas où ce serait une reprise de partie, sinon duree etait à 0)
    partie->duree += endTimeG - beginTimeG;

    if(partie->resultat==GAGNE)
    {

        printf("\033[5m\n\t\t\t\t#################\n\t\t\t\tBRAVOOOO !!! \n\t\t\t\t#################\033[0m \n\t\tPartie gagnée en %d coups.\n\t\tDurée : %lf secondes\n",partie->nb_propos,partie->duree);

    }
    else if(partie->resultat==J1_GAGNE)
    {

        printf("\033[5m\n\t\t\t\t#################\n\t\t\t\tBRAVOOOO %s !!! \n\t\t\t\t#################\033[0m \n\t\tPartie gagnée en %d coups.\n\t\tDurée : %lf secondes\n",partie->joueurs[0],partie->nb_propos,partie->duree);

        /*for(int i=0;i<COUP_MAX;i++)
            if(partie->evlts[i] !=NULL)
                printf("\n=> %f",partie->evlts[i]->tmp);*/
    }
    else if(partie->resultat==J2_GAGNE)
    {

        printf("\033[5m\n\t\t\t\t#################\n\t\t\t\tBRAVOOOO %s!!! \n\t\t\t\t#################\033[0m \n\t\tPartie gagnée en %d coups.\n\t\tDurée : %lf secondes\n",partie->joueurs[1],partie->nb_propos,partie->duree);

    }
    else
    {
        printf("\n\t\t\t\t#################\n\t\t\t\tPerdu !!! \n\t\t\t\t#################\033[0m \n\t\tDurée : %lf secondes\n",partie->duree);

        printf("\n\t\tLe mot était : %s \n\n",partie->mot_a_trouver);
    }

        printf("\n\t\tVoullez vous sauvegarder la partie?(0/1) : ");

        scanf("%d",&resp);
        if(resp==1)
        {
            sauvegarder_partie(partie);
            printf("\n\t\t\nPartie bien sauvegargée.");
        }



    return 1;

}





//Reveler une lettre, la première à droite non encore au rouge
void affiche1lettre(Partie * partie)
{
    Evolution * evlt  = malloc(sizeof(Evolution));
    int i;
    //On cherche la première à droite non encore au rouge
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



//Format de sauvegarge d'une partie dans un fichier

/*
id  niveau  dictionnaire    taille_mot  type  joueur1  joueur2
mot_a_rouve  nb_propos   duree   etat    resultat  help
etat_lettre
mot1    temp1
mot2    temp2
mot3    temp3
...      ...

Sauvegarde d'une partie */

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


//Rechargement

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



int verifier_correspondance(char * mot_propose,Partie * partie,double tmp)
{
    Evolution * evlt = malloc(sizeof(Evolution));
    int i,j,retour = 1,present=0;
    char lettres[10]={0,0,0,0,0,0,0,0,0,0};  // Va contienir les différents carectères du mot à trouver
    int nb_occur_lettre[10],l=0,p=0;  // Contient leurs nombres d'occurence respectivement

    //Replissage de lettre et nb_occur_lettre
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
    //Un bien placé est colorié au rouge (2) et son nb d'occurence est décrémenté
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
    //Présent et mal placé passe en jaune (1) si le nb d'occur > 0 et son nb d'occurence est décrémenté, blanc(0) sinon
    //Pas présent passe en blanc
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

    //On ajoute l'etat de ligne ainsi cléé au tableau d'evolutions
    partie->evlts[partie->nb_propos]=evlt;
    return retour;
}


//Stat
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


/*
    Verifie si le mot respecte les critères de mots valables
    Retourne 1 si c'est valide 0 sinon
*/
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


//Visualiser le deroulement d'une partie déjà jouée
void visualiser_une_partie(Partie * partie)
{
    int nb_propos = partie->nb_propos,i,tour=0;
    partie->nb_propos=0;

    for(i=0;i<nb_propos;i++)
    {
        free(partie->evlts[i]);
        partie->evlts[i]=NULL;
    }

    print_file("entete.txt");
    printf("\n\n\t\t\t\tVous voulez visualiser une partie.\n\033[32m\t\t\tTapez entrer pour commencer...\033[0m");
    getchar();
    getchar();
    while(partie->nb_propos != nb_propos)
    {
        clear_console();
        interface_graphique(partie);
        sleep(2);
        printf("\n\t\t\t%s \033[5m propose\033[0m : \033[32m%s\033[0m\n",partie->joueurs[tour%2],partie->mots_proposes[partie->nb_propos]);
        verifier_correspondance(partie->mots_proposes[partie->nb_propos],partie,0.0);
        sleep(4);

        partie->nb_propos++;
        if(partie->type != _1_JOUEUR)
            tour++;


        if(partie->nb_propos==nb_propos)
        {
            clear_console();
            interface_graphique(partie);
            printf("\n\t\tFin de partie !\n");
            if(partie->resultat==GAGNE)
            {

                printf("\n\t\tPartie gagnée en %d coups.\n\t\tDurée : %lf secondes\n",partie->nb_propos,partie->duree);

            }
            else if(partie->resultat==J1_GAGNE)
            {

                printf("\n\t\tPartie gagnée en %d coups par %s.\n\t\tDurée : %lf secondes\n",partie->nb_propos,partie->joueurs[0],partie->duree);

            }
            else if(partie->resultat==J2_GAGNE)
            {

                printf("\n\t\tPartie gagnée en %d coups par %s.\n\t\tDurée : %lf secondes\n",partie->nb_propos,partie->joueurs[1],partie->duree);

            }
            else
            {
                printf("\n\t\tPersonne n'avait gagné !!!\n\t\tDurée : %lf secondes\n",partie->duree);

                printf("\n\t\tLe mot était : %s \n\n",partie->mot_a_trouver);
            }

            printf("\n\n\t\t\033[32mEntrer pour quitter !\033[0m");
            getchar();
        }

    }


}

//Liberer l'est aloué en memoire pour une partie
void free_partie(Partie * partie)
{
    int i;

    for(i=0;i<partie->nb_propos;i++)
        if(partie->evlts[i]!=NULL)
            free(partie->evlts[i]);

    free(partie);

}

