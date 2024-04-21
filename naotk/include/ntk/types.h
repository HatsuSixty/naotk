#ifndef NTK_TYPES_H_
#define NTK_TYPES_H_

typedef struct Ntk_List Ntk_List;

typedef enum Ntk_Widget_Type Ntk_Widget_Type;
typedef struct Ntk_Widget Ntk_Widget;
typedef struct Ntk_Button Ntk_Button;
typedef struct Ntk_Row_Container Ntk_Row_Container;

typedef struct Ntk_Window Ntk_Window;

typedef struct {
    float x;
    float y;
} Vector2;

typedef struct {
    float x;
    float y;
    float width;
    float height;
} Rectangle;

#endif // NTK_TYPES_H_
