#include "configmanager.h"
#include "glibmm/error.h"

#include <iostream>
#include <string>

ConfigManager *ConfigManager::m_instance = nullptr;

std::string ConfigManager::get_config_path() {
  // Get XDG config directory
  std::string config_dir =
      std::string(g_get_user_config_dir()) + "/recipe-book/";

  // Create directory if it doesn't exist
  Glib::RefPtr<Gio::File> dir = Gio::File::create_for_path(config_dir);
  if (!dir->query_exists()) {
    dir->make_directory_with_parents();
  }

  return config_dir + "config.conf";
}

void ConfigManager::save_config() {
  std::string path = get_config_path();
  try {
    m_keyfile->save_to_file(path);
    m_wasModified = false;
  } catch (const Glib::Error &ex) {
    std::cerr << "Error saving config:" << ex.what() << std::endl;
  }
}

void ConfigManager::load_config() {
  std::string path = get_config_path();
  if (!Glib::file_test(path, Glib::FileTest::EXISTS)) {
    std::cout << "Config file not found" << std::endl;
    throw Glib::Error();
  }

  try {
    m_keyfile->load_from_file(path);
  } catch (const Glib::Error &ex) {
    std::cerr << "Error loading config:" << ex.what() << std::endl;
    throw ex;
  }
}

void ConfigManager::create_config() {
  set<std::string>("General", "Language", "us_EN");

  set<std::string>("Display", "Theme", "dark");
  set("Display", "Width", 500);
  set("Display", "Height", 500);
}

ConfigManager::ConfigManager() {
  m_keyfile = Glib::KeyFile::create();

  // First we try to load the config
  try {
    std::cout << "Trying to load config" << std::endl;
    load_config();

    // If the file doesn't load, we create a config with default values
    // and save it to make sure the file exists
    // The error is already printed out in the load_config() function, so no
    // need to print it out again here.
  } catch (const Glib::Error &ex) {
    std::cout << "Trying to create a new config" << std::endl;
    create_config();
    save_config();
  }
}

ConfigManager &ConfigManager::init() {
  if (m_instance == nullptr) {
    m_instance = new ConfigManager();
  }
  return *m_instance;
}

ConfigManager &ConfigManager::getInstance() {
  if (m_instance == nullptr) {
    // If getInstance() is called before init(), initialize it
    return init();
  }
  return *m_instance;
}

ConfigManager::~ConfigManager() {
  // If we modified a value in the KeyFile, we save the file
  if (m_wasModified)
    save_config();
}

bool ConfigManager::hasKey(const std::string &section, const std::string &key) {
  return m_keyfile->has_group(section) && m_keyfile->has_key(section, key);
}

void ConfigManager::removeKey(const std::string &section,
                              const std::string &key) {}

std::vector<std::string> ConfigManager::getSections() const {
  std::vector<std::string> groups;

  for (auto i : m_keyfile->get_groups()) {
    groups.push_back(i);
  }

  return groups;
}

std::vector<std::string>
ConfigManager::getKeys(const std::string &section) const {
  if (!m_keyfile->has_group(section))
    return std::vector<std::string>();

  std::vector<std::string> keys;

  for (auto i : m_keyfile->get_keys(section)) {
    keys.push_back(i);
  }

  return keys;
}

void ConfigManager::save() { save_config(); }
