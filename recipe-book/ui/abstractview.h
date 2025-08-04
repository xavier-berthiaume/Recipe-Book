#ifndef ABSTRACTVIEW_H
#define ABSTRACTVIEW_H

#include "../models.h"
#include "../objecttypes.h"

#include <QWidget>

class AbstractView : public QWidget {
  Q_OBJECT

public:
  explicit AbstractView(QWidget *parent = nullptr) : QWidget(parent) {}

  // In derived classes, don't mark these functions as slots, just throw them in
  // as normal public functions and add the override keyword.
public slots:
  virtual void handleObjectsCounted(ObjectTypes type, int count) = 0;
  virtual void handleObjectCreated(ObjectTypes type, Storable *object) = 0;
  virtual void handleObjectLoaded(ObjectTypes type, Storable *object) = 0;

signals:
  void requestObject(ObjectTypes type, const QUuid &id);
  void requestObjects(ObjectTypes type, int offset = 0, int limit = 10);
  void createObjectRequested(ObjectTypes type, const QVariantMap &data);
  void updateObjectRequested(ObjectTypes type, Storable *object);
  void deleteObjectRequested(ObjectTypes type, Storable *object);
};

#endif
