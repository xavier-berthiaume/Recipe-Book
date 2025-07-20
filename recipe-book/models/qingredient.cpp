#include "qingredient.h"

QIngredient::QIngredient(const QString &name, const QString &description,
                         QObject *parent)
    : Storable(parent),
      m_ingredient(QUuid::createUuid().toString().toStdString(),
                   name.toStdString(), description.toStdString()) {}

QIngredient::QIngredient(const QUuid &id, const QString &name,
                         const QString &description, QObject *parent)
    : Storable(parent),
      m_ingredient(id.toString().toStdString(), name.toStdString(),
                   description.toStdString()) {}

QString QIngredient::getName() const {
  return QString::fromStdString(m_ingredient.getName());
}

QString QIngredient::getDescription() const {
  return QString::fromStdString(m_ingredient.getDescription());
}

void QIngredient::setName(const QString &name) {
  if (name == m_ingredient.getName())
    return;

  m_ingredient.setName(name.toStdString());
  emit nameChanged();
}

void QIngredient::setDescription(const QString &description) {
  if (description == m_ingredient.getDescription())
    return;

  m_ingredient.setDescription(description.toStdString());
  emit descriptionChanged();
}
