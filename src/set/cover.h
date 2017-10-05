#ifndef COVER_H
#define COVER_H

#include "set.h"

typedef struct KSet_{
    void *key;
    Set set;
}KSet;

/*public interface */
int cover(Set *members, Set * subsets, Set *covering);

#endif // COVER_H
