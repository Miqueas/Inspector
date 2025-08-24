#ifndef __INSPECTOR_APP_H__
#define __INSPECTOR_APP_H__

#include <adwaita.h>

G_BEGIN_DECLS

#define INSPECTOR_TYPE_APP (inspector_app_get_type())
#define INSPECTOR_APP(obj) (G_TYPE_CHECK_INSTANCE_CAST((obj), INSPECTOR_TYPE_APP, InspectorApp))
#define INSPECTOR_APP_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST((klass), INSPECTOR_TYPE_APP, InspectorAppClass))
#define INSPECTOR_IS_APP(obj) (G_TYPE_CHECK_INSTANCE_TYPE((obj), INSPECTOR_TYPE_APP))
#define INSPECTOR_IS_APP_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE((klass), INSPECTOR_TYPE_APP))
#define INSPECTOR_APP_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS((obj), INSPECTOR_TYPE_APP, InspectorAppClass))

typedef struct _InspectorApp InspectorApp;
typedef struct _InspectorAppClass InspectorAppClass;

struct _InspectorApp {
  AdwApplication parent_instance;
};

struct _InspectorAppClass {
  AdwApplicationClass parent_class;
};

GType inspector_app_get_type(void) G_GNUC_CONST;
G_DEFINE_AUTOPTR_CLEANUP_FUNC(InspectorApp, g_object_unref)
InspectorApp* inspector_app_new(void);

G_END_DECLS

#endif /* __INSPECTOR_APP_H__ */