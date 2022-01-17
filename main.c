#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "entetes.h"

int main()
{
    Partie * partie = NULL;
    int id,s;
    int continuer=1,niveau,type,langue_dico,choix;
    char * j1 =malloc(sizeof(char)*50),*j2=malloc(sizeof(char)*50), *mot,nom[50];


    while(continuer)
    {   clear_console();
        switch(menu_principal())
        {
            case 1 :
            //Jouer une nouvelle partie

                niveau = get_niveau();
                langue_dico = get_langue_dico();
                type = get_type();
                get_joueurs(&j1,&j2,type);
                DEBUT :
                    mot= get_mot_aleatoire(niveau+5,langue_dico);
                    partie = initialiser_partie(niveau,langue_dico,type,niveau+5,mot,j1,j2);
                    clear_console();
                    s=jouer(partie);
                    if(s==1)
                    {
                        free_partie(partie);
                        printf("\n\t\tEntrer 1 pour rejouer, 0 pour revenir au menu principal : ");
                        scanf("%d",&choix);
                        if(choix==1)
                            goto DEBUT;
                    }
                    else if(s==0)
                        continuer=0;



            break;
            case 2 :
            //Continuer une partie
                printf("\t\tVotre nom : ");
                scanf("%s",nom);
                print_parties_joueur(nom);
                printf("\t\tChoisissez un id : ");
                scanf("%d",&id);
                if(si_joue(nom,id))
                {
                    partie = charger_partie(id);
                    if(partie)
                    {
                        clear_console();
                        jouer(partie);
                    }
                }
                else
                {
                    printf("Mauvais choix");
                }


            break;
            case 3 :
            //Visualiser une partie
                printf("\t\tVotre nom : ");
                scanf("%s",nom);
                if(print_parties_joueur(nom))
                {
                    printf("\n\t\tLes parties récentes sont d'id plus elevé\n");
                    printf("\t\tChoisissez un id : ");
                    scanf("%d",&id);
                    if(si_joue(nom,id))
                    {
                        partie = charger_partie(id);
                        if(partie && partie->etat==FINIE)
                        {
                            clear_console();
                            visualiser_une_partie(partie);
                        }
                        else
                            printf("\n\t\t\033[5mVous ne pouvez pas visualiser une partie non achévée !!\033[0m");
                    }
                    else
                    {
                        printf("Mauvais choix");
                    }
                }
            break;

            case 4 :
            //Consulter statistiques
            printf("\t\tVotre nom : ");
            scanf("%s",nom);
            clear_console();
            print_file("entete.txt");
            printf("\n\n\n");
            statistiques_globales(nom);

            printf("\n\n\t\t\33[5m\33[32mEntrez pour continuer \033[0m\n");
            getchar();
            getchar();
            break;
            case 5 :
            printf("\nBYE !!");
            free(j1);
            free(j2);
            continuer=0;
            break;
        }
    }




    return 0;

}
