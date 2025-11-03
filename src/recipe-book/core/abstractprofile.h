/**
 * @file abstractprofile.h
 * @brief Abstract class that defines the data fields of a user account. This
 * outline is being defined in anticipation of different kinds of user accounts.
 */
#ifndef ABSTRACTPROFILE_H
#define ABSTRACTPROFILE_H

#include <QObject>
#include <QString>

/**
 * @brief Abstract class that defines the base data required to create a user
 * account. This abstraction doesn't reference or define any means of
 * authentication.
 *
 * The following fields are added:
 * - m_screen_name : The string representation of a users display name. This
 * name will potentially be shared in network-related activities so the user
 * must be concious that it will be publicly available.
 * - m_first_name : The users first name. This name must not be publicly
 * available.
 * - m_last_name : The users last name. This name must not be publicly
 * available.
 * - is_locked : If an account is currently locked or not.
 *
 * @note This class is movable and copyable.
 */
class AbstractProfile {
  Q_OBJECT

  Q_PROPERTY(QString m_screen_name READ getScreenName WRITE setScreenName NOTIFY
                 screenNameChanged)
  Q_PROPERTY(QString m_first_name READ getFirstName WRITE setFirstName NOTIFY
                 firstNameChanged)
  Q_PROPERTY(QString m_last_name READ getLastName WRITE setLastName NOTIFY
                 lastNameChanged)
  Q_PROPERTY(bool m_is_locked READ getIsLocked WRITE setIsLocked NOTIFY
                 isLockedChanged)

  QString m_screen_name;
  QString m_first_name;
  QString m_last_name;
  bool m_is_locked;

protected:
  AbstractProfile(QString screen_name, QString first_name, QString last_name,
                  bool is_locked = true)
      : m_screen_name(std::move(screen_name)),
        m_first_name(std::move(first_name)), m_last_name(std::move(last_name)),
        m_is_locked(is_locked) {}

public:
  virtual ~AbstractProfile() = default;

  /** @brief Copy constructor */
  AbstractProfile(const AbstractProfile &other) noexcept
      : AbstractProfile(other.getScreenName(), other.getFirstName(),
                        other.getLastName(), other.getIsLocked()) {}

  /** @brief Move constructor */
  AbstractProfile(AbstractProfile &&other) noexcept
      : AbstractProfile(other.getScreenName(), other.getFirstName(),
                        other.getLastName(), other.getIsLocked()) {}

  /** @brief Copy assignment operator */
  auto operator=(const AbstractProfile &other) noexcept -> AbstractProfile & {
    if (this != &other) {
      m_screen_name = other.getScreenName();
      m_first_name = other.getFirstName();
      m_last_name = other.getLastName();
      m_is_locked = other.getIsLocked();
    }

    return *this;
  }

  /** @brief Move assignment operator */
  auto operator=(AbstractProfile &&other) noexcept -> AbstractProfile & {
    if (this != &other) {
      m_screen_name = other.getScreenName();
      m_first_name = other.getFirstName();
      m_last_name = other.getLastName();
      m_is_locked = other.getIsLocked();
    }

    return *this;
  }

  /** @brief Getter for the profiles display name */
  [[nodiscard]] auto getScreenName() const -> QString { return m_screen_name; }

  /** @brief Getter for the profile users first name */
  [[nodiscard]] auto getFirstName() const -> QString { return m_first_name; }

  /** @brief Getter for the profile users last name */
  [[nodiscard]] auto getLastName() const -> QString { return m_last_name; }

  /** @brief Getter that checks if the profile was unlocked through
   * authentication or not.
   *
   * @return true if the profile is currently locked and the user hasn't
   * authenticated yet
   * @return false if the profile is currently unlocked and the user has
   * previously successfully authenticated.
   * */
  [[nodiscard]] auto getIsLocked() const -> bool { return m_is_locked; }

  /**
   * @brief Setter for profiles display name
   */
  void setScreenName(QString screen_name) {
    if (screen_name != m_screen_name) {
      m_screen_name = std::move(screen_name);

      emit screenNameChanged();
    }
  }

  /**
   * @brief Setter for the profile users first name
   */
  void setFirstName(QString first_name) {
    if (first_name != m_first_name) {
      m_first_name = std::move(first_name);

      emit firstNameChanged();
    }
  }

  /**
   * @brief Setter for the profile users last name
   */
  void setLastName(QString last_name) {
    if (last_name != m_last_name) {
      m_last_name = std::move(last_name);

      emit lastNameChanged();
    }
  }

  /**
   * @brief Setter for the lock status of the profile
   */
  void setIsLocked(bool is_locked) {
    if (is_locked != m_is_locked) {
      m_is_locked = is_locked;

      emit isLockedChanged();
    }
  }

  /**
   * @brief This function is what should be called when the user can unlock a
   * given profile. This applies to profiles that don't have any security
   * measure, have single authentication or multi-factor authentication.
   */
  virtual void authenticate() = 0;

  /**
   * @brief This function locks the profile from access.
   */
  virtual void logout() = 0;

signals:
  void screenNameChanged();
  void firstNameChanged();
  void lastNameChanged();
  void isLockedChanged();
};

#endif
