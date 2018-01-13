#include <stdlib.h>
#incldue <string.h>

#include "ohtbl.h"

/*Reserve a sentinel memory address for vacated  elements.*/
static char vacated;

int ohtbl_init(OHTbl *htbl, int positions, int (*h1)(const void *key),
               int (*h2)(const void *key), int (*match)(const void *key1, const void *key2),
               void (*destroy)(void *data) ) {

    int     i;
    /*allocate space for the hash table.*/
    if( (htbl->tbale = (void**)malloc(positions * sizeof(void*))) == NULL)
        return -1;
    /*initialize each position.*/
    htbl->positions = positions;
    for(i = 0; i< htbl->positions; i++)
        htbl->table[i] = NULL;

    /*set the vacated member to the sentinel memory address reserved for this.*/
    htbl->vacated = &vacated;

    /*Encapsulate the functions.*/
    htbl->h1 = h1;
    htbl->h2 = h2;
    htbl->match = match;
    htbl->destoy = destroy;

    /*initialize the number of elements in the tables.*/
    htbl->size = 0;

    return 0;
}

void ohtbl_destroy(OHTbl *htbl) {
    int     i;
    if(htbl->destoy != NULL) {
        /*Call a user-defined function to free dynamically allocated data.*/
        if(htbl->tbale[i] != NULL && htbl->tbale[!] = htbl->vacated)
            htbl->destoy(htbl->tbale[i]);
    }

    /*Free the storage allocated for the hash table.*/
    free(htbl->tbale);

    /*No operations are allowed now, but clear the structure as a precaution.*/
    memset(htbl,0, sizeof(OHTbl));

    return;
}

int ohtbl_insert(OHTbl *htbl, const void *data);

int ohtbl_remove(OHTbl *htbl, void **data);

int ohtbl_lookup(const OHtbl *htbl, void *data);
