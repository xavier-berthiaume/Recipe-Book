#ifndef APPLICATIONCLEANUP_H
#define APPLICATIONCLEANUP_H

#include "abstractdbmanager.h"
#include "datacache.h"

#include <QObject>

class ApplicationCleanup : public QObject {
  Q_OBJECT

  DataCache *m_datacache;
  AbstractDbManager *m_db;

public:
  explicit ApplicationCleanup(AbstractDbManager *dbManager, DataCache *cache,
                              QObject *parent = nullptr);
public slots:
  void handleShutdown();
};

#endif
