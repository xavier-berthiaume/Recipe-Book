#ifndef PROFILECACHE_H
#define PROFILECACHE_H

#include "storableobjectcache.h"

class ProfileCache : public StorableObjectCache<QProfile> {
  Q_OBJECT

public:
  explicit ProfileCache(QObject *parent = nullptr);

  QProfile *getProfileByName(const QString &username);
};

#endif
