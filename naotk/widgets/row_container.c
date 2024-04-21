#include "ntk/widgets/row_container.h"

#include "ntk/widgets/widget.h"
#include "ntk/list.h"

#include <assert.h>

#include "util.h"

Ntk_Widget ntk_row_container_create(void)
{
    Ntk_Widget widget = {
        .id = get_id(),
        .type = NTK_WIDGET_TYPE_ROW_CONTAINER,
    };
    ntk_list_init(&widget.widget.row_container.widgets);

    return widget;
}

void ntk_row_container_add_widget(Ntk_Widget* container, Ntk_Widget* widget)
{
    assert(container->type == NTK_WIDGET_TYPE_ROW_CONTAINER && "Widget type is not row container");
    ntk_list_insert(&container->widget.row_container.widgets, &widget->link);
}
