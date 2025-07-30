#ifndef GENERICFACTORYSS_H
#define GENERICFACTORYSS_H

#include "../objecttypes.h"
#include "storable.h"

#include <QObject>

class GenericFactorySS : public QObject {
  Q_OBJECT

public:
  explicit GenericFactorySS(QObject *parent = nullptr) : QObject(parent) {}

signals:
  void objectCreated(ObjectTypes type, Storable *object);
  void objectLoaded(ObjectTypes type, Storable *object);
};

#endif
