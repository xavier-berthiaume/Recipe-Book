#ifndef ABSTRACTDBHANDLER_H
#define ABSTRACTDBHANDLER_H

#include "../../models.h"
#include "../../objecttypes.h"
#include "databasevisitor.h"

#include <QObject>

class AbstractDbHandler : public QObject {
  Q_OBJECT

protected:
  virtual bool beginTransaction() = 0;
  virtual bool rollbackTransaction() = 0;
  virtual bool commitTransaction() = 0;

public:
  explicit AbstractDbHandler(QObject *parent = nullptr) : QObject(parent) {}

  virtual void saveObject(Storable *toSave) = 0;
  virtual void updateObject(Storable *toUpdate) = 0;
  virtual QVariantMap readObject(ObjectTypes type, const QUuid &id) = 0;
  virtual QList<QVariantMap> readObjectRange(ObjectTypes type, int offset,
                                             int count) = 0;
  virtual QList<QVariantMap> readAllObjects(ObjectTypes type) = 0;
  virtual bool removeObject(Storable *object) = 0;

  // Getters for the different database visitor objects
  virtual DatabaseVisitor *getSaver() = 0;
  virtual DatabaseVisitor *getUpdater() = 0;
  virtual DatabaseVisitor *getDeleter() = 0;

public slots:
  void onObjectCreation(Storable *object) { saveObject(object); }
  void onObjectUpdate(Storable *object) { updateObject(object); }
  void onObjectDelete(Storable *object) { removeObject(object); }
};

#endif
