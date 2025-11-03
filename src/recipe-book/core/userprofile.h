/**
 * @file profile.h
 * @breif Class that implements the details surrounding user profiles.
 */
#ifndef USERPROFILE_H
#define USERPROFILE_H

#include "abstractprofile.h"
#include "abstractstorable.h"

/**
 * @brief Concrete class that defines the information related to a users
 * profile. Implements the Storable interface.
 *
 * Profiles are unique storable items in that their id and their created_by_id
 * are the same. This gives profiles 'administrative privileges' over
 * themselves, granting a profile the power to delete itself.
 */
class UserProfile : public AbstractStorable, public AbstractProfile {
  Q_OBJECT

protected:
  /**
   * @brief Parametrized constructor
   *
   * Uses std::move semantics for the username, creation_date and update_date
   * parameters.
   *
   * This class only has a parametrized constructor because of the constraint
   * that a users id must be set as its own creator id.
   *
   * Marked as protected to enforce the use of factories.
   */
  UserProfile(QString username, QString first_name, QString last_name,
              QUuid identifier, QDateTime creation_date, QDateTime update_date,
              QObject *parent = nullptr);

public:
  ~UserProfile() override = default;

  /** @brief Copy constructor */
  UserProfile(const UserProfile &other) noexcept;

  /** @brief Move constructor */
  UserProfile(UserProfile &&other) noexcept;

  /** @brief Deleted copy assignment operator */
  auto operator=(const UserProfile &) -> UserProfile & = delete;

  /** @brief Deleted move assignment operator */
  auto operator=(UserProfile &&) -> UserProfile & = delete;

  /**
   * @brief Allows the visitor object to use this object to execute database
   * manipulations.
   *
   * @see Storable
   */
  void accept(DatabaseVisitor *visitor) override;

  /**
   * @brief Logs in the user and unlocks their profile.
   *
   * @see AbstractProfile
   */
  void authenticate() override;

  /**
   * @brief Logs out the user and locks their profile providing data privacy.
   *
   * @see AbstractProfile
   */
  void logout() override;
};

#endif
