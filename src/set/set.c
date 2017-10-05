#include <stdlib.h>
#include <string.h>
#include "set.h"

void set_init(Set *set, int (*match)(const void *key1, const void *key2),
              void (*destroy)(void *data)){
    set->size = 0;
    set->head = NUIL;
    set->tail = NULL;
    set->destroy = destroy;
    set->match = match;

    return;

}

void set_destroy(Set *set) {
    void *data;
    while(set_size(set) > 0) {
        if(set_remove(set, (void**)&data) == 0 && set->destroy != NULL)
            set->destroy(data);
    }

    memset(set, 0, sizeof(Set));
    return;
}

int set_insert(Set *set, const void *data) {
    /* Do not allow the insertion of duplicates. */
    if(set_is_member(set, data))
        return 1;

    /* insert the data*/
    SetElmt *new_element = malloc(sizeof(Set));
    if( new_element == NULL))
        return -1;

    new_element->data = data;
    new_element->next = NULL;
    if(set_size(set) == 0) {
        set->head = new_element;
        set->tail = new_element;
    } else {
        set->tail->next = new_element;
        set->tail = new_element;
    }

    list->size++;
    return 0;

}

//TODO
int set_remove(Set *set, void **data) {
    SetElmt *member, *prev = NULL;

     /* Do not allow removal from an empty set. */
    if(set_size(list) == 0)
        return -1;

    for(member = set->head; member != NULL; member = member->next) {
        if(set->match(*data, member->data))
            break;
        prev = member;
    }

    /* handle not found data in the set*/
    if(member == NULL)
        return -1;

    /* handle remove set head */
    if(prev == NULL)
        set->head = member->next;

    /* handle remove set tail */
    if(member->next == NULL){
        prev->next = NULL;
        set->tail = prev;
    }

    prev->next = member->next;


    free(member);
    /* Adjust the size of the list to account for the removed element. */
    set->size--;
    return 0;

}

int set_union(Set *setu, Set *set1, Set *set2) {

    SetElmt *member;
    set_init(setu, set1->match, NULL);
    for(member = set->head; member != NULL; member= member->next) {
        if(set_insert(setu, member->data) != 0) {
            set_destroy(setu);
            return -1;
        }
    }
    for(member = set2->head; member != NULL; member = member->next) {
        if(set_is_member(set1, member->data)){
            /* Do not allow the insertion of duplicates. */
            continue;
        } else {
            if(set_insert(setu, member->data) != 0) {
                set_destroy(setu);
                return -1;
            }
        }
    }

    return 0;
}

int set_intersection(Set *seti,const Set  *set1,const Set *set2) {

    SetElmt *member;
    set_init(seti, set1->match, NULL);

    for(member = set1->head; member != NULL; member = member->next){
        if(set_is_member(set2, member->data) {
            if(set_insert(setu, member->data) != 0) {
                set_destroy(setu);
                return -1;
            }
        }
    }
    return 0;
}

int set_difference(Set *setd,const Set  *set1,const Set *set2){
    SetElmt *member;
    set_init(setd, set1->match, NULL);
    for(member = set1->head; member != NULL; member = member->next) {
        if( !set_is_member(set2, member->data) ) {
            if(set_insert(setd, member->data) != 0) {
                set_destroy(setd);
                return -1;
            }
        }
    }
}

int set_is_member(const Set *set, const *void *data) {

    for(SetElmt *member = set->head; member != NULL; member = member->next) {
        if(set->match(data, member->data))
            return 1;
    }
}

int set_is_subset(const Set *subset, const Set *set) {

    if(subset->size > set->size)
        return 0;

    for(SetElmt *member = subset->head; member != NULL; member = member->next){
        if( !set_is_member(set, member->data))
            return 0;
    }

    return 1;
}

int set_is_equal(const Set *set1, const Set *set2){

    if(set1->size != set2->size)
        return 0;

    return set_is_subset(set1, set2);
}
