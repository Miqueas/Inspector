#include "app.h"
#include "utils.h"
#include "consts.h"
#include "window.h"

static gpointer inspector_window_parent_class = NULL;

InspectorWindow*
inspector_window_new(InspectorApp* app)
{
  InspectorWindow* self = g_object_new(
    INSPECTOR_TYPE_WINDOW,
    "application", app,
    "default-width", 600,
    "default-height", 800,
    NULL
  );

  return self;
}

static gboolean
inspector_window_do_close_request(GtkWindow* base)
{
  InspectorWindow* self = INSPECTOR_WINDOW(base);
  GtkApplication* app = gtk_window_get_application(GTK_WINDOW(self));
  g_application_quit(G_APPLICATION(app));
  return FALSE;
}

static void
inspector_window_do_constructed(GObject* base)
{
  InspectorWindow* self = INSPECTOR_WINDOW(base);
  GtkWidget* toolbar_view = adw_toolbar_view_new();
  GtkWidget* header_bar = adw_header_bar_new();
  GtkWidget* search_toggle = gtk_toggle_button_new();
  GtkWidget* search_icon = gtk_image_new_from_resource("/io/github/Miqueas/Inspector/icons/loupe-symbolic.svg");
  GtkWidget* window_title = adw_window_title_new(INSPECTOR_APP_NAME, "");
  GtkWidget* clamp = adw_clamp_new();
  GtkWidget* list_view = gtk_list_view_new(NULL, NULL);

  gtk_widget_add_css_class(list_view, "card");

  adw_clamp_set_child(ADW_CLAMP(clamp), list_view);
  gtk_widget_set_margin_start(clamp, 12);
  gtk_widget_set_margin_end(clamp, 12);
  gtk_widget_set_margin_top(clamp, 12);
  gtk_widget_set_margin_bottom(clamp, 12);

  gtk_button_set_child(GTK_BUTTON(search_toggle), search_icon);

  adw_header_bar_pack_start(ADW_HEADER_BAR(header_bar), search_toggle);
  adw_header_bar_set_title_widget(ADW_HEADER_BAR(header_bar), window_title);

  adw_toolbar_view_set_content(ADW_TOOLBAR_VIEW(toolbar_view), clamp);
  adw_toolbar_view_add_top_bar(ADW_TOOLBAR_VIEW(toolbar_view), header_bar);

  adw_application_window_set_content(
    ADW_APPLICATION_WINDOW(self),
    toolbar_view
  );
}

static void
inspector_window_instance_init(InspectorWindow* self,
                               gpointer klass)
{
  // TODO: Initialize instance members
}

static void
inspector_window_finalize(GObject* obj)
{
  InspectorWindow* self = INSPECTOR_WINDOW(obj);
  // TODO: Clean up resources
  G_OBJECT_CLASS(inspector_window_parent_class)->finalize(obj);
}

static void
inspector_window_class_init(InspectorWindowClass *klass,
                            gpointer klass_data)
{
  inspector_window_parent_class = g_type_class_peek_parent(klass);
  GTK_WINDOW_CLASS(klass)->close_request = inspector_window_do_close_request;
  G_OBJECT_CLASS(klass)->constructed = inspector_window_do_constructed;
  G_OBJECT_CLASS(klass)->finalize = inspector_window_finalize;
}

static GType
inspector_window_get_type_once(void)
{
  static const GTypeInfo type_info = {
    .class_size = sizeof (InspectorWindowClass),
    .base_init = (GBaseInitFunc) NULL,
    .base_finalize = (GBaseFinalizeFunc) NULL,
    .class_init = (GClassInitFunc) inspector_window_class_init,
    .class_finalize = (GClassFinalizeFunc) NULL,
    .class_data = NULL,
    .instance_size = sizeof (InspectorWindow),
    .n_preallocs = 0,
    .instance_init = (GInstanceInitFunc) inspector_window_instance_init,
    .value_table = NULL
  };

  GType type_id = g_type_register_static(
    adw_application_window_get_type(),
    "InspectorWindow",
    &type_info,
    0
  );

  return type_id;
}

GType
inspector_window_get_type(void)
{
  static volatile gsize type_id_once = 0;

  PUSH_IGNORE_DISCARDS_VOLATILE
  if (g_once_init_enter(&type_id_once)) {\
  POP_IGNORE_DISCARDS_VOLATILE
    GType type_id = inspector_window_get_type_once();
    g_once_init_leave(&type_id_once, type_id);
  }

  return type_id_once;
}