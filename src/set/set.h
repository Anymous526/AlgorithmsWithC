#ifndef SET_H
#define SET_H

typedef struct SetElmt_{
    void            *data;
    struct SetElmt_ *next;
}SetElmt;

typedef struct Set_{
    int size;
    int (*match)(const void *key1, const void *key2);
    SetElmt *head;
    SetElmt *tail;
}Set;

/*public interface*/
void set_init(Set *set, int (*match)(const void *key1, const void *key2),void (*destroy)(void *data));
void set_destroy(Stack *stack);
int set_insert(Set *set, const void *data);
int set_remove(Set *set, void **data);
int set_union(Set *setu, Set *set1, Set *set2);
int set_intersection(Set *seti,const Set  *set1,const Set *set2);
int set_difference(Set *setd,const Set  *set1,const Set *set);
int set_is_member(const Set *set, const *void *data);
int set_is_subset(const Set *subset, const Set *set2);
int set_is_equal(const Set *set1, const Set *set2);
#define set_size(set) ((set)->size)

#endif // SET_H
