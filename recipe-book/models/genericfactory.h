#ifndef GENERICFACTORY_H
#define GENERICFACTORY_H

#include "genericfactoryss.h"

template <typename T> class GenericFactory : public GenericFactorySS {
  Q_OBJECT

public:
  explicit GenericFactory<T>(QObject *parent = nullptr)
      : GenericFactorySS(parent) {}

  virtual T *createObject(const QVariantMap &data) = 0;
  virtual T *loadObject(const QVariantMap &data) = 0;
};

#endif
