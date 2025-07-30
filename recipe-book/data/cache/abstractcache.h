#ifndef ABSTRACTCACHE_H
#define ABSTRACTCACHE_H

#include "../../objecttypes.h"

#include <QObject>
#include <QUuid>
#include <QVariantMap>

class AbstractCache : public QObject {
  Q_OBJECT

public:
  explicit AbstractCache(QObject *parent = nullptr) : QObject(parent) {}
  virtual ~AbstractCache() = default;

  virtual bool hasObject(ObjectTypes type, const QUuid &id) = 0;
  virtual QVariantMap getObject(ObjectTypes type, const QUuid &id) = 0;
  virtual void putObject(ObjectTypes type, const QUuid &id,
                         const QVariantMap &data) = 0;
  virtual void invalidateObject(ObjectTypes type, const QUuid &id) = 0;

  virtual bool hasQuery(ObjectTypes type, int offset, int limit) = 0;
  virtual QList<QVariantMap> getQuery(ObjectTypes type, int offset,
                                      int limit) = 0;
  virtual void putQuery(ObjectTypes type, int offset, int limit,
                        const QList<QVariantMap> &data) = 0;
  virtual void invalidateQueries(ObjectTypes type) = 0;

  virtual void invalidateAll() = 0;
};

#endif
