#ifndef NTK_BUTTON_H_
#define NTK_BUTTON_H_

#include <stdbool.h>

#include "ntk/types.h"

typedef void (*Ntk_Button_Callback)(void*);

struct Ntk_Button {
    char const* label;
    Ntk_Button_Callback callback;
    void* callback_data;
};

Ntk_Widget ntk_button_create(char const* label, Ntk_Button_Callback callback,
                             void* callback_data);

#endif // NTK_BUTTON_H_
