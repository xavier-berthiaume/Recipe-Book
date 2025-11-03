#include "userprofile.h"

UserProfile::UserProfile(QString username, QString first_name,
                         QString last_name, QUuid identifier,
                         QDateTime creation_date, QDateTime update_date,
                         QObject *parent)
    : AbstractStorable(identifier, identifier, std::move(creation_date),
                       std::move(update_date), parent),
      AbstractProfile(std::move(username), std::move(first_name),
                      std::move(last_name)) {}

UserProfile::UserProfile(const UserProfile &other) noexcept
    : UserProfile(std::move(other.getScreenName()),
                  std::move(other.getFirstName()), other.getLastName(),
                  other.getId(), std::move(other.getCreationDate()),
                  std::move(other.getUpdateDate()), other.parent()) {}

UserProfile::UserProfile(UserProfile &&other) noexcept
    : UserProfile(std::move(other.getScreenName()),
                  std::move(other.getFirstName()), other.getLastName(),
                  other.getId(), std::move(other.getCreationDate()),
                  std::move(other.getUpdateDate()), other.parent()) {}

void UserProfile::accept(DatabaseVisitor *visitor) {}

void UserProfile::authenticate() { setIsLocked(false); }

void UserProfile::logout() { setIsLocked(true); }
