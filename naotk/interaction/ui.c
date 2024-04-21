#include "ui.h"

#include "ntk/list.h"
#include "ntk/types.h"
#include "ntk/window.h"
#include "ntk/widgets/widget.h"

#include <assert.h>
#include <stdio.h>
#include <GLFW/glfw3.h>
#include <math.h>

#include "shapes.h"
#include "util.h"
#include "input.h"

#include <rlgl.h>
#include <string.h>

struct {
    bool initialized;
    int active_button_id;
} UI;

static void window_size_callback(GLFWwindow* window, int width, int height)
{
    Ntk_Window* ntk_window = glfwGetWindowUserPointer(window);
    ntk_window->width = width;
    ntk_window->height = height;

    rlSetFramebufferWidth(width);
    rlSetFramebufferHeight(height);

    rlViewport(0, 0, ntk_window->width, ntk_window->height);
    rlMatrixMode(RL_PROJECTION);
    rlLoadIdentity();
    rlOrtho(0, ntk_window->width, ntk_window->height, 0, 0.0f, 1.0f);
    rlMatrixMode(RL_MODELVIEW);
    rlLoadIdentity();
}

#define BACKGROUND_COLOR 0x181818FF
#define BUTTON_COLOR color_brightness(BACKGROUND_COLOR, 20)
#define BUTTON_HOVER_COLOR color_brightness(BUTTON_COLOR, 20)
#define BUTTON_PRESSED_COLOR color_brightness(BUTTON_HOVER_COLOR, 20)

#define WIDGET_PADDING 5
#define BUTTON_ROUNDNESS 0.1
#define ROUNDNESS_SEGMENTS 20

static void draw_widget(GLFWwindow* window, Rectangle area, Ntk_Widget* widget)
{
    switch (widget->type) {
    case NTK_WIDGET_TYPE_BUTTON: {
        double cursor_pos_x;
        double cursor_pos_y;
        glfwGetCursorPos(window, &cursor_pos_x, &cursor_pos_y);
        Vector2 cursor_pos = { cursor_pos_x, cursor_pos_y };

        bool hovered = check_collision_point(cursor_pos, area);
        bool pressed
            = hovered && glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);

        uint32_t button_color = hovered ? BUTTON_HOVER_COLOR : BUTTON_COLOR;
        button_color = pressed ? BUTTON_PRESSED_COLOR : button_color;

        draw_rectangle_rounded(area, BUTTON_ROUNDNESS, ROUNDNESS_SEGMENTS,
                               button_color);

        if (hovered && is_mouse_button_just_pressed(GLFW_MOUSE_BUTTON_LEFT)) {
            UI.active_button_id = widget->id;
        } else if (UI.active_button_id != -1 && UI.active_button_id == widget->id) {
            if (is_mouse_button_just_released(GLFW_MOUSE_BUTTON_LEFT)) {
                UI.active_button_id = -1;
                if (hovered)
                    widget->widget.button.callback(widget->widget.button.callback_data);
            }
        }
    } break;

    case NTK_WIDGET_TYPE_ROW_CONTAINER: {
        size_t widget_count
            = ntk_list_length(&widget->widget.row_container.widgets);
        if (widget_count == 0) {
            Ntk_Widget* w = ntk_container_of(
                widget->widget.row_container.widgets.next, w, link);
            draw_widget(window, area, w);
            return;
        }

        float single_widget_width = area.width / widget_count;

        Ntk_Widget* cwidget;
        size_t i = 0;
        ntk_list_for_each(cwidget, &widget->widget.row_container.widgets, link)
        {
            Rectangle carea = {
                .x = area.x + single_widget_width * i,
                .y = area.y,
                .width = single_widget_width,
                .height = area.height,
            };
            if (i != widget_count - 1)
                carea.width -= WIDGET_PADDING;

            draw_widget(window, carea, cwidget);

            i++;
        }
    } break;
    }
}

void ui_init(void)
{
    memset(&UI, 0, sizeof(UI));
    UI.active_button_id = -1;
    UI.initialized = true;
}

bool ui_is_initialized(void)
{
    return UI.initialized;
}

int render_window(Ntk_Window* ntk_window)
{
    assert(ntk_window->main_widget && "Main widget not set");

    if (!glfwInit()) {
        return -1;
    }

    glfwDefaultWindowHints();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(ntk_window->width, ntk_window->height,
                                          "Hello World", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    rlLoadExtensions(glfwGetProcAddress);
    rlglInit(ntk_window->width, ntk_window->height);

    glfwSetWindowUserPointer(window, ntk_window);
    glfwSetWindowSizeCallback(window, window_size_callback);

    GLint gl_major_version;
    GLint gl_minor_version;
    glGetIntegerv(GL_MAJOR_VERSION, &gl_major_version);
    glGetIntegerv(GL_MINOR_VERSION, &gl_minor_version);
    if (gl_major_version < 3
        || (gl_major_version == 3 && gl_minor_version < 3)) {
        fprintf(stderr,
                "ERROR: Unsupported OpenGL version: %d.%d (in other words, buy "
                "a newer GPU)\n",
                gl_major_version, gl_minor_version);
        return -1;
    }
    printf("Using OpenGL %d.%d\n", gl_major_version, gl_minor_version);

    rlViewport(0, 0, ntk_window->width, ntk_window->height);
    rlMatrixMode(RL_PROJECTION);
    rlLoadIdentity();
    rlOrtho(0, ntk_window->width, ntk_window->height, 0, 0.0f, 1.0f);
    rlMatrixMode(RL_MODELVIEW);
    rlLoadIdentity();

    while (!glfwWindowShouldClose(window)) {
        uint8_t background_color[4];
        int_to_array(BACKGROUND_COLOR, background_color);
        rlClearColor(background_color[0], background_color[1],
                     background_color[2], background_color[3]);
        rlClearScreenBuffers();

        Rectangle rectangle = {
            .x = WIDGET_PADDING,
            .y = WIDGET_PADDING,
            .width = ntk_window->width - (WIDGET_PADDING * 2),
            .height = ntk_window->height - (WIDGET_PADDING * 2),
        };
        draw_widget(window, rectangle, ntk_window->main_widget);

        update_input_state(window);
        rlDrawRenderBatchActive();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    rlglClose();
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
