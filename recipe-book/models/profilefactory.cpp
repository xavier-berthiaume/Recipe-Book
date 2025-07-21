#include "profilefactory.h"

ProfileFactory::ProfileFactory(QObject *parent)
    : GenericFactory<QProfile>(parent) {}

QProfile *ProfileFactory::createObject(const QVariantMap &data) {

  QProfile *newProfile = new QProfile(data["username"].toString(), this);

  emit profileCreated(newProfile);
  return newProfile;
}

QProfile *ProfileFactory::loadObject(const QVariantMap &data) {

  QProfile *newProfile =
      new QProfile(data["id"].toUuid(), data["username"].toString(), this);

  emit profileLoaded(newProfile);
  return newProfile;
}
