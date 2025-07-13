#ifndef PROFILEFACTORY_H
#define PROFILEFACTORY_H

#include <QObject>

#include "qprofile.h"

class ProfileFactory : public QObject {
  Q_OBJECT

public:
  ProfileFactory(QObject *parent = nullptr);

  void createProfile(const QString &username);
  QProfile *loadProfile(const QUuid &id, const QString &username);

signals:
  void profileCreated(QProfile *newProfile);
};

#endif // PROFILEFACTORY_H
