#include "shapes.h"

// Code for drawing shapes
// Mostly copy-pasted from raylib

#include <math.h>

#include <rlgl.h>

#include "util.h"

#define DEG2RAD (PI / 180.0f)
#define SMOOTH_CIRCLE_ERROR_RATE 0.5f
#define PI 3.14159265358979323846f

void draw_rectangle_rounded(Rectangle rec, float roundness, int segments,
                            uint32_t color)
{
    // Not a rounded rectangle
    if ((roundness <= 0.0f) || (rec.width < 1) || (rec.height < 1)) {
        draw_rectangle(rec, color);
        return;
    }

    uint8_t color_array[4];
    int_to_array(color, color_array);

    if (roundness >= 1.0f)
        roundness = 1.0f;

    // Calculate corner radius
    float radius = (rec.width > rec.height) ? (rec.height * roundness) / 2
                                            : (rec.width * roundness) / 2;
    if (radius <= 0.0f)
        return;

    // Calculate number of segments to use for the corners
    if (segments < 4) {
        // Calculate the maximum angle between segments based on the error rate
        // (usually 0.5f)
        float th
            = acosf(2 * powf(1 - SMOOTH_CIRCLE_ERROR_RATE / radius, 2) - 1);
        segments = (int)(ceilf(2 * PI / th) / 4.0f);
        if (segments <= 0)
            segments = 4;
    }

    float stepLength = 90.0f / (float)segments;

    /*
    Quick sketch to make sense of all of this,
    there are 9 parts to draw, also mark the 12 points we'll use

          P0____________________P1
          /|                    |\
         /1|          2         |3\
     P7 /__|____________________|__\ P2
       |   |P8                P9|   |
       | 8 |          9         | 4 |
       | __|____________________|__ |
     P6 \  |P11              P10|  / P3
         \7|          6         |5/
          \|____________________|/
          P5                    P4
    */
    // Coordinates of the 12 points that define the rounded rect
    Vector2 const point[12] = {
        { (float)rec.x + radius, rec.y },
        { (float)(rec.x + rec.width) - radius, rec.y },
        { rec.x + rec.width, (float)rec.y + radius }, // PO, P1, P2
        { rec.x + rec.width, (float)(rec.y + rec.height) - radius },
        { (float)(rec.x + rec.width) - radius, rec.y + rec.height }, // P3, P4
        { (float)rec.x + radius, rec.y + rec.height },
        { rec.x, (float)(rec.y + rec.height) - radius },
        { rec.x, (float)rec.y + radius }, // P5, P6, P7
        { (float)rec.x + radius, (float)rec.y + radius },
        { (float)(rec.x + rec.width) - radius,
          (float)rec.y + radius }, // P8, P9
        { (float)(rec.x + rec.width) - radius,
          (float)(rec.y + rec.height) - radius },
        { (float)rec.x + radius,
          (float)(rec.y + rec.height) - radius } // P10, P11
    };

    Vector2 const centers[4] = { point[8], point[9], point[10], point[11] };
    float const angles[4] = { 180.0f, 270.0f, 0.0f, 90.0f };

    rlBegin(RL_TRIANGLES);

    // Draw all of the 4 corners: [1] Upper Left Corner, [3] Upper Right Corner,
    // [5] Lower Right Corner, [7] Lower Left Corner
    for (int k = 0; k < 4;
         ++k) // Hope the compiler is smart enough to unroll this loop
    {
        float angle = angles[k];
        Vector2 const center = centers[k];
        for (int i = 0; i < segments; i++) {
            rlColor4ub(color_array[0], color_array[1], color_array[2],
                       color_array[3]);
            rlVertex2f(center.x, center.y);
            rlVertex2f(center.x + cosf(DEG2RAD * (angle + stepLength)) * radius,
                       center.y
                           + sinf(DEG2RAD * (angle + stepLength)) * radius);
            rlVertex2f(center.x + cosf(DEG2RAD * angle) * radius,
                       center.y + sinf(DEG2RAD * angle) * radius);
            angle += stepLength;
        }
    }

    // [2] Upper Rectangle
    rlColor4ub(color_array[0], color_array[1], color_array[2], color_array[3]);
    rlVertex2f(point[0].x, point[0].y);
    rlVertex2f(point[8].x, point[8].y);
    rlVertex2f(point[9].x, point[9].y);
    rlVertex2f(point[1].x, point[1].y);
    rlVertex2f(point[0].x, point[0].y);
    rlVertex2f(point[9].x, point[9].y);

    // [4] Right Rectangle
    rlColor4ub(color_array[0], color_array[1], color_array[2], color_array[3]);
    rlVertex2f(point[9].x, point[9].y);
    rlVertex2f(point[10].x, point[10].y);
    rlVertex2f(point[3].x, point[3].y);
    rlVertex2f(point[2].x, point[2].y);
    rlVertex2f(point[9].x, point[9].y);
    rlVertex2f(point[3].x, point[3].y);

    // [6] Bottom Rectangle
    rlColor4ub(color_array[0], color_array[1], color_array[2], color_array[3]);
    rlVertex2f(point[11].x, point[11].y);
    rlVertex2f(point[5].x, point[5].y);
    rlVertex2f(point[4].x, point[4].y);
    rlVertex2f(point[10].x, point[10].y);
    rlVertex2f(point[11].x, point[11].y);
    rlVertex2f(point[4].x, point[4].y);

    // [8] Left Rectangle
    rlColor4ub(color_array[0], color_array[1], color_array[2], color_array[3]);
    rlVertex2f(point[7].x, point[7].y);
    rlVertex2f(point[6].x, point[6].y);
    rlVertex2f(point[11].x, point[11].y);
    rlVertex2f(point[8].x, point[8].y);
    rlVertex2f(point[7].x, point[7].y);
    rlVertex2f(point[11].x, point[11].y);

    // [9] Middle Rectangle
    rlColor4ub(color_array[0], color_array[1], color_array[2], color_array[3]);
    rlVertex2f(point[8].x, point[8].y);
    rlVertex2f(point[11].x, point[11].y);
    rlVertex2f(point[10].x, point[10].y);
    rlVertex2f(point[9].x, point[9].y);
    rlVertex2f(point[8].x, point[8].y);
    rlVertex2f(point[10].x, point[10].y);
    rlEnd();
}

void draw_rectangle(Rectangle rectangle, uint32_t color)
{
    uint8_t color_array[4];
    int_to_array(color, color_array);

    rlBegin(RL_TRIANGLES);

    rlColor4ub(color_array[0], color_array[1], color_array[2], color_array[3]);

    rlVertex2f(rectangle.x, rectangle.y);
    rlVertex2f(rectangle.x, rectangle.y + rectangle.height);
    rlVertex2f(rectangle.x + rectangle.width, rectangle.y + rectangle.height);

    rlVertex2f(rectangle.x, rectangle.y);
    rlVertex2f(rectangle.x + rectangle.width, rectangle.y + rectangle.height);
    rlVertex2f(rectangle.x + rectangle.width, rectangle.y);

    rlEnd();
}

bool check_collision_point(Vector2 point, Rectangle rec)
{
    bool collision = false;

    if ((point.x >= rec.x) && (point.x < (rec.x + rec.width))
        && (point.y >= rec.y) && (point.y < (rec.y + rec.height)))
        collision = true;

    return collision;
}
