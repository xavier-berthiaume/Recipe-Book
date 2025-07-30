#include "memorycache.h"

MemoryCache::MemoryCache(uint32_t maxObjectCacheSize,
                         uint32_t maxQueryCacheSize, QObject *parent)
    : AbstractCache(parent), m_objectCache(maxObjectCacheSize),
      m_queryCache(maxQueryCacheSize) {}

// We're storing objects in their own cache, and queries in their own cache. The
// key is the numerical value of the objects type, and underscore, and the
// objects quuid.

QString MemoryCache::objectKey(ObjectTypes type, const QUuid &id) const {
  return QString("%1_%2").arg(static_cast<int>(type)).arg(id.toString());
}

QString MemoryCache::queryKey(ObjectTypes type, int offset, int limit) const {
  return QString("%1_%2_%3").arg(static_cast<int>(type)).arg(offset).arg(limit);
}

bool MemoryCache::hasObject(ObjectTypes type, const QUuid &id) {
  QReadLocker locker(&m_objectCacheLock);

  return m_objectCache.contains(objectKey(type, id));
}

QVariantMap MemoryCache::getObject(ObjectTypes type, const QUuid &id) {
  QReadLocker locker(&m_objectCacheLock);

  // To avoid dereferencing a nullptr
  if (QVariantMap *obj = m_objectCache.object(objectKey(type, id))) {
    return *obj;
  }

  return {};
}

void MemoryCache::putObject(ObjectTypes type, const QUuid &id,
                            const QVariantMap &data) {
  QWriteLocker locker(&m_objectCacheLock);

  // Create a new object for the data, and the cache will handle its lifecycle
  // Pass the size of the data as the cost
  m_objectCache.insert(objectKey(type, id), new QVariantMap(data), data.size());
}

void MemoryCache::invalidateObject(ObjectTypes type, const QUuid &id) {
  QWriteLocker locker(&m_objectCacheLock);

  m_objectCache.remove(objectKey(type, id));
}

bool MemoryCache::hasQuery(ObjectTypes type, int offset, int limit) {
  QReadLocker lock(&m_queryCacheLock);

  return m_queryCache.contains(queryKey(type, offset, limit));
}

QList<QVariantMap> MemoryCache::getQuery(ObjectTypes type, int offset,
                                         int limit) {
  QReadLocker lock(&m_queryCacheLock);

  if (QList<QVariantMap> *query =
          m_queryCache.object(queryKey(type, offset, limit))) {
    return *query;
  }

  return {};
}

void MemoryCache::putQuery(ObjectTypes type, int offset, int limit,
                           const QList<QVariantMap> &data) {
  QWriteLocker lock(&m_queryCacheLock);

  m_queryCache.insert(queryKey(type, offset, limit),
                      new QList<QVariantMap>(data), data.size());
}

void MemoryCache::invalidateQueries(ObjectTypes type) {
  QWriteLocker lock(&m_queryCacheLock);

  QString prefix = QString("%1_").arg(static_cast<int>(type));
  for (const QString &key : m_queryCache.keys()) {
    if (key.startsWith(prefix)) {
      m_queryCache.remove(key);
    }
  }
}

void MemoryCache::invalidateAll() {
  QWriteLocker objectLocker(&m_objectCacheLock);
  m_objectCache.clear();

  QWriteLocker queryLocker(&m_queryCacheLock);
  m_queryCache.clear();
}
