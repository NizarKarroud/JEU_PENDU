#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_UNIQUE 256
#define N 3
int main() {
    char list[N][20] = {"apple", "banana", "cherry"};
    char prepend_char = '0';
    float prob_matrix[MAX_UNIQUE][MAX_UNIQUE];
    float freq_matrix[MAX_UNIQUE][MAX_UNIQUE];

    int char_freq[MAX_UNIQUE] ;
    memset(prob_matrix, 0, sizeof(prob_matrix));
    memset(freq_matrix, 0, sizeof(freq_matrix));
    memset(char_freq, 0, sizeof(char_freq));

    for (int i = 0; i < 3; i++) {
        char temp[20];              
        temp[0] = prepend_char;    
        temp[1] = '\0';             
        strcat(temp, list[i]);      
        strcpy(list[i], temp);      
    }


    for (int i = 0; i < N; i++) {
        for (int j = 0; j < strlen(list[i]); j++) {
            char c = list[i][j];
            char_freq[c] ++ ;
            char next_char = list[i][j+1];
            if (j + 1 < strlen(list[i])) {
                char next_char = list[i][j + 1];
                freq_matrix[c][next_char]++;
                // printf("%c followed by : %c , %f times \n" , c, next_char, freq_matrix[c][next_char]) ;
            }

        }
    }

    for (int i = 0; i < MAX_UNIQUE; i++) {
        for (int j = 0; j < MAX_UNIQUE ; j++) {
        
            if (freq_matrix[i][j] != 0 && char_freq[i] != 0 ){
                prob_matrix[i][j] = freq_matrix[i][j] / (float)char_freq[i];
                printf("%c is followed by %c with a prob of %f \n" , i , j , prob_matrix[i][j]);
            }


        }
    }

    // to find the first char , lets check the probabilities of 


    return 0;
}


