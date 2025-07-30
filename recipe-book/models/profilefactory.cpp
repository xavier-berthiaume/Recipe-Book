#include "profilefactory.h"

ProfileFactory::ProfileFactory(QObject *parent)
    : GenericFactory<QProfile>(parent) {}

QProfile *ProfileFactory::createObject(const QVariantMap &data) {

  QProfile *newProfile = new QProfile(data["username"].toString(), this);

  emit objectCreated(PROFILEOBJECT, newProfile);
  emit profileCreated(newProfile);
  return newProfile;
}

QProfile *ProfileFactory::loadObject(const QVariantMap &data) {

  QProfile *loadedProfile =
      new QProfile(data["id"].toUuid(), data["username"].toString(), this);

  emit objectLoaded(PROFILEOBJECT, loadedProfile);
  emit profileLoaded(loadedProfile);
  return loadedProfile;
}
