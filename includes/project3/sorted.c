/* Brian Benedicto
 * Coen12L Project 3
 * 4/26/2020
 */
# include <assert.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
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

static int binary_search(SET *sp, char *elt, bool *found) { // O(n), *found is true if element matches

    assert(sp != NULL); //check if memory successfully allocated

    int mid = sp->count / 2; //start from middle because binary search
    int low = 0, high = sp->count - 1;

    while (low <= high) {
        mid = (low + high) / 2;
        if (strcmp(sp->data[mid], elt) < 0) //means current middle comes before elt, so shift high down
            high = mid - 1;
        else if (strcmp(sp->data[mid], elt) > 0) //means current middle comes after elt, so shift low up
            low = mid + 1;
        else { //which means if strcmp == 0 which is a match
            *found = true; //found a duplicate
            return mid;
        }
    }

    *found = false; //its unique
    return low;
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
    bool found;
    if (sp->count >= sp->length) return;

    int storage_location = binary_search(sp, elt, &found);
    if (found == false) {
        sp->data[sp->count] = malloc(
                strlen(elt) + 1); //allocate memory for string according to length +1 because of the NULL

        for (int i = sp->count; i > storage_location; i--) { //start at the top, decrement until where to store
            strcpy(sp->data[i], sp->data[i - 1]); //shift every above element up
        }

        strcpy(sp->data[storage_location], elt); //uses array syntax to copy string into now empty space
        sp->count++; //increment count if you add
    }
}

void removeElement(SET *sp, char *elt) { // O(n), same explanation of addElement
    assert(sp != NULL); //check if memory is allocated
    bool found;

    int i = 0;
    int storage_location = binary_search(sp, elt, &found);
    if (found == true) {
        while (i < sp->count) {
            // to remove copy next in line into current spot
            strcpy(sp->data[storage_location], sp->data[storage_location + 1]);
            i++;
        }
        sp->count--;
    }
}

char *findElement(SET *sp, char *elt) { // O(1)
    assert(sp != NULL); //check if memory is allocated
    bool found;

    binary_search(sp, elt, &found);
    if (found == false) {
        return NULL; //return null since element not matching

    }
    return elt; //else returns this matching element
}

char **getElements(SET *sp) { // O(1)
    assert(sp != NULL); //check if memory is allocated
    return (sp->data);
}
