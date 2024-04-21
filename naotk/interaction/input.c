#include "input.h"

#include <stdbool.h>
#include <string.h>

#include <GLFW/glfw3.h>

#define MOUSE_BUTTON_MAX 8

struct {
    int previous_mouse_state[MOUSE_BUTTON_MAX];
    int mouse_state[MOUSE_BUTTON_MAX];
} RNDR;

bool is_mouse_button_just_pressed(int button)
{
    return RNDR.mouse_state[button] == GLFW_PRESS
        && RNDR.previous_mouse_state[button] == GLFW_RELEASE;
}

bool is_mouse_button_just_released(int button)
{
    return RNDR.mouse_state[button] == GLFW_RELEASE
        && RNDR.previous_mouse_state[button] == GLFW_PRESS;
}

void update_input_state(GLFWwindow* window)
{
    memcpy(RNDR.previous_mouse_state, RNDR.mouse_state,
           MOUSE_BUTTON_MAX * sizeof(*RNDR.mouse_state));
    for (size_t i = 0; i < MOUSE_BUTTON_MAX; ++i) {
        RNDR.mouse_state[i] = glfwGetMouseButton(window, i);
    }
}
