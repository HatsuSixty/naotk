#ifndef SHAPES_H_
#define SHAPES_H_

#include "ntk/types.h"

#include <stdbool.h>
#include <stdint.h>

void draw_rectangle(Rectangle rectangle, uint32_t color);
void draw_rectangle_rounded(Rectangle rec, float roundness, int segments,
                            uint32_t color);

bool check_collision_point(Vector2 point, Rectangle rec);

#endif // SHAPES_H_
