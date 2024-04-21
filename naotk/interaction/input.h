#ifndef INPUT_H_
#define INPUT_H_

#include <stdbool.h>

#include <GLFW/glfw3.h>

bool is_mouse_button_just_pressed(int button);
bool is_mouse_button_just_released(int button);

void update_input_state(GLFWwindow* window);

#endif // INPUT_H_
