#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Player
{
    int tentative ;
    char *incorrect_guesses;
}Player;


bool only_letters(const char *s);

int main(void) {

    char mot[15];
    char buffer[100];

    int erreurs_max;
    Player joueur2;
    joueur2.incorrect_guesses = malloc(erreurs_max * sizeof(char));


    do {
        printf("Entrer un mot (14 lettres, sans espaces ni chiffres) : ");
        fgets(mot, sizeof(mot), stdin);

        if (strlen(mot) == 1 ){
            continue;

        }
        mot[strcspn(mot, "\n")] = '\0';
        if (!only_letters(mot)) {
            printf("Erreur : le mot doit contenir uniquement des lettres.\n");
            continue;
        }
       
        break; 

    } while (1);

    do {
        printf("Entrer le nombre maximal d\'erreurs  : ");
        

        fgets(buffer, sizeof(buffer), stdin) ;

        erreurs_max = (int)strtol(buffer,NULL,10 );
        if (erreurs_max == 0) {
            printf("Erreur entrer un nombre positif.\n");
            continue;
        }
        joueur2.tentative = erreurs_max;
        break;

    } while (1);

    char *mot_copy ;
    int size = strlen(mot);
    memset(mot_copy, '-', size);
    mot_copy[size] = '\0'; 

    printf("%s" , mot_copy);

    // while (joueur2.tentative != 0){
    //     if 
    // }

    // bool result = verifier_tentative();

}

int afficher_progression(Player player){

    return player.tentative;
}


bool verifier_tentative(char guess , char* mot){
    char *ptr = mot;
    
    while((ptr = strchr(ptr , guess)) != NULL){
        printf("%c , %d" , guess , ptr - mot );
    }


}

bool only_letters(const char *s) {
    for (int i = 0; i < strlen(s); i++) {
        if (!isalpha(s[i]))
            return false ;
    }
    return true;
}