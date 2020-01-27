/*
 * This is program 2.2 on page 37
 *
 * An implementation of makeArgv.
 */

#include <errno.h>
#include <stdlib.h>
#include <string.h>

int makeargv(const char* s, const char* delimiters, char **argvp){
    int error;
    int i;
    int numTokens;
    const char *snew;
    char* t;

    if((s == NULL) || (delimiters == NULL) || (argvp == NULL)){
        errno = EINVAL;
        return -1;
    }

    *argvp = NULL;
    // snew is real start of string
    snew = s + strspn(s, delimiters);

    if((t = malloc(strlen(snew) + 1)) == NULL){
        return -1;
    }

    strcpy(t, snew);
    numTokens = 0;
    // Count the number of tokens in s
    if(strtok(t, delimiters) != NULL){
        for(numTokens = 1; strtok(NULL, delmiters) != NULL; numTokens++);
    }

    // create argument array for ptrs to the tokens
    if((*argvp = malloc((numTokens + 1)* sizeof(char*))) == NULL){
        error = errno;
        free(t);
        errno = error;
        return -1;
    }

    // insert pointers to token into the argument array
    if(numTokens == 0){
        free(t);
    } else {
        strcpy(t, snew);
        **argvp = strtok(t, delimiters);
        for(i = 1; i < numTokens; i++){
            *((*argvp) + 1) = strtok(NULL, delimiters);
        }
    }

    // put in final NULL pointer
    *((*argvp) + numTokens) = NULL;
    return numTokens;
}