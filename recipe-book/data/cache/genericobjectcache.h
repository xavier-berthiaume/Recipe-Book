#ifndef GENERICOBJECTCACHE_H
#define GENERICOBJECTCACHE_H

#include "../models.h"
#include "genericobjectcachess.h"

#include <QList>
#include <QQueue>

template <typename T> class GenericObjectCache : public GenericObjectCacheSS {

  const int kCacheLimitSize = 50;
  const int kToSaveLimitSize = 5;
  const int kToUpdateLimitSize = 5;
  const int kToDeleteLimitSize = 5;

protected:
  QQueue<T *> m_objectCache;
  QList<T *> m_toSave;
  QList<T *> m_toUpdate;
  QList<T *> m_toDelete;

public:
  explicit GenericObjectCache<T>(QObject *parent = nullptr);

  QQueue<T *> getCache() const;
  QList<T *> getToSave() const;
  QList<T *> getToUpdate() const;
  QList<T *> getToDelete() const;

  void addObjectToCache(T *);
  void removeObjectFromCache(T *);

  void addObjectToSave(T *);
  void removeObjectToSave(T *);

  void addObjectToUpdate(T *);
  void removeObjectToUpdate(T *);

  void addObjectToDelete(T *);
  void removeObjectToDelete(T *);

  int toSaveSize();
  int toUpdateSize();
  int toDeleteSize();
};
#endif
