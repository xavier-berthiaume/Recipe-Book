#include "storableobjectcache.h"

template <typename T>
StorableObjectCache<T>::StorableObjectCache(QObject *parent)
    : GenericObjectCache<Storable>(parent) {}

template <typename T>
T *StorableObjectCache<T>::getObjectInCache(const QUuid &id) {
  for (Storable *object : m_objectCache) {
    if (object->getId() == id)
      return object;
  }

  return nullptr;
}
