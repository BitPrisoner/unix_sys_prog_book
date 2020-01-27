/*
 * Program 2.6 from page 43
 * The header file listLib.h
 */

#ifndef UNIX_SYS_PROG_BOOK_LISTLIB_H
#define UNIX_SYS_PROG_BOOK_LISTLIB_H

#include <time.h>

typedef struct data_struct{
    time_t time;
    char *string;
} data_t;

int accessData(void);
int addData(data_t data);
int freeKey(int key);
int getData(int key, data_t *datap);

#endif //UNIX_SYS_PROG_BOOK_LISTLIB_H