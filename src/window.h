#ifndef __INSPECTOR_WINDOW_H__
#define __INSPECTOR_WINDOW_H__

#include <adwaita.h>

G_BEGIN_DECLS

#define INSPECTOR_TYPE_WINDOW (inspector_window_get_type())
#define INSPECTOR_WINDOW(obj) (G_TYPE_CHECK_INSTANCE_CAST((obj), INSPECTOR_TYPE_WINDOW, InspectorWindow))
#define INSPECTOR_WINDOW_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST((klass), INSPECTOR_TYPE_WINDOW, InspectorWindowClass))
#define INSPECTOR_IS_WINDOW(obj) (G_TYPE_CHECK_INSTANCE_TYPE((obj), INSPECTOR_TYPE_WINDOW))
#define INSPECTOR_IS_WINDOW_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE((klass), INSPECTOR_TYPE_WINDOW))
#define INSPECTOR_WINDOW_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS((obj), INSPECTOR_TYPE_WINDOW, InspectorWindowClass))

typedef struct _InspectorWindow InspectorWindow;
typedef struct _InspectorWindowClass InspectorWindowClass;

struct _InspectorWindow {
  AdwApplicationWindow parent_instance;
};

struct _InspectorWindowClass {
  AdwApplicationWindowClass parent_class;
};

GType inspector_window_get_type(void) G_GNUC_CONST;
G_DEFINE_AUTOPTR_CLEANUP_FUNC(InspectorWindow, g_object_unref)
InspectorWindow* inspector_window_new(InspectorApp* app);

G_END_DECLS

#endif /* __INSPECTOR_WINDOW_H__ */