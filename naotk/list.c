#include "ntk/list.h"

#include <stddef.h>

void ntk_list_init(Ntk_List* list)
{
    list->prev = list;
    list->next = list;
}

void ntk_list_insert(Ntk_List* list, Ntk_List* elm)
{
    elm->prev = list;
    elm->next = list->next;
    list->next = elm;
    elm->next->prev = elm;
}

void ntk_list_remove(Ntk_List* elm)
{
    elm->prev->next = elm->next;
    elm->next->prev = elm->prev;
    elm->next = NULL;
    elm->prev = NULL;
}

int ntk_list_length(const Ntk_List* list)
{
    int count = 0;
    Ntk_List* e = list->next;
    while (e != list) {
        e = e->next;
        count++;
    }

    return count;
}

int ntk_list_empty(const Ntk_List* list)
{
    return list->next == list;
}

void ntk_list_insert_list(Ntk_List* list, Ntk_List* other)
{
    if (ntk_list_empty(other))
        return;

    other->next->prev = list;
    other->prev->next = list->next;
    list->next->prev = other->prev;
    list->next = other->next;
}
