#ifndef NTK_WINDOW_H_
#define NTK_WINDOW_H_

#include <stdbool.h>

#include "ntk/types.h"

struct Ntk_Window {
    char const* title;
    int width;
    int height;
    Ntk_Widget* main_widget;

    bool should_quit;
};

void ntk_window_set_size(Ntk_Window* window, int width, int height);
void ntk_window_set_title(Ntk_Window* window, char const* title);
void ntk_window_set_main_widget(Ntk_Window* window, Ntk_Widget* widget);

int ntk_window_run(Ntk_Window* window);
void ntk_window_close(Ntk_Window* window);

#endif // NTK_WINDOW_H_
