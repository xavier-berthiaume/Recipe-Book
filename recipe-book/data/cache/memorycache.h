#ifndef MEMORYCACHE_H
#define MEMORYCACHE_H

#include "abstractcache.h"

#include <QCache>
#include <QReadWriteLock>

class MemoryCache : public AbstractCache {
  Q_OBJECT

  QString objectKey(ObjectTypes type, const QUuid &id) const;
  QString queryKey(ObjectTypes type, int offset, int limit) const;

  QCache<QString, QVariantMap> m_objectCache;
  QCache<QString, QList<QVariantMap>> m_queryCache;
  mutable QReadWriteLock m_objectCacheLock;
  mutable QReadWriteLock m_queryCacheLock;

public:
  explicit MemoryCache(uint32_t maxObjectCacheSize = 1024 * 1024 * 50, // 50MB
                       uint32_t maxQueryCacheSize = 1024 * 1024 * 40,  // 40MB
                       QObject *parent = nullptr);

  bool hasObject(ObjectTypes type, const QUuid &id) override;
  QVariantMap getObject(ObjectTypes type, const QUuid &id) override;
  void putObject(ObjectTypes type, const QUuid &id,
                 const QVariantMap &data) override;
  void invalidateObject(ObjectTypes type, const QUuid &id) override;

  bool hasQuery(ObjectTypes type, int offset, int limit) override;
  QList<QVariantMap> getQuery(ObjectTypes type, int offset, int limit) override;
  void putQuery(ObjectTypes type, int offset, int limit,
                const QList<QVariantMap> &data) override;
  void invalidateQueries(ObjectTypes type) override;

  void invalidateAll() override;
};

#endif
