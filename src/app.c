#include "app.h"
#include "utils.h"
#include "consts.h"
#include "window.h"

static gpointer inspector_app_parent_class = NULL;

InspectorApp*
inspector_app_new(void)
{
  InspectorApp* self = g_object_new(
    INSPECTOR_TYPE_APP,
    "application-id", INSPECTOR_APP_ID,
    "flags", G_APPLICATION_HANDLES_OPEN,
    NULL
  );

  return self;
}

static void
inspector_app_do_startup(GApplication* base)
{
  InspectorApp* self = INSPECTOR_APP(base);
  G_APPLICATION_CLASS(inspector_app_parent_class)->startup(G_APPLICATION(self));

  InspectorWindow* window = inspector_window_new(self);
  g_object_ref_sink(window);
  CLEAR(window);
}

static void
_inspector_app_show_window(InspectorApp* self)
{
  GtkWindow *window = gtk_application_get_active_window(GTK_APPLICATION(self));
  if (window != NULL) gtk_window_present(window);
}

static void
inspector_app_do_activate(GApplication* base)
{
  _inspector_app_show_window(INSPECTOR_APP(base));
}

static void
inspector_app_do_open(GApplication* base,
                      GFile** files,
                      gint n_files,
                      const gchar* hint)
{
  _inspector_app_show_window(INSPECTOR_APP(base));

  if (n_files == 0) return;

  for (gint i = 0; i < n_files; i++) {
    gchar* path = g_file_get_path(files[i]);
    g_print("Opened file: %s\n", path);
    g_free(path);
  }
}

static void
inspector_app_class_init(InspectorAppClass* klass, gpointer _)
{
  inspector_app_parent_class = g_type_class_peek_parent(klass);
  G_APPLICATION_CLASS(klass)->startup = inspector_app_do_startup;
  G_APPLICATION_CLASS(klass)->activate = inspector_app_do_activate;
  G_APPLICATION_CLASS(klass)->open = inspector_app_do_open;
}

static GType
inspector_app_get_type_once (void)
{
  static const GTypeInfo type_info = {
    .class_size = sizeof (InspectorAppClass),
    .base_init = (GBaseInitFunc) NULL,
    .base_finalize = (GBaseFinalizeFunc) NULL,
    .class_init = (GClassInitFunc) inspector_app_class_init,
    .class_finalize = (GClassFinalizeFunc) NULL,
    .class_data = NULL,
    .instance_size = sizeof (InspectorApp),
    .n_preallocs = 0,
    .instance_init = (GInstanceInitFunc) NULL,
    .value_table = NULL
  };

  GType type_id = g_type_register_static(
    adw_application_get_type(),
    "InspectorApp",
    &type_info,
    0
  );

  return type_id;
}

GType
inspector_app_get_type(void)
{
  static volatile gsize type_id_once = 0;

  PUSH_IGNORE_DISCARDS_VOLATILE
  if (g_once_init_enter(&type_id_once)) {
  POP_IGNORE_DISCARDS_VOLATILE
    GType type_id = inspector_app_get_type_once();
    g_once_init_leave(&type_id_once, type_id);
  }

  return type_id_once;
}