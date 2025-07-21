#ifndef PROFILEFACTORY_H
#define PROFILEFACTORY_H

#include "genericfactory.h"
#include "qprofile.h"

#include <QVariantMap>

class ProfileFactory : public GenericFactory<QProfile> {
  Q_OBJECT

public:
  explicit ProfileFactory(QObject *parent = nullptr);

  QProfile *createObject(const QVariantMap &data) override;
  QProfile *loadObject(const QVariantMap &data) override;

signals:
  void profileCreated(QProfile *);
  void profileLoaded(QProfile *);
};

#endif
