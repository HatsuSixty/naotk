#include "util.h"

#include <stdint.h>

int id_counter;

int get_id(void) { return id_counter++; }

void int_to_array(uint32_t color, uint8_t dst[4])
{
    dst[0] = (uint8_t)(color >> 24) & 0xFF;
    dst[1] = (uint8_t)(color >> 16) & 0xFF;
    dst[2] = (uint8_t)(color >> 8) & 0xFF;
    dst[3] = (uint8_t)(color) & 0xFF;
}

uint32_t array_to_int(uint8_t array[4])
{
    uint32_t result = 0;
    result |= (uint32_t)array[0] << 24;
    result |= (uint32_t)array[1] << 16;
    result |= (uint32_t)array[2] << 8;
    result |= (uint32_t)array[3];
    return result;
}

uint32_t color_brightness(uint32_t color, int brightness)
{
    uint8_t color_array[4];
    int_to_array(color, color_array);

    uint8_t red = color_array[0];
    uint8_t green = color_array[1];
    uint8_t blue = color_array[2];

    red = (red + brightness > 255) ? 255 : red + brightness;
    green = (green + brightness > 255) ? 255 : green + brightness;
    blue = (blue + brightness > 255) ? 255 : blue + brightness;

    uint8_t new_color_array[4] = { red, green, blue, color_array[3] };
    return array_to_int(new_color_array);
}
