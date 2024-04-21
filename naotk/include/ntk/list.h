#ifndef NTK_LIST_H_
#define NTK_LIST_H_

#include "types.h"

struct Ntk_List {
    Ntk_List* prev;
    Ntk_List* next;
};

#define ntk_container_of(ptr, sample, member) \
    (__typeof__(sample))((char*)(ptr)-offsetof(__typeof__(*sample), member))

#define ntk_list_for_each(pos, head, member)                \
    for (pos = ntk_container_of((head)->next, pos, member); \
         &pos->member != (head);                            \
         pos = ntk_container_of(pos->member.next, pos, member))

#define ntk_list_for_each_safe(pos, tmp, head, member)           \
    for (pos = ntk_container_of((head)->next, pos, member),      \
        tmp = ntk_container_of((pos)->member.next, tmp, member); \
         &pos->member != (head);                                 \
         pos = tmp, tmp = ntk_container_of(pos->member.next, tmp, member))

#define ntk_list_for_each_reverse(pos, head, member)        \
    for (pos = ntk_container_of((head)->prev, pos, member); \
         &pos->member != (head);                            \
         pos = ntk_container_of(pos->member.prev, pos, member))

#define ntk_list_for_each_reverse_safe(pos, tmp, head, member)   \
    for (pos = ntk_container_of((head)->prev, pos, member),      \
        tmp = ntk_container_of((pos)->member.prev, tmp, member); \
         &pos->member != (head);                                 \
         pos = tmp, tmp = ntk_container_of(pos->member.prev, tmp, member))

void ntk_list_init(Ntk_List* list);
void ntk_list_insert(Ntk_List* list, Ntk_List* elm);
void ntk_list_remove(Ntk_List* elm);
int ntk_list_length(Ntk_List const* list);
int ntk_list_empty(Ntk_List const* list);
void ntk_list_insert_list(Ntk_List* list, Ntk_List* other);

#endif // NTK_LIST_H_
