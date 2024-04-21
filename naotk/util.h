#ifndef UTIL_H_
#define UTIL_H_

#include <stdint.h>

int get_id(void);

void int_to_array(uint32_t color, uint8_t dst[4]);
uint32_t array_to_int(uint8_t array[4]);

uint32_t color_brightness(uint32_t color, int brightness);

#endif // UTIL_H_
