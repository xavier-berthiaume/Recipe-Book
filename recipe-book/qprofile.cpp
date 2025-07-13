#include "qprofile.h"

QProfile::QProfile(QObject *parent) : Storable(parent) {}

QProfile::QProfile(const QUuid &id, QObject *parent) : Storable(id, parent) {}

QProfile::QProfile(const QString &username, QObject *parent)
    : Storable(parent) {
  m_profile = Profile();
  setUsername(username);
}

QProfile::QProfile(const Profile &profile, QObject *parent)
    : Storable(parent), m_profile(profile) {}

QProfile::~QProfile() {}

QString QProfile::getUsername() const {
  return QString::fromStdString(m_profile.getUsername());
}

void QProfile::setUsername(const QString &username) {
  std::string newUsername = username.toStdString();
  if (m_profile.getUsername() != newUsername) {
    m_profile.setUsername(newUsername);
    emit usernameChanged();
  }
}
