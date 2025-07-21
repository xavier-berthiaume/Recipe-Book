#ifndef GENERICFACTORYSS_H
#define GENERICFACTORYSS_H

#include <QObject>

class GenericFactorySS : public QObject {
  Q_OBJECT

public:
  explicit GenericFactorySS(QObject *parent = nullptr) : QObject(parent) {}

signals:
  void objectCreated(QObject *object);
  void objectLoaded(QObject *object);
};

#endif
