#include "app.h"
#include "utils.h"

int main(int argc, char *argv[]) {
  InspectorApp* app = inspector_app_new();
  gint result = g_application_run(G_APPLICATION(app), argc, argv);
  CLEAR(app);
  return result;
}