#include "storable.h"
#include <quuid.h>

Storable::Storable(QUuid id, QObject *parent) : QObject(parent), m_id(id) {
  if (m_id.isNull()) {
    m_id = QUuid::createUuid();
  }
}

Storable::Storable(QObject *parent)
    : QObject(parent), m_id(QUuid::createUuid()) {}

QUuid Storable::getId() const { return m_id; }

void Storable::setId(QUuid id) {
  this->m_id = id;

  emit idChanged();
}
