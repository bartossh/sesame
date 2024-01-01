/// Copyright (c) 2024 Bartosz Lenart

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <limits.h>
#include <stdbool.h>
#include "sesame.h"

#define PasswordLength 128
#define StrengthIndicatorLenght 32
#define DaysInYear 365

int min(int a, int b) {
    if (a < b) {
        return a;
    }
    return b;
}

void validator(unsigned char* str) {
    unsigned long result = se_shannon(str);
    unsigned long long days = se_bruteForceDays(result);
    
    printf("\n");
    switch (result) {
        case 1:
            printf("INFO: Password: [ %s ] has %lu bit of Shannon entropy.\n", str, result);
            break;
        default:
            printf("INFO: Password: [ %s ] has %lu bits of Shannon entropy.\n", str, result);
            break;
    }
    printf("\n");
    int strength = min(result/4 ,StrengthIndicatorLenght);
    printf("STRENGTH: %.*s%.*s%s",
           strength, 
           "+++++++++++++++++++++++++++++++++",
           StrengthIndicatorLenght - strength,
           "                                 ",
           "|<<< MAX\n"); 
    printf("\n");
    if (days < DaysInYear) {
        printf(
            "INFO: It will take %llu days to brute force your password with speed of 1000 guesses/second.\n",
            days
        );
    } else {
        char *yd = se_yearsAndDays(days);
        printf(
            "INFO: It will take %s to brute force your password with speed of 1000 guesses/second.\n",
            yd
        );
        free(yd);
    }
    printf("\n");

    unsigned long long pwned_count = se_getPwned(str);
    printf("INFO: Password [ %s ] is Pwned %llu times.\n", str, pwned_count);

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
