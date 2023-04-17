#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int number_input = 0;
    int choice = 0;
    printf("Bienvenue à McDo mon ami =), choisissez votre menu!\n");
    
    while(choice == 0){
        printf("On vous propose les menus suivantes, en choissisez un! \n");
        printf("1.Royal Cheese\n2.Mc Deluxe\n3.Mc Bacon\n4.Big Mac\n");
        scanf("%d", &number_input);

        switch(number_input){
            case 1:
            printf("Vous avez choisi 1.Royal Cheese\n");
            choice = 1;
            break;

            case 2:
            printf("Vous avez choisi 2.Mc Deluxe\n");
            choice = 1;
            break;

            case 3:
            printf("Vous avez choisi 3.Mc Bacon\n");
            choice = 1;
            break;

            case 4:
            printf("Vous avez choisi 4.Big Mac\n");
            choice = 1;
            break;

            default:
            printf("Oops!, vous vous êtes trompé!, vous avez choisi %d\n",number_input);
            
        }
    }

    printf("You've entered the value %d =)\n", number_input);
    return 0;
}