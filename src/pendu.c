#include <stdio.h>
#include <string.h>

int main() {
    char list[3][20] = {"apple", "banana", "cherry"};
    char prepend_char = '0';

    for (int i = 0; i < 3; i++) {
        char temp[20];              
        temp[0] = prepend_char;    
        temp[1] = '\0';             
        strcat(temp, list[i]);      
        strcpy(list[i], temp);      
    }

    for (int i = 0; i < 3; i++) {
        printf("%s\n", list[i]);
    }

    return 0;
}


