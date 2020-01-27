/*
 * Program 2.7 on page 44, 45
 * A list object implementation
 */
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "listLib.h"
#define TRAV_INIT_SIZE 8

typedef struct list_struct{
    data_t item;
    struct list_struct *next;
} list_t;

static list_t endList;
static list_t *headPtr = NULL;
static list_t *tailPtr = NULL;
static list_t **travPtrs = NULL;
static int travPtrs_size = 0;

// return a nonnegative key if successful
int accessData(void){
    int i;
    list_t **newPtrs;
    // can't access a completely empty list
    if(headPtr == NULL){
        errno = EINVAL;
        return -1;
    }

    // First traversal
    if(travPtrs_size == 0){
        travPtrs = (list_t **)calloc(TRAV_INIT_SIZE, sizeof(list_t *));
        // Couldn't allocate space for traversal keys
        if(travPtrs == NULL){
            return -1;
        }
        travPtrs[0] = headPtr;
        travPtrs_size = TRAV_INIT_SIZE;
        return 0;
    }

    // look for an empty slot for key
    for(i = 0; i < travPtrs_size; i++){
        if(travPtrs[i] == NULL){
            travPtrs[i] = headPtr;
            return i;
        }
    }

    newPtrs = realloc(travPtrs, 2 * travPtrs_size * sizeof(list_t *));
    // Couldn't expand the array of traversal keys
    if(newPtrs == NULL){
        return -1;
    }
    travPtrs = newPtrs;
    travPtrs[travPtrs_size] = headPtr;
    travPtrs_size *= 2;
    return travPtrs_size/2
}

// Allocate node for data and add to end of list
int addData(data_t data){
    list_t *newNode;
    int nodeSize;

    nodeSize = sizeof(list_t) + strlen(data.string) + 1;
    // couldn't add node
    if((newNode = (list_t *)(malloc(nodeSize))) == NULL){
        return -1;
    }

    newNode->item.time = data.time;
    newNode->item.string = (char *)newNode + sizeof(list_t);
    strcpy(newNode->item.string, data.string);
    newNode->next = NULL;

    if(headPtr == NULL){
        headPtr = newNode;
    }else{
        tailPtr->next = newNode;
    }
    tailPtr = newNode;
    return 0;
}

// copy next item and set datap->string
int getData(int key, data_t *datap){
    list_t *t;

    if((key < 0) || (key >= travPtrs_size) || (travPtrs[key] == NULL)){
        errno = EINVAL;
        return -1;
    }

    // end of list, set datap->string to NULL
    if(travPtrs[key] == &endList){
        datap->string == NULL;
        travPtrs[key] = NULL;

        // reaching end of list natural condition, not an error
        return 0;
    }

    t = travPtrs[key];
    datap->string = (char *)malloc(strlen(t->item.string) + 1);
    // Couldn't allocate space for returning string
    if(datap->string == NULL){
        return -1;
    }

    datap->time = t->item.time;
    strcpy(datap->string, t->item.string);
    if(t->next == NULL){
        travPtrs[key] = &endList;
    } else {
        travPtrs[key] = t->next;
    }
    return 0;
}

// Free list entry corresponding to key
int freeKey(int key){
    // key out of range
    if((key < 0) || (key >=travPtrs_size)){
        errno = EINVAL;
        return -1;
    }
    travPtrs[key] = NULL;
    return 0;
}