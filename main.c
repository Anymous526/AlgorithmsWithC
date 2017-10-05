#include <stdio.h>
#include <stdlib.h>
#include "clist/clist.h"
#include "dlist/dlist.h"
#include "list/list.h"
#include "stack/stack.h"
#include  "main.h"

int maina(){
    listTest();
    dlistTest();
    return 0;
}

void printListItem(List *list){

    if(list == NULL || list->size ==  0)
        return;

    for(ListElmt *item = list->head; item != NULL; item=item->next){
        printf("%2d\n", *((int*)item->data));
    }

}

void printDListItem(DList *list) {
    if(list == NULL || list->size == 0)
        return;

    for(DListElmt *item = list->head; item != NULL; item=item->next){
        printf("%2d\n", *((int*)item->data));
    }
}

void listTest(){
    List *list;

    if ( (list = malloc(sizeof(List)) ) == NULL )
        return ;
    list_init(list, NULL);
    int a = 10;
    int b = 100;
    int c = 1000;
    list_ins_next(list, NULL,  &a);
    printListItem(list);
    printf("--one--\n");
    list_ins_next(list, list->head,  &b);
    printListItem(list);
     printf("--two--\n");
    list_ins_next(list, list->head,  &c);
    printListItem(list);
    printf("--three--\n");
    int *d;
    list_rem_next(list, list->head, (void *)&d);
    printListItem(list);

    printf("\n\ndelete the number : %2d\n", *d);

    list_destroy(list);
    printf("----ListTestEnd----\n");
    return ;
}


void dlistTest(){
    DList *list;
    if ((list = malloc(sizeof(DList))) == NULL )
        return;
    dlist_init(list, NULL);

    int a = 1;
    int b = 10;
    int c = 100;
    int *d;

    dlist_ins_next(list, NULL, &a);
    dlist_ins_next(list, list->head, &c);
    dlist_ins_prev(list, list->head, &b);
    printDListItem(list);
    dlist_remove(list, list->head, &d);



    //dlist_destroy(list);
    return;
}


