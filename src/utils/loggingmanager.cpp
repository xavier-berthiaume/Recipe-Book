#include "loggingmanager.h"

#include <iostream>

LoggingManager *LoggingManager::m_instance = nullptr;

LoggingManager::LoggingManager() : m_minLogLevel(DEFAULT_LOG_LEVEL) {
  // Set up custom log handler
  g_log_set_default_handler(logHandlerWrapper, this);

  g_message("Logging initialized. Level: %s", getLogLevelName(m_minLogLevel));
}

LoggingManager &LoggingManager::init() {
  if (m_instance == nullptr) {
    m_instance = new LoggingManager();
  }
  return *m_instance;
}

LoggingManager &LoggingManager::getInstance() {
  if (m_instance == nullptr) {
    return init();
  }
  return *m_instance;
}

const char *LoggingManager::getLogLevelName(GLogLevelFlags level) const {
  switch (level & G_LOG_LEVEL_MASK) {
  case G_LOG_LEVEL_ERROR:
    return "ERROR";
  case G_LOG_LEVEL_CRITICAL:
    return "CRITICAL";
  case G_LOG_LEVEL_WARNING:
    return "WARNING";
  case G_LOG_LEVEL_MESSAGE:
    return "INFO";
  case G_LOG_LEVEL_INFO:
    return "INFO";
  case G_LOG_LEVEL_DEBUG:
    return "DEBUG";
  default:
    return "UNKNOWN";
  }
}

void LoggingManager::customLogHandler(const gchar *log_domain,
                                      GLogLevelFlags level,
                                      const gchar *message) {
  // Skip messages below configured level
  if (level > m_minLogLevel) {
    return;
  }

  // Format timestamp
  auto now = Glib::DateTime::create_now_local();
  std::string timestamp = now.format("%H:%M:%S");

  const char *level_str = getLogLevelName(level);

  // Format output
  std::cerr << "[" << timestamp << "] [" << level_str << "] ";
  if (log_domain && log_domain[0] != '\0') {
    std::cerr << log_domain << ": ";
  }
  std::cerr << message << std::endl;
}

void LoggingManager::logHandlerWrapper(const gchar *log_domain,
                                       GLogLevelFlags log_level,
                                       const gchar *message,
                                       gpointer user_data) {
  LoggingManager *instance = static_cast<LoggingManager *>(user_data);
  instance->customLogHandler(log_domain, log_level, message);
}
