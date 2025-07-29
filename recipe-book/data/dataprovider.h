#ifndef DATAPROVIDER_H
#define DATAPROVIDER_H

#include "cache/abstractcache.h"
#include "db/abstractdbhandler.h"
#include "objecttypes.h"

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
};

#endif
