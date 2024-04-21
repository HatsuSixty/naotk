naotk_inc = include_directories('include')

c_compiler = meson.get_compiler('c')
if not c_compiler.compiles('#include <rlgl.h>')
  error('Could not find `rlgl.h` in your include path. Please make sure you have the raylib headers installed in your system')
endif

naotk = library(
  'naotk', [
    'widgets/button.c',
    'widgets/row_container.c',
    'util.c',
    'list.c',
    'window.c',
    'interaction/ui.c',
    'interaction/shapes.c',
    'interaction/input.c',
    'rlgl.c',
  ], include_directories : [
    naotk_inc,
  ], dependencies : [
    dependency('glfw3'),
    dependency('gl'),
  ],
  link_args : ['-lm'],
)
