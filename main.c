#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fonctions.h"

int main()
{
    Partie * partie = NULL;
    int id;
    int continuer=1;

    //Juste un test
    while(continuer)
    {   clear_console();
        switch(menu())
        {
            case 1 :
                partie = initialiser_partie(MOYEN,FRANCAIS,7,"MANGEES","Dinyad");
                clear_console();
                jouer(partie);
            break;
            case 2 :

                printf("id : ");
                scanf("%d",&id);
                partie = charger_partie(id);
                if(partie)
                {
                    getchar();
                    visualiser_une_partie(partie);
                }
                else
                {
                    printf("Entrer pour continuer !");
                    getchar();
                    getchar();

                }
            break;
            case 3 :
            printf("\nBYE !!");
            continuer=0;
            break;
        }
    }




    return 0;

}
