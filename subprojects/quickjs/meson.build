project('quickjs', 'c',
    default_options: [ 'warning_level=1' ]
)

quickjs_source = [
    'cutils.c',
    'cutils.h',
    'dtoa.c',
    'dtoa.h',
    'libregexp.c',
    'libregexp.h',
    'libregexp-opcode.h',
    'libunicode.c',
    'libunicode.h',
    'libunicode-table.h',
    'quickjs-atom.h',
    'quickjs.c',
    'quickjs.h',
    'quickjs-opcode.h',
]

flags = [ '-D_GNU_SOURCE', '-DCONFIG_VERSION="thirty"' ]

if meson.get_compiler('c').get_id() == 'gcc'
    flags += [ '-Wno-array-bounds', '-Wno-format-truncation', '-Wno-infinite-recursion', '-Wno-unused-parameter', '-Wno-sign-compare' ]
endif

inc = include_directories('.')
quickjs = static_library('quickjs', quickjs_source, c_args: flags, include_directories: inc)
quickjs_dep = declare_dependency(link_with: quickjs, include_directories: inc)