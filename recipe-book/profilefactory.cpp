#include "profilefactory.h"

#include <QDebug>

ProfileFactory::ProfileFactory(QObject *parent) : QObject(parent) {}

void ProfileFactory::createProfile(const QString &username) {
  QProfile *newProfile = new QProfile(username, nullptr);
  qDebug() << "Created new profile with username " << newProfile->getUsername();
  emit profileCreated(newProfile);
}

QProfile *ProfileFactory::loadProfile(const QUuid &id,
                                      const QString &username) {
  QProfile *loadedProfile = new QProfile(id);
  loadedProfile->setUsername(username);

  return loadedProfile;
}
