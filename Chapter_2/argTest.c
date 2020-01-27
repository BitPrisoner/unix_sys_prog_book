/*
 * This is program 2.1
 *
 * A program that takes a single string as its command-line argument
 * and calls makeArgv to create an argument array
 */
#include <stdio.h>
#include <stdlib.h>
int makeargv(const char* s, const char* delimiters, char ***argvp);

int main(int argc, char* argv[]){
    char delim[] = " \t";
    int i;
    char **myargv;
    int numTokens;

    if(argc != 2){
        fprintf(stderr, "Usage: %s string\n", argv[0]);
        return 1;
    }

    if((numTokens = makeargv(argv[1], delim, &myargv)) == -1){
        fprintf(stderr, "Failed to construct an argument array for %s\n", argv[1]);
        return 1;
    }

    printf("The argument array contains:\n");
    for(i = 0; i < numTokens; i++){
        printf("%d:%s\n", i, myargv[i]);
    }
    return 0;
}
