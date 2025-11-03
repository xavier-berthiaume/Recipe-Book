#include "authenticatedprofile.h"

#include <QCryptographicHash>
#include <QDebug>

AuthenticatedProfile::AuthenticatedProfile(QString screen_name,
                                           QString first_name,
                                           QString last_name, QString password)
    : AbstractProfile(std::move(screen_name), std::move(first_name),
                      std::move(last_name)) {
  setPasswordHash(password);
}

AuthenticatedProfile::AuthenticatedProfile(QString screen_name,
                                           QString first_name,
                                           QString last_name,
                                           QByteArray password_hash)
    : AbstractProfile(std::move(screen_name), std::move(first_name),
                      std::move(last_name)),
      m_password_hash(std::move(password_hash)) {}

auto AuthenticatedProfile::getProfile() noexcept -> AbstractProfile & {
  return m_profile;
}

void AuthenticatedProfile::setPasswordHash(const QString &password) {
  QByteArray data = password.toUtf8();

  m_password_hash = QCryptographicHash::hash(data, QCryptographicHash::Sha256);
}

void AuthenticatedProfile::authenticate(const QString &password) {
  QByteArray data = password.toUtf8();

  if (m_password_hash == data) {
    m_profile.authenticate();
    qDebug() << "Successfully authenticated";
  }
  qDebug() << "Failed authentication";
}

void AuthenticatedProfile::logout() {}
