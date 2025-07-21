#include "qingredient.h"

QIngredient::QIngredient(const QUuid &creatorId, const QString &name,
                         const QString &description, QObject *parent)
    : Storable(parent),
      m_ingredient(creatorId.toString().toStdString(), name.toStdString(),
                   description.toStdString()) {}

QIngredient::QIngredient(const QUuid &id, const QUuid &creatorId,
                         const QString &name, const QString &description,
                         QObject *parent)
    : Storable(id, parent),
      m_ingredient(creatorId.toString().toStdString(), name.toStdString(),
                   description.toStdString()) {}

QUuid QIngredient::getCreatorId() const {
  return QUuid::fromString(QString::fromStdString(m_ingredient.getCreatorId()));
}

QString QIngredient::getName() const {
  return QString::fromStdString(m_ingredient.getName());
}

QString QIngredient::getDescription() const {
  return QString::fromStdString(m_ingredient.getDescription());
}

void QIngredient::setName(const QString &name) {
  if (name == QString::fromStdString(m_ingredient.getName()))
    return;

  m_ingredient.setName(name.toStdString());
  emit nameChanged();
}

void QIngredient::setDescription(const QString &description) {
  if (description == QString::fromStdString(m_ingredient.getDescription()))
    return;

  m_ingredient.setDescription(description.toStdString());
  emit descriptionChanged();
}
