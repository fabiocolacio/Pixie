project('Pixie', 'c', 'cpp',
    default_options: [ 'cpp_std=c++11' ],
    version: '0.0.0')

PIXIE_REPO = 'https://github.com/fabiocolacio/Pixie'
PIXIE_WEBSITE = 'https://github.com/fabiocolacio/Pixie'

ID = 'com.github.fabiocolacio.pixie'
EXECUTABLE_NAME = 'pixie'

gnome = import('gnome')

res = gnome.compile_resources(
    'pixie_resources',
    'src/resources/pixie.gresources.xml',
    source_dir: 'src/resources'
)

src = [
    'src/pixie.cpp',
    'src/pixie-window.cpp',
    'src/pixie-session.cpp',
    'src/pixie-pencil.cpp',
    'src/pixie-rgba.cpp',
    'src/pixie-coord.cpp',
    'src/pixie-coordf.cpp',
    'src/pixie-rect.cpp',
    'src/pixie-rectf.cpp',
    'src/pixie-layer.cpp',
    'src/pixie-sprite.cpp',
    'src/pixie-document.cpp',
    res
]

deps = [
    dependency('gtkmm-3.0'),
    dependency('glibmm-2.4'),
    dependency('sigc++-2.0')
]

add_global_arguments(
    '-DPIXIE_VERSION="@0@"'.format(meson.project_version()),
    '-DPIXIE_REPO="@0@"'.format(PIXIE_REPO),
    '-DPIXIE_WEBSITE="@0@"'.format(PIXIE_WEBSITE),
    language: 'cpp'
)

executable(
    EXECUTABLE_NAME,
    sources: src,
    dependencies: deps
)
