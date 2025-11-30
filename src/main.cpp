#include "utils/configmanager.h"
#include "utils/loggingmanager.h"

#include <gtkmm-4.0/gtkmm.h>

class MainWindow : public Gtk::Window {
public:
  MainWindow();
};

MainWindow::MainWindow() {
  set_title("Recipe Book");
  set_default_size(ConfigManager::getInstance().get("Display", "Width", 500),
                   ConfigManager::getInstance().get("Display", "Height", 500));
}

auto main(int argc, char **argv) -> int {
  LoggingManager::init();

  g_message("Recipe Book application starting (built with log level: %s)",
            LOG_LEVEL_STRING);

  auto app = Gtk::Application::create(APPLICATION_ID);

  ConfigManager::init();

  g_info("Software successfully configured and ready to run");

  int result = app->make_window_and_run<MainWindow>(argc, argv);

  g_info("Software shutting down");

  return result;
}
