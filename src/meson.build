src = [
  resources,
  'window.c',
  'app.c',
  'main.c',
]

executable(
  meson.project_name(),
  src,
  install: true,
  dependencies: [
    gtk4_dep,
    libcjson_dep,
    libadwaita_dep,
  ],
)