project('Pixie', 'cpp',
    default_options: [ 'cpp_std=c++11' ])

ID = 'com.github.fabiocolacio.pixie'
EXECUTABLE_NAME = 'pixie'

gnome = import('gnome')

src = [
    'src/pixie.cpp',
    'src/pixie-application.cpp',
    'src/pixie-layer.cpp',
    'src/pixie-sprite.cpp',
    'src/pixie-sprite-editor.cpp'
]

deps = [
    dependency('gtkmm-3.0'),
    dependency('glibmm-2.4'),
    dependency('sigc++-2.0')
]

executable(
    EXECUTABLE_NAME,
    sources: src,
    dependencies: deps
)
