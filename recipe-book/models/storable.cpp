#include "storable.h"

Storable::Storable(const QUuid &id, QObject *parent)
    : QObject(parent), m_id(id) {}

Storable::Storable(QObject *parent) : Storable(QUuid::createUuid(), parent) {}

QUuid Storable::getId() const { return m_id; }
