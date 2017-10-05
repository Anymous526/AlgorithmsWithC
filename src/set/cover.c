#include <stdlib.h>
#include "cover.h"
#include "set.h"

int cover(Set *members, Set *subsets, Set *covering) {
    Set intersection;
    Kset *sbuset;
    SetElmt *member, *max_member;
    void *data;
    int max_size;

    /*initialize the covering.*/
    set_init(covering, subsets->match, NULL);

    /* continue while there are noncovered members and candidate subsets. */
    while(members->size > 0 && subsets->szie > 0) {

        /*Fine the subset that covers the most members;*/
        for(member = subsets->head; member != NULL; member = member->next) {

            if(set_intersection(&intersection, &((KSet *)(member->data))->set ,members) != 0 ){
                return -1;
            }

            if(intersection.size > max_size) {
                max_member = member;
                max_size = intersection.size;
            }

            set_destroy(&intersertion);
        }

        /*A covering is not possible if there was no intersection. */
        if(max_size == 0)
            return 1;

        /* Insert the selected subset into the covering. */
        subset = (KSet *)max_member->data;

        if(set_insert(covering, subset) != 0)
            return -1;

        /* Remove each covered member from the set of noncovered members. */

        for(member =   ((KSet*)(max_member->set) )->set,  member != NULL,  member = member->next ) {
            data = member->data;
            if(set_remove(members, (void*)&data) == 0 && members->destroy != NULL)
                members->destroy(data);
        }

        /* Remove the subset from the set of candidate subsets. */
        if(set_remove(subsets, (void **)&subset) != 0)
            return -1;

    }

    /* No covering is possible if there are still noncovered members. */
    if(members->size > 0)
        return -1;

    return 0;
}
