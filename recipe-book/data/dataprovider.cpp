#include "dataprovider.h"
#include <qcontainerfwd.h>

DataProvider::DataProvider(AbstractCache *cache, AbstractDbHandler *db,
                           QObject *parent)
    : QObject(parent), m_cache(cache), m_db(db) {}

QVariantMap DataProvider::getObject(ObjectTypes type, const QUuid &id) {
  if (m_cache->hasObject(type, id)) {
    return m_cache->getObject(type, id);
  }

  QVariantMap result = m_db->readObject(type, id);

  m_cache->putObject(type, id, result);

  return result;
}

QList<QVariantMap> DataProvider::getObjects(ObjectTypes type, int offset,
                                            int limit) {
  if (m_cache->hasQuery(type, offset, limit)) {
    return m_cache->getQuery(type, offset, limit);
  }

  QList<QVariantMap> result = m_db->readObjectRange(type, offset, limit);

  m_cache->putQuery(type, offset, limit, result);

  return result;
}

void DataProvider::invalidateObject(ObjectTypes type, const QUuid &id) {
  m_cache->invalidateObject(type, id);
}

void DataProvider::invalidateObjectType(ObjectTypes type) {
  m_cache->invalidateQueries(type);
}

void DataProvider::invalidateAll() { m_cache->invalidateAll(); }
