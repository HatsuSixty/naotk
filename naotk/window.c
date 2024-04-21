#include "ntk/window.h"

#include "interaction/ui.h"

void ntk_window_set_size(Ntk_Window* window, int width, int height)
{
    window->width = width;
    window->height = height;
}

void ntk_window_set_title(Ntk_Window* window, char const* title)
{
    /*
     * Anti-clang-format comment
     */
    window->title = title;
}

void ntk_window_set_main_widget(Ntk_Window* window, Ntk_Widget* widget)
{
    /*
     * Anti-clang-format comment
     */
    window->main_widget = widget;
}

int ntk_window_run(Ntk_Window* ntk_window)
{
    return render_window(ntk_window);
}
