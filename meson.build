project('io.github.Miqueas.Inspector', 'c')

gtk4_dep = dependency('gtk4', required: true)
libcjson_dep = dependency('libcjson', required: true)
libadwaita_dep = dependency('libadwaita-1', required: true)

find_program('exiftool', required: true)

subdir('data')
subdir('src')