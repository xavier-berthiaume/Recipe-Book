/**
 * @file loggingmanager.h
 * @brief Utility class centered around logging. Uses the Glib built-in library
 * for handling different log levels.
 */
#ifndef LOGGINGMANAGER_H
#define LOGGINGMANAGER_H

#include <glibmm.h>

/**
 * @brief Singleton implementation of a class that manages the logging needs of
 * the software.
 *
 * Makes use of the Glibmm logging functionality to output logs to a target
 * directory defined in the softwares configuration file.
 Uses*/
class LoggingManager {

  /**
   * @brief Constructor for the LoggingManager class
   *
   * There should only be 1 instance of the logging manager in use throughout
   * the softwares lifecycle to keep output consistent. This class is
   * implemented as a singleton that must be globally accessible.
   */
  explicit LoggingManager();

  /**
   * @brief Converts the Glib log level to a human readable string.
   * @return A string representation of the log level.
   */
  const char *getLogLevelName(GLogLevelFlags level) const;

  /**
   * @breif Formats the output of the log. Also checks if a message should be
   * logged based on log level.
   */
  void customLogHandler(const gchar *log_domain, GLogLevelFlags level,
                        const gchar *message);

  static LoggingManager *m_instance;

  GLogLevelFlags m_minLogLevel;

public:
  /**
   * @brief Initializer class for the singleton instance of LoggingManager
   * @return Reference to the singleton instance
   */
  static LoggingManager &init();

  /**
   * @brief Get the singleton instance
   * @return Reference to the singleton instance
   */
  static LoggingManager &getInstance();

  LoggingManager(const LoggingManager &) = delete;
  LoggingManager &operator=(const LoggingManager &) = delete;

  ~LoggingManager();

  /**
   * @brief Calls the instance of the log and logs a given message.
   *
   * Validation is done within the customLogHandler() function.
   * @see customLogHandler()
   */
  static void logHandlerWrapper(const gchar *log_domain,
                                GLogLevelFlags log_level, const gchar *message,
                                gpointer user_data);
};

#endif
