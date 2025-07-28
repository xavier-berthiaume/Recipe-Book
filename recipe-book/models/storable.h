#ifndef STORABLE_H
#define STORABLE_H

#include "../database_visitor_fwd.h"

#include <QObject>
#include <QUuid>

class Storable : public QObject {
  Q_OBJECT

  Q_PROPERTY(QUuid m_id READ getId)

protected:
  QUuid m_id;

public:
  explicit Storable(QObject *parent = nullptr);
  explicit Storable(const QUuid &id = QUuid::createUuid(),
                    QObject *parent = nullptr);

  QUuid getId() const;

  virtual void accept(DatabaseVisitor *) = 0;
};

#endif
