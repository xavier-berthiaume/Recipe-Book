#include "applicationcleanup.h"
#include "abstractdbmanager.h"
#include <qobject.h>

ApplicationCleanup::ApplicationCleanup(AbstractDbManager *dbManager,
                                       DataCache *cache, QObject *parent)
    : m_datacache(cache), m_db(dbManager), QObject(parent) {}

void ApplicationCleanup::handleShutdown() {
  // Specifically save cache data to the database
  for (QObject *obj : m_datacache->getModelsToSave()) {
    m_db->saveObject(obj);
  }

  for (QObject *obj : m_datacache->getModelsToUpdate()) {
    m_db->updateObject(obj);
  }

  for (QObject *obj : m_datacache->getModelsToDelete()) {
    // m_db->deleteObject(obj);
  }
}
