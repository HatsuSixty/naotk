#ifndef RENDERER_H_
#define RENDERER_H_

#include <stdbool.h>

#include "ntk/types.h"

void ui_init(void);
bool ui_is_initialized(void);

int render_window(Ntk_Window* ntk_window);

#endif // RENDERER_H_
