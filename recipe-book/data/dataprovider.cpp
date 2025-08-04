#include "dataprovider.h"

#include <QDebug>
#include <quuid.h>

DataProvider::DataProvider(AbstractCache *cache, AbstractDbHandler *db,
                           QObject *parent)
    : QObject(parent), m_cache(cache), m_db(db) {}

QVariantMap DataProvider::getObject(ObjectTypes type, const QUuid &id) {
  QVariantMap result;

  if (m_cache->hasObject(type, id)) {
    qDebug() << "Cache hit";
    result = m_cache->getObject(type, id);

    emit objectLoaded(type, result);
    return result;
  }

  qDebug() << "Cache miss";
  result = m_db->readObject(type, id);

  m_cache->putObject(type, id, result);

  emit objectLoaded(type, result);
  return result;
}

QList<QVariantMap> DataProvider::getObjects(ObjectTypes type, int offset,
                                            int limit) {
  QList<QVariantMap> result;

  if (m_cache->hasQuery(type, offset, limit)) {
    qDebug() << "Cache hit";
    result = m_cache->getQuery(type, offset, limit);

    emit objectsLoaded(type, result);
    return result;
  }

  qDebug() << "Cache miss";
  result = m_db->readObjectRange(type, offset, limit);

  m_cache->putQuery(type, offset, limit, result);

  emit objectsLoaded(type, result);
  return result;
}

void DataProvider::invalidateObject(ObjectTypes type, const QUuid &id) {
  m_cache->invalidateObject(type, id);
}

void DataProvider::invalidateObjectType(ObjectTypes type) {
  m_cache->invalidateQueries(type);
}

void DataProvider::invalidateAll() { m_cache->invalidateAll(); }

void DataProvider::objectCountRequested(ObjectTypes type) {
  qDebug() << "Received count signal for object type" << static_cast<int>(type);
  emit objectsCounted(type, m_db->countObjectRows(type));
}

void DataProvider::objectRequested(ObjectTypes type, const QUuid &id) {
  qDebug() << "Individual object requested with type" << static_cast<int>(type)
           << "and id" << id.toString();
  getObject(type, id);
}

void DataProvider::objectsRequested(ObjectTypes type, int offset, int limit) {
  qDebug() << "Objects requested with type" << static_cast<int>(type)
           << "and offset, limit of" << offset << limit;
  getObjects(type, offset, limit);
}

void DataProvider::objectChanged(ObjectTypes type, const QUuid &id) {
  invalidateObject(type, id);
}

void DataProvider::objectsChanged(ObjectTypes type) {
  invalidateObjectType(type);
}
