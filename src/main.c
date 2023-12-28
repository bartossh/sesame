#include <stdio.h>
#include <stdlib.h>
#include "sesame.h"

#define PasswordLength 128
   
int main(int argc, char* argv[]) 
{ 
    if( argc < 2 ) {
        printf("ERROR: Please provide password to be validated.\n");
        return 1;
    }
    switch (SE_check()){
    case 0:
        printf("INFO: All modules are ready.\n");
        break;
    case SE_ErrPownedModuleNotReady:
        printf("INFO: Module Pawned Passwords is not ready yet.\n");
        break;
    default:
        printf("FATAL: Unknown check status. Some modules may not work properly.\n");
        return 1;
    }
  
    char tbo[PasswordLength];
    snprintf(tbo, PasswordLength*sizeof(char), "%s", argv[1]); 

    printf("INFO: Validating password: [ %s ] ...\n", tbo);  
  
    return 0; 
}
