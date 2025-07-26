#ifndef GENERICOBJECTCACHESS_H
#define GENERICOBJECTCACHESS_H

#include <QObject>

class GenericObjectCacheSS : public QObject {
  Q_OBJECT

public:
  explicit GenericObjectCacheSS(QObject *parent = nullptr) : QObject(parent) {}

signals:
  void cacheChanged();

  void cacheLimitReached();
  void toSaveLimitReached();
  void toUpdateLimitReached();
  void toDeleteLimitReached();
};

#endif
