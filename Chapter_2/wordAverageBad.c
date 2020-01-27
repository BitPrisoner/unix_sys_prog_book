/*
 * Program 2.3 on page 39
 * An incorrect use of strtok to determine the average number of words
 * per line
 */
#include <string.h>
#define LINE_DELIMITERS "\n"
#define WORD_DELIMITERS " "

static int wordCount(char *s){
    int count = 1;

    if(strtok(s, WORD_DELIMITERS) == NULL) {
        return 0;
    }
    while(strtok(NULL, WORD_DELIMITERS) != NULL) {
        count++;
    }
    return count;
}

// return average size of words in s
double wordaverage(char *s) {
    int lineCount = 1;
    char *nextLine;
    int words;

    nextLine = strtok(s, LINE_DELIMITERS);
    if(nextLine == NULL) {
        return 0.0;
    }

    words = wordCount(nextLine);
    while((nextLine = strtok(NULL, LINE_DELIMITERS)) != NULL) {
        words += wordCount(nextLine);
        lineCount++;
    }

    return (double)words/lineCount;
}