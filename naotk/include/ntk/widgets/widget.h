#ifndef NTK_WIDGET_H_
#define NTK_WIDGET_H_

#include "ntk/types.h"
#include "ntk/widgets/button.h"
#include "ntk/widgets/row_container.h"

enum Ntk_Widget_Type {
    NTK_WIDGET_TYPE_BUTTON,
    NTK_WIDGET_TYPE_ROW_CONTAINER,
};

struct Ntk_Widget {
    int id;
    Ntk_Widget_Type type;
    union {
        Ntk_Button button;
        Ntk_Row_Container row_container;
    } widget;

    Ntk_List link;
};

#endif // NTK_WIDGET_H_
