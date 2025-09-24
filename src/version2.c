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
bool verifier_tentative(char guess , char* mot, char* mot_copy);
char *choisir_mot_mystere();
int choisir_N_erreurs();

int main(void) {


    Player joueur;


    char *mot = choisir_mot_mystere();      
    char *mot_modifiable = malloc(strlen(mot) + 1);
    strcpy(mot_modifiable, mot);    
    printf("%s" , mot); 
    
    int erreurs_max = choisir_N_erreurs();
    printf("Vous avez %i tentatives" , erreurs_max);

    joueur.tentative = erreurs_max;



    joueur.incorrect_guesses = malloc(erreurs_max * sizeof(char));

    int size = strlen(mot);
    char *mot_copy = malloc((size + 1) * sizeof(char));
    memset(mot_copy, '-', size);
    mot_copy[size] = '\0'; 

    printf("%s\n" , mot_copy);

    while (joueur.tentative > 0 && strchr(mot_copy , '-') !=NULL ) {
        char guess;
        scanf(" %c", &guess);  
        joueur.tentative--;
        verifier_tentative(guess , mot, mot_copy);
        printf("%s\n" , mot_copy);

    }



    free(mot_copy);
    free(joueur.incorrect_guesses);
}

int afficher_progression(Player player){

    return player.tentative;
}


bool verifier_tentative(char guess , char* mot , char* mot_copy){
    char *ptr = mot;
    
    
    ptr = strchr(mot , guess);   
    if (ptr != NULL) {
        *ptr = '-';  
        mot_copy[(int) (ptr - mot )] = guess;

        return true;
        
    }
    else
        return false;

}

bool only_letters(const char *s) {
    for (int i = 0; i < strlen(s); i++) {
        if (!isalpha(s[i]))
            return false ;
    }
    return true;
}

char *choisir_mot_mystere(){

    char* liste_mots[] = { "bonjour", "maison", "papillon", "artisan",
    "ruelle", "ordinateur", "chocolat", "fromage", "jardin", "etoile",
    "nuages", "cyclone", "robotique", "escargot", "chameau", "probleme",
    "terrasse", "bonsoir", "biscuit", "catastrophe" } ;

    int random_int = rand() % (sizeof(liste_mots) / sizeof(liste_mots[0]));

    return liste_mots[random_int];
}


int choisir_N_erreurs() {

    return rand() % 20;

}