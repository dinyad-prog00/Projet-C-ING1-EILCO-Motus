#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fonctions.h"

int main()
{
    Partie * partie = NULL;
    int id,s;
    int continuer=1,niveau,type,langue_dico,choix;
    char * j1 =malloc(sizeof(char)*50),*j2=malloc(sizeof(char)*50), *mot,nom[50];

    //Juste un test
    while(continuer)
    {   clear_console();
        switch(menu_principal())
        {
            case 1 :

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
                        printf("\t\tEntrer 1 pour rejouer, 0 pour revenir au menu principal : ");
                        scanf("%d",&choix);
                        if(choix==1)
                            goto DEBUT;
                    }
                    else if(s==0)
                        continuer=0;



            break;
            case 2 :
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
                printf("\t\tVotre nom : ");
                scanf("%s",nom);
                print_parties_joueur(nom);
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
                    printf("\n\t\tVous ne pouvez pas visualiser une partie non achévée !!");
                }
                else
                {
                    printf("Mauvais choix");
                }

                /*printf("id : ");
                scanf("%d",&id);
                partie = charger_partie(id);
                if(partie)
                {
                                    //visualiser_une_partie(partie);
                }
                else
                {
                    printf("Entrer pour continuer !");
                    getchar();
                    getchar();

                }*/
            break;
            case 4 :
            printf("\nBYE !!");
            free(j1);
            free(j2);
            continuer=0;
            break;
        }
    }




    return 0;

}
