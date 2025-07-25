#ifndef STORABLEOBJECTCACHE_H
#define STORABLEOBJECTCACHE_H

#include "../models.h"
#include "genericobjectcache.h"

template <typename T>
class StorableObjectCache : public GenericObjectCache<Storable> {

public:
  explicit StorableObjectCache<T>(QObject *parent = nullptr);

  // Simplest approach here is to return nullptr if the object isn't found
  // and have whatever is looking for the data ask the database to look for the
  // item by itself.
  T *getObjectInCache(const QUuid &id);
};

#endif
