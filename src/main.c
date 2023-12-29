#include <stdio.h>
#include <stdlib.h>
#include "sesame.h"

#define PasswordLength 128

int min(int a, int b) {
    if (a < b) {
        return a;
    }
    return b;
}
   
int main(int argc, char* argv[]) 
{ 
    if( argc < 2 ) {
        printf("ERROR: Please provide a password to be validated.\n");
        return 1;
    }
  
    char to_validate[PasswordLength];
    snprintf(to_validate, PasswordLength*sizeof(char), "%s", argv[1]); 


    unsigned long result = SE_shannon((unsigned char *)to_validate);

    printf("\n");
    switch (result) {
        case 1:
            printf("INFO: Password: [ %s ] has [ %lu ] bit of Shannon entropy.\n", to_validate, result);
            break;
        default:
            printf("INFO: Password: [ %s ] has [ %lu ] bits of Shannon entropy.\n", to_validate, result);
            break;
    }
    printf("\n");
    int strength = min(result/4 ,32);
    printf("STRENGTH: %.*s%.*s%s",
           1 + strength, 
           "+++++++++++++++++++++++++++++++++",
           32 - strength,
           "                                 ",
           "|<<< MAX\n"); 
    printf("\n");
    return 0; 
}
