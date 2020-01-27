/*
 * Program 2.4 on page 40
 * A correct use of strtok_r to determine the average number
 * of words per line
 */

#include <string.h>
#define LINE_DELIMITERS "\n"
#define WORD_DELIMITERS " "

static int wordCount(char *s){
    int count = 1;
    char *lasts;

    if(strtok_r(s, WORD_DELIMITERS, &lasts) == NULL){
        return 0;
    }

    while(strtok_r(NULL, WORD_DELIMITERS, &lasts) != NULL){
        count++;
    }
    return count;
}

// return average size of words in s
double wordAverage(char *s){
    char *lasts;
    int lineCount = 1;
    char *nextLine;
    int words;

    nextLine = strtok_r(s, LINE_DELIMITERS, &lasts);
    if(nextLine == NULL){
        return 0.0;
    }

    words = wordCount(nextLine);
    while((nextLine = strtok_r(NULL, LINE_DELIMITERS, &lasts)) != NULL){
        words += wordCount(nextLine);
        lineCount++;
    }

    return (double)words/lineCount;
}