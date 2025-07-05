#ifndef ABSTRACTDBMANAGER_H
#define ABSTRACTDBMANAGER_H

#include <QObject>

class AbstractDbManager : public QObject {
  Q_OBJECT

public:
  explicit AbstractDbManager(QObject *parent = nullptr);

  // Must be virtual so that the destructor of the derived classes are called
  virtual ~AbstractDbManager() = default;

  virtual bool saveObject(QObject *object) = 0;
  virtual bool updateObject(QObject *object) = 0;
  virtual QObject *readObject(const QString &objectType, const QUuid &id) = 0;
  virtual bool deleteObject(const QString &objectType, const QUuid &id) = 0;

  virtual bool beginTransaction() = 0;
  virtual bool commitTransaction() = 0;
  virtual bool rollbackTransaction() = 0;
};

#endif
