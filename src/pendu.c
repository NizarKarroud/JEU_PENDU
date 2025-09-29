#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>

#define MAX_UNIQUE 256
#define N 5

typedef struct prob_pair
{
   char lettre ;
   float probability;
}Tuple;

void print_banner(void);
void prepare_list(char list[][20], int size);
bool verifier_tentative(char *mot_mystere , char guess , int index);
int compare_func(const void *a, const void *b) ;

void compute_frequencies(char list[][20], int size, float freq_matrix[MAX_UNIQUE][MAX_UNIQUE], int char_freq[MAX_UNIQUE]);
void compute_probabilities(float freq_matrix[MAX_UNIQUE][MAX_UNIQUE], int char_freq[MAX_UNIQUE], float prob_matrix[MAX_UNIQUE][MAX_UNIQUE]);

int main() {

    srand(time(NULL));
    char list[N][20] = {"apple", "banana", "cherry" , "grapes" , "oranges"};

    int random_index = rand() % N ;

    char *random_word = list[random_index];
    int nombre_tentative = (rand() %  10 ) + strlen(random_word) ;

    printf("%s\n" , random_word);
    printf("%i\n" , nombre_tentative);

    float prob_matrix[MAX_UNIQUE][MAX_UNIQUE];
    float freq_matrix[MAX_UNIQUE][MAX_UNIQUE];

    int char_freq[MAX_UNIQUE] ;
    memset(prob_matrix, 0, sizeof(prob_matrix));
    memset(freq_matrix, 0, sizeof(freq_matrix));
    memset(char_freq, 0, sizeof(char_freq));


    print_banner();

    prepare_list(list,N );


    compute_frequencies(list, N, freq_matrix, char_freq);
    compute_probabilities(freq_matrix, char_freq, prob_matrix);


    for (int i = 0; i < MAX_UNIQUE; i++) {
        Tuple list_of_prob_for_given_char[MAX_UNIQUE];
        int count = 0;  

        for (int j = 0; j < MAX_UNIQUE; j++) {
            if (prob_matrix[i][j] != 0.0f) {
                list_of_prob_for_given_char[count].lettre = (char)j;  
                list_of_prob_for_given_char[count].probability = prob_matrix[i][j];
                count++;
            }
        }

        if (count > 0) {
            qsort(list_of_prob_for_given_char, count, sizeof(Tuple), compare_func);

            printf("Probabilities for '%c':\n", (char)i);
            for (int k = 0; k < count; k++) {
                printf("  %c -> %c : %f\n", 
                    (char)i, 
                    list_of_prob_for_given_char[k].lettre, 
                    list_of_prob_for_given_char[k].probability);
            }
            printf("\n");
        }
    }


    return 0;
}

            //     printf("%c is followed by %c with a prob of %f\n",
            //         i,
            //         list_of_prob_for_given_char[j].lettre,
            //         list_of_prob_for_given_char[j].probability);


void compute_frequencies(char list[][20], int size, float freq_matrix[MAX_UNIQUE][MAX_UNIQUE], int char_freq[MAX_UNIQUE]) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < strlen(list[i]); j++) {
            char c = list[i][j];
            char_freq[c]++;
            if (j + 1 < strlen(list[i])) {
                char next_char = list[i][j + 1];
                freq_matrix[c][next_char]++;
            }
        }
    }
}

void compute_probabilities(float freq_matrix[MAX_UNIQUE][MAX_UNIQUE], int char_freq[MAX_UNIQUE], float prob_matrix[MAX_UNIQUE][MAX_UNIQUE]) {
    for (int i = 0; i < MAX_UNIQUE; i++) {
        for (int j = 0; j < MAX_UNIQUE; j++) {
            if (freq_matrix[i][j] != 0 && char_freq[i] != 0) {
                prob_matrix[i][j] = freq_matrix[i][j] / (float)char_freq[i];
            }
        }
    }
}






int compare_func(const void *a, const void *b) {
    Tuple *pa = (Tuple *)a;
    Tuple *pb = (Tuple *)b;

    if (pa->probability < pb->probability) return 1;   
    if (pa->probability > pb->probability) return -1;
    return 0;
}


bool verifier_tentative(char *mot_mystere , char guess , int index){

    if (mot_mystere[index] == guess){
        return true;
    }
    else{
        return false;
    }


}


void prepare_list(char list[][20], int size) {
    char prepend_char = '0';

    for (int i = 0; i < size; i++) {
        char temp[20];              
        temp[0] = prepend_char;    
        temp[1] = '\0';             
        strcat(temp, list[i]);      
        strcpy(list[i], temp);      
    }
}


void print_banner(void){


    printf("\n");

    printf("     ▄█    ▄████████ ███    █▄       ████████▄  ███    █▄          ▄███████▄    ▄████████ ███▄▄▄▄   ████████▄  ███    █▄  \n");
    printf("    ███   ███    ███ ███    ███      ███   ▀███ ███    ███        ███    ███   ███    ███ ███▀▀▀██▄ ███   ▀███ ███    ███ \n");
    printf("    ███   ███    █▀  ███    ███      ███    ███ ███    ███        ███    ███   ███    █▀  ███   ███ ███    ███ ███    ███ \n");
    printf("    ███  ▄███▄▄▄     ███    ███      ███    ███ ███    ███        ███    ███  ▄███▄▄▄     ███   ███ ███    ███ ███    ███ \n");
    printf("    ███ ▀▀███▀▀▀     ███    ███      ███    ███ ███    ███      ▀█████████▀  ▀▀███▀▀▀     ███   ███ ███    ███ ███    ███ \n");
    printf("    ███   ███    █▄  ███    ███      ███    ███ ███    ███        ███          ███    █▄  ███   ███ ███    ███ ███    ███ \n");
    printf("    ███   ███    ███ ███    ███      ███   ▄███ ███    ███        ███          ███    ███ ███   ███ ███   ▄███ ███    ███ \n");
    printf("█▄ ▄███   ██████████ ████████▀       ████████▀  ████████▀        ▄████▀        ██████████  ▀█   █▀  ████████▀  ████████▀  \n");
    printf("▀▀▀▀▀▀                                                                                                                     \n");

    printf("\n");

}