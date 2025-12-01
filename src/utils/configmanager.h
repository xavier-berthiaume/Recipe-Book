/**
 * @file configmanager.h
 * @brief Utility class that stores in memory config data. Saves and loades the
 * data to a file in the users ~/.config folder, in a subdirectory named
 * recipe-book.
 */
#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

#include <glibmm.h>
#include <gtkmm-4.0/gtkmm.h>
#include <string>

/**
 * @brief Singleton implementation of a class that manages the current software
 * configuration as well as manages loading the previously set configuration.
 */
class ConfigManager
{

  /**
   * @brief Static function that returns the path where the softwares config
   * file should be.
   */
  static auto get_config_path() -> std::string;

  /**
   * @brief Writes to a config files the current settings saved to this class.
   */
  void save_config();

  /**
   * @brief Loads from a config file the different settings for the software and
   * saves them to this classes attributes.
   */
  void load_config();

  /**
   * @brief Creates a new config KeyFile with default values
   */
  void create_config();

  /**
   * @brief Constructor for the ConfigManager class
   *
   * Since there should only be 1 instance of the softwares configuration during
   * the lifecycle of the software, this class is implemented as a singleton
   * that's globally accessible.
   */
  explicit ConfigManager();

  /**
   * @brief The individual KeyFile reference where configuration data is stored.
   */
  Glib::RefPtr<Glib::KeyFile> m_keyfile;

  /**
   * @brief Keeps track of whether or not the configuration file was changed
   * since the last save/load.
   */
  bool m_was_modified = false;

  static ConfigManager *m_instance;

public:
  /**
   * @brief Initializer class for the singleton instance of ConfigManager
   * @return Reference to the singleton instance
   */
  static auto init() -> ConfigManager &;

  /**
   * @brief Get the singleton instance
   * @return Reference to the singleton instance
   */
  static auto getInstance() -> ConfigManager &;

  ConfigManager(const ConfigManager &) = delete;
  auto operator=(const ConfigManager &) -> ConfigManager = delete;
  ConfigManager(ConfigManager &&) = delete;
  auto operator=(ConfigManager &&) -> ConfigManager = delete;

  ~ConfigManager();

  /**
   * @brief Generic getter with a default value field.
   *
   * Since this function makes the use of templates, its implementation is in
   * the header file.
   */
  template <typename T>
  auto get(const std::string &section, const std::string &key,
           const T &default_value) -> T
  {
    if (!m_keyfile->has_group(section) || !m_keyfile->has_key(section, key))
    {
      return default_value;
    }

    try
    {
      if constexpr (std::is_same_v<T, int>)
      {
        return m_keyfile->get_integer(section, key);
      }
      else if constexpr (std::is_same_v<T, bool>)
      {
        return m_keyfile->get_boolean(section, key);
      }
      else if constexpr (std::is_same_v<T, double>)
      {
        return m_keyfile->get_double(section, key);
      }
      else if constexpr (std::is_same_v<T, std::string>)
      {
        return m_keyfile->get_string(section, key);
      }
      else if constexpr (std::is_same_v<T, std::vector<std::string>>)
      {
        return m_keyfile->get_string_list(section, key);
      }
      else if constexpr (std::is_same_v<T, const char *>)
      {
        return m_keyfile->get_string(section, key);
      }
    }
    catch (const Glib::Error &ex)
    {
      g_error("Error reading from config: %s", ex.what());
    }
  }

  /**
   * @brief Generic setter
   */
  template <typename T>
  void set(const std::string &section, const std::string &key, const T &value)
  {
    try
    {
      if constexpr (std::is_same_v<T, int>)
      {
        m_keyfile->set_integer(section, key, value);
        m_was_modified = true;
      }
      else if constexpr (std::is_same_v<T, bool>)
      {
        m_keyfile->set_boolean(section, key, value);
        m_was_modified = true;
      }
      else if constexpr (std::is_same_v<T, double>)
      {
        m_keyfile->set_double(section, key, value);
        m_was_modified = true;
      }
      else if constexpr (std::is_same_v<T, std::string>)
      {
        m_keyfile->set_string(section, key, value);
        m_was_modified = true;
      }
      else if constexpr (std::is_same_v<T, std::vector<std::string>>)
      {
        m_keyfile->set_string_list(section, key, value);
        m_was_modified = true;
      }
      else if constexpr (std::is_same_v<T, const char *>)
      {
        m_keyfile->set_string(section, key, value);
        m_was_modified = true;
      }
    }
    catch (const Glib::Error &ex)
    {
      g_error("Error setting config: %s", ex.what());
    }
  }

  /**
   * @brief Checks if a key is present in the KeyFile
   */
  auto hasKey(const std::string &section, const std::string &key) -> bool;

  /**
   * @brief Removes a key
   */
  void removeKey(const std::string &section, const std::string &key);

  /**
   * @brief Gets all sections
   */
  [[nodiscard]] auto getSections() const -> std::vector<std::string>;

  /**
   * @brief Gets all keys in a section
   */
  [[nodiscard]] auto getKeys(const std::string &section) const
      -> std::vector<std::string>;

  /**
   * @brief Publicly exposed save function
   */
  void save();
};
#endif
