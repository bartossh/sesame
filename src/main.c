#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <limits.h>
#include <stdbool.h>
#include "sesame.h"

#define PasswordLength 128

int min(int a, int b) {
    if (a < b) {
        return a;
    }
    return b;
}

void validator(unsigned char* str) {
    unsigned long result = SE_shannon(str);
    printf("\n");
    switch (result) {
        case 1:
            printf("INFO: Password: [ %s ] has [ %lu ] bit of Shannon entropy.\n", str, result);
            break;
        default:
            printf("INFO: Password: [ %s ] has [ %lu ] bits of Shannon entropy.\n", str, result);
            break;
    }
    printf("\n");
    int strength = min(result/4 ,32);
    printf("STRENGTH: %.*s%.*s%s",
           strength, 
           "+++++++++++++++++++++++++++++++++",
           32 - strength,
           "                                 ",
           "|<<< MAX\n"); 
    printf("\n");
}
   
int main(int argc, char* argv[]) {
    if( argc < 2 ) {
        char buf[BUFSIZ];
        char *result = fgets(buf, sizeof buf, stdin);
        if (!result) {
            printf("ERROR: Provide password to perform validation or pipe input.\n");
            return 0;
        }
        if (buf[strlen(buf)-1] == '\n') {
            buf[strlen(buf)-1] = '\0';
        }
        validator((unsigned char*)buf);
        return 0;
    }
  
    char to_validate[PasswordLength];
    snprintf(to_validate, PasswordLength*sizeof(char), "%s", argv[1]);
    
    validator((unsigned char*)to_validate);

    return 0; 
}
