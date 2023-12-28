#include <stdio.h>
#include <stdlib.h>
#include "sesame.h"

#define PasswordLength 128
   
int main(int argc, char* argv[]) 
{ 
    if( argc < 2 ) {
        printf("Please provide password to be validated.\n");
        return 1;
    }
    char tbo[PasswordLength];
    switch (SE_check()){
    case 0:
        printf("All modules are ready.\n");
        break;
    case SE_ErrPownedModuleNotReady:
        printf("Module Pawned Passwords is not ready yet.\n");
        break;
    default:
        printf("Unknown check status. Some modules may not work properly.\n");
    }
  
    snprintf(tbo, PasswordLength*sizeof(char), "%s", argv[1]); 

    printf("Given password [ %s ] is going to be validated...\n", tbo);  
  
    return 0; 
}
