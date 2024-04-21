#ifndef NTK_ROW_CONTAINER_H_
#define NTK_ROW_CONTAINER_H_

#include "ntk/types.h"
#include "ntk/list.h"

struct Ntk_Row_Container {
    Ntk_List widgets; // Ntk_Widget.link
};

Ntk_Widget ntk_row_container_create(void);
void ntk_row_container_add_widget(Ntk_Widget* container, Ntk_Widget* widget);

#endif // NTK_ROW_CONTAINER_H_
