#ifndef DATAPROVIDER_H
#define DATAPROVIDER_H

#include "../objecttypes.h"
#include "cache/abstractcache.h"
#include "db/abstractdbhandler.h"

#include <QObject>

class DataProvider : public QObject {
  Q_OBJECT

  AbstractCache *m_cache;
  AbstractDbHandler *m_db;

public:
  explicit DataProvider(AbstractCache *cache, AbstractDbHandler *db,
                        QObject *parent = nullptr);

  QVariantMap getObject(ObjectTypes type, const QUuid &id);

  QList<QVariantMap> getObjects(ObjectTypes type, int offset = 0,
                                int limit = 10);

  void invalidateObject(ObjectTypes type, const QUuid &id);
  void invalidateObjectType(ObjectTypes type);
  void invalidateAll();

public slots:
  void objectCountRequested(ObjectTypes type);
  void objectRequested(ObjectTypes type, const QUuid &id);
  void objectsRequested(ObjectTypes type, int offset = 0, int limit = 10);
  void objectChanged(ObjectTypes type, const QUuid &id);
  void objectsChanged(ObjectTypes type);

signals:
  void objectsCounted(ObjectTypes type, int count);
  void objectLoaded(ObjectTypes type, const QVariantMap &data);
  void objectsLoaded(ObjectTypes type, const QList<QVariantMap> &data);
};

#endif
