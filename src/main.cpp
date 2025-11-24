#include "utils/configmanager.h"
#include "utils/loggingmanager.h"
#include "utils/uuid.h"

#include <gtkmm-4.0/gtkmm.h>

class MainWindow : public Gtk::Window {
public:
  MainWindow();
};

MainWindow::MainWindow() {
  set_title("Recipe Book");
  set_default_size(300, 400);
}

int main(int argc, char **argv) {
  LoggingManager::init();

  g_message("Recipe Book application starting (built with log level: %s)",
            LOG_LEVEL_STRING);

  auto app = Gtk::Application::create(APPLICATION_ID);

  ConfigManager::init();

  g_info("Software successfully configured and ready to run");

  std::string uuid = Uuid::generate();
  g_info("Generated uuid: %s", uuid.c_str());
  g_info("Uuid %s checked for validity: %d", uuid.c_str(), Uuid::isValid(uuid));

  int result = app->make_window_and_run<MainWindow>(argc, argv);

  g_info("Software shutting down");

  return result;
}
