#ifndef STORABLE_H
#define STORABLE_H

#include <QUuid>

class Storable {

  QUuid id;

public:
  explicit Storable(QUuid id);
  Storable();

  QUuid getId() const;
  void setId(QUuid id);
};

#endif
