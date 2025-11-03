/**
 * @file authenticatedprofile.h
 * @brief Decorator class that provides actual authentication mechanisms for a
 * profile.
 */
#ifndef AUTHENTICATEDPROFILE_H
#define AUTHENTICATEDPROFILE_H

#include "abstractprofile.h"

/**
 * @brief Decorator class that wraps an AbstractProfile object to provide
 * password-protected authentication.
 *
 * @note A hash of the password is stored, not the password itself.
 * @see AbstractProfile
 */
class AuthenticatedProfile : public AbstractProfile {
  Q_OBJECT

  const AbstractProfile m_profile;
  QByteArray m_password_hash;

  /**
   * @brief Parametrized constructor to be used when creating a new account.
   *
   * @note The plaintext password is passed and then hashed.
   */
  AuthenticatedProfile(QString screen_name, QString first_name,
                       QString last_name, QString password);
  /**
   * @brief Parametrized constructor to be used when loading an account.
   *
   * @note The password is already hashed.
   */
  AuthenticatedProfile(QString screen_name, QString first_name,
                       QString last_name, QByteArray password_hash);

protected:
  /**
   * @brief Logs in the user and unlocks their profile.
   *
   * @see AbstractProfile
   */
  void authenticate() override;

public:
  ~AuthenticatedProfile() override = default;

  /** @brief Copy constructor */
  AuthenticatedProfile(const AuthenticatedProfile &other) noexcept;

  /** @brief Move constructor */
  AuthenticatedProfile(AuthenticatedProfile &&other) noexcept;

  /** @brief Deleted copy assignment operator */
  auto operator=(const AuthenticatedProfile &other)
      -> AuthenticatedProfile & = delete;

  /** @brief Deleted move assignment operator */
  auto operator=(AuthenticatedProfile &&other)
      -> AuthenticatedProfile & = delete;

  /**
   * @brief Getter for the profile object.
   */
  [[nodiscard]] auto getProfile() noexcept -> AbstractProfile &;

  /**
   * @brief Setter for the password hash.
   *
   * Takes in a QString and creates a SHA256 hash.
   */
  void setPasswordHash(const QString &password);

  /**
   * @brief An overload of the authenticate() function that evaluates
   * credentials before unlocking a profile.
   */
  void authenticate(const QString &password);

  /**
   * @brief Logs out the user and locks their profile providing data privacy.
   *
   * @see AbstractProfile
   */
  void logout() override;
};

#endif
