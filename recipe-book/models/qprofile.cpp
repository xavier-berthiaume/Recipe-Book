#include "qprofile.h"

QProfile::QProfile(QObject *parent) : Storable(parent), m_profile("") {}

QProfile::QProfile(const QString &username, QObject *parent)
    : Storable(parent), m_profile(username.toStdString()) {}

QString QProfile::getUsername() const {
  return QString::fromStdString(m_profile.getUsername());
}

void QProfile::setUsername(const QString &username) {
  if (username == QString::fromStdString(m_profile.getUsername()))
    return;

  m_profile.setUsername(username.toStdString());

  emit usernameChanged();
}
