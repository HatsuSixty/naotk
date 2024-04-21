#include "ntk/widgets/button.h"

#include "ntk/types.h"
#include "ntk/widgets/widget.h"

#include "util.h"

Ntk_Widget ntk_button_create(char const* label, Ntk_Button_Callback callback,
                             void* callback_data)
{
    return (Ntk_Widget) {
        .id = get_id(),
        .type = NTK_WIDGET_TYPE_BUTTON,
        .widget = {
            .button = {
                .label = label,
                .callback = callback,
                .callback_data = callback_data,
            },
        },
    };
}
