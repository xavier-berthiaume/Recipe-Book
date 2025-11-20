#include "utils/configmanager.h"

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
  auto app = Gtk::Application::create("org.gtk.example");

  // Initialize the software configuration
  ConfigManager::init();

  return app->make_window_and_run<MainWindow>(argc, argv);
}
