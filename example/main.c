#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include "ntk/widgets/widget.h"
#include "ntk/window.h"

static void print_hello(void* data)
{
    (void)data;

    printf("Hello, World!\n");
}

static void bye_bye(void* data)
{
    Ntk_Window* window = data;
    ntk_window_close(window);
}

int main(void)
{
    Ntk_Window window = {0};

    Ntk_Widget container = ntk_row_container_create();
    Ntk_Widget hello_button = ntk_button_create("Hello, World!", print_hello, NULL);
    Ntk_Widget hello_button2 = ntk_button_create("Hello, World!", print_hello, NULL);
    Ntk_Widget exit_button = ntk_button_create("Exit program", bye_bye, &window);

    ntk_row_container_add_widget(&container, &hello_button);
    ntk_row_container_add_widget(&container, &hello_button2);
    ntk_row_container_add_widget(&container, &exit_button);

    ntk_window_set_size(&window, 640, 480);
    ntk_window_set_title(&window, "Hello, World!");
    ntk_window_set_main_widget(&window, &container);

    ntk_window_run(&window);

    return 0;
}
