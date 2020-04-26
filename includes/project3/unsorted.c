/* Brian Benedicto
 * Coen12L Project 3
 * 4/26/2020
 */
# include <assert.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "set.h"

# define NONDUPLICATE -1 //just incase it returns first index, we use -1 instead of 0

typedef struct set { // initialize our set
    char **data; // the array of string pointers
    int count; // used for # of elements in array
    int length; // maximum length of the array
} SET;

SET *createSet(int maxElts) { // O(1)
    SET *sp = malloc(sizeof(SET));
    assert(sp != NULL); //check if memory successfully allocated

    sp->count = 0; //count initialized
    sp->length = maxElts;
    sp->data = malloc(sizeof(char *) * (maxElts));
    return sp;
}

static int search(SET *sp, char *elt) { // O(n)
    assert(sp != NULL); //check if memory successfully allocated
    for (int n = 0; n < sp->count; n++) {
        if (strcmp(sp->data[n], elt) == 0) {
            return n;
        }
    }
    return NONDUPLICATE;
}

void destroySet(SET *sp) { // O(1), frees all allocated memory of the set
    assert(sp != NULL); //check if memory is allocated
    for (int i = 0; i < sp->count; i++)
        free(sp->data[i]); //have to free each string
    free(sp->data); //free this pointer
    free(sp); //free entire structure sp
}

int numElements(SET *sp) { // O(1)
    assert(sp != NULL); //check if memory is allocated
    return (sp->count); //return count
}

void addElement(SET *sp, char *elt) { // O(n), this is because it is O(1) + O(n) from the search function
    assert(sp != NULL); //check if memory is allocated
    if (sp->count >= sp->length) return;

    int storage_location = search(sp, elt);
    if (storage_location == NONDUPLICATE) {
        sp->data[sp->count] = malloc(
                strlen(elt) + 1); //allocate memory for string according to length +1 because of the NULL
        strcpy(sp->data[sp->count], elt); //uses array syntax to copy string
        sp->count++; //increment count if you add
    }
}

void removeElement(SET *sp, char *elt) { // O(n), same explanation of addElement
    assert(sp != NULL); //check if memory is allocated


    int storage_location = search(sp, elt);
    int i = storage_location+1;
    if (storage_location != NONDUPLICATE) {
        while (i < sp->count) {
            // to remove copy next in line into current spot
            strcpy(sp->data[i-1], sp->data[i]);
            i++;
        }
        sp->count--;
    }
}

char *findElement(SET *sp, char *elt) { // O(1)
    assert(sp != NULL); //check if memory is allocated
    int storage_location = search(sp, elt);
    if (storage_location == NONDUPLICATE) {
        return NULL; //return null since element not matching

    }
    return elt; //else returns this matching element
}

char **getElements(SET *sp) { // O(1)
    assert(sp != NULL); //check if memory is allocated
    return (sp->data);
}
