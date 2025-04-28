#include "storable.h"

Storable::Storable(QUuid id) : id(id) {}

Storable::Storable() {}

QUuid Storable::getId() const { return id; }

void Storable::setId(QUuid id) { this->id = id; }
