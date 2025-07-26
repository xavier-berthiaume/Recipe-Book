#include "profilecache.h"

ProfileCache::ProfileCache(QObject *parent)
    : StorableObjectCache<QProfile>(parent) {}

QProfile *ProfileCache::getProfileByName(const QString &name) {
  for (Storable *profile : m_objectCache) {
    if (qobject_cast<QProfile *>(profile)->getUsername() == name) {
      return qobject_cast<QProfile *>(profile);
    }
  }

  return nullptr;
}
