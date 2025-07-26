#include "genericobjectcache.h"

template <typename T>
GenericObjectCache<T>::GenericObjectCache(QObject *parent)
    : GenericObjectCacheSS(parent) {}

template <typename T> QQueue<T *> GenericObjectCache<T>::getCache() const {
  return m_objectCache;
}

template <typename T> QList<T *> GenericObjectCache<T>::getToSave() const {
  return m_toSave;
}

template <typename T> QList<T *> GenericObjectCache<T>::getToUpdate() const {
  return m_toUpdate;
}

template <typename T> QList<T *> GenericObjectCache<T>::getToDelete() const {
  return m_toDelete;
}

template <typename T> void GenericObjectCache<T>::addObjectToCache(T *object) {
  if (!m_objectCache.contains(object)) {
    m_objectCache.enqueue(object);
    emit cacheChanged();
  }

  if (m_objectCache.size() >= kCacheLimitSize) {
    m_objectCache.dequeue();
    emit cacheLimitReached();
  }
}

template <>
void GenericObjectCache<Storable>::addObjectToCache(Storable *object) {
  for (Storable *cachedObject : m_objectCache) {
    if (cachedObject->getId() == object->getId())
      return;
  }

  m_objectCache.enqueue(object);

  emit cacheChanged();

  if (m_objectCache.size() >= kCacheLimitSize) {
    m_objectCache.dequeue();
    emit cacheLimitReached();
  }
}

template <typename T>
void GenericObjectCache<T>::removeObjectFromCache(T *object) {
  for (int i = 0; i < m_objectCache.size(); i++) {
    if (m_objectCache.at(i) == object) {
      m_objectCache.removeAt(i);
      emit cacheChanged();
      return;
    }
  }
}

// Remove based on object ID, not the pointer directly
template <>
void GenericObjectCache<Storable>::removeObjectFromCache(Storable *object) {
  for (int i = 0; i < m_objectCache.size(); i++) {
    if (m_objectCache.at(i)->getId() == object->getId()) {
      m_objectCache.removeAt(i);
      emit cacheChanged();
      // We don't stop in case the object is present multiple times
    }
  }
}

template <typename T> void GenericObjectCache<T>::addObjectToSave(T *object) {
  if (!m_toSave.contains(object)) {
    m_toSave.append(object);
    emit cacheChanged();

    if (m_toSave.size() >= kToSaveLimitSize) {
      emit toSaveLimitReached();
    }
  }
}

template <>
void GenericObjectCache<Storable>::addObjectToSave(Storable *object) {
  for (Storable *cacheObject : m_toSave) {
    if (cacheObject->getId() == object->getId())
      return;
  }

  m_toSave.push_back(object);
  emit cacheChanged();

  if (m_toSave.size() >= kToSaveLimitSize) {
    emit toSaveLimitReached();
  }
}

template <typename T>
void GenericObjectCache<T>::removeObjectToSave(T *object) {
  int removed = m_toSave.removeAll(object);
  if (removed > 0) {
    emit cacheChanged();
  }
}

template <>
void GenericObjectCache<Storable>::removeObjectToSave(Storable *object) {
  int removed = 0;

  for (int i = 0; i < m_toSave.size(); i++) {
    if (m_toSave.at(i)->getId() == object->getId()) {
      m_toSave.removeAt(i);
      removed++;
    }
  }

  if (removed > 0)
    emit cacheChanged();
}

template <typename T> void GenericObjectCache<T>::addObjectToUpdate(T *object) {
  if (!m_toUpdate.contains(object)) {
    m_toUpdate.append(object);
    emit cacheChanged();

    if (m_toUpdate.size() >= kToUpdateLimitSize) {
      emit toUpdateLimitReached();
    }
  }
}

template <>
void GenericObjectCache<Storable>::addObjectToUpdate(Storable *object) {
  for (Storable *cacheObject : m_toUpdate) {
    if (cacheObject->getId() == object->getId())
      return;
  }

  m_toUpdate.push_back(object);
  emit cacheChanged();

  if (m_toUpdate.size() >= kToUpdateLimitSize) {
    emit toUpdateLimitReached();
  }
}

template <typename T>
void GenericObjectCache<T>::removeObjectToUpdate(T *object) {
  int removed = m_toUpdate.removeAll(object);
  if (removed > 0) {
    emit cacheChanged();
  }
}

template <>
void GenericObjectCache<Storable>::removeObjectToUpdate(Storable *object) {
  int removed = 0;

  for (int i = 0; i < m_toUpdate.size(); i++) {
    if (m_toUpdate.at(i)->getId() == object->getId()) {
      m_toUpdate.removeAt(i);
      removed++;
    }
  }

  if (removed > 0)
    emit cacheChanged();
}

template <typename T> void GenericObjectCache<T>::addObjectToDelete(T *object) {
  if (!m_toDelete.contains(object)) {
    m_toDelete.append(object);
    removeObjectFromCache(object); // We don't want to leave an object that's
                                   // gonna be deleted in the cache
    removeObjectToSave(object);
    removeObjectToUpdate(object);
    emit cacheChanged();

    if (m_toDelete.size() >= kToDeleteLimitSize) {
      emit toDeleteLimitReached();
    }
  }
}

template <>
void GenericObjectCache<Storable>::addObjectToDelete(Storable *object) {
  for (Storable *cacheObject : m_toDelete) {
    if (cacheObject->getId() == object->getId())
      return;
  }

  m_toDelete.push_back(object);
  removeObjectFromCache(object);
  removeObjectToSave(object);
  removeObjectToUpdate(object);
  emit cacheChanged();

  if (m_toDelete.size() >= kToDeleteLimitSize) {
    emit toDeleteLimitReached();
  }
}

template <typename T>
void GenericObjectCache<T>::removeObjectToDelete(T *object) {
  int removed = m_toDelete.removeAll(object);
  if (removed > 0) {
    emit cacheChanged();
  }
}

template <>
void GenericObjectCache<Storable>::removeObjectToDelete(Storable *object) {
  int removed = 0;

  for (int i = 0; i < m_toDelete.size(); i++) {
    if (m_toDelete.at(i)->getId() == object->getId()) {
      m_toDelete.removeAt(i);
      removed++;
    }
  }

  if (removed > 0)
    emit cacheChanged();
}

template <typename T> int GenericObjectCache<T>::toSaveSize() {
  return m_toSave.size();
}

template <typename T> int GenericObjectCache<T>::toUpdateSize() {
  return m_toUpdate.size();
}

template <typename T> int GenericObjectCache<T>::toDeleteSize() {
  return m_toDelete.size();
}
