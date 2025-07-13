#include "qingredient.h"

QIngredient::QIngredient(QObject *parent) : Storable(parent) {}

QIngredient::QIngredient(const QUuid &id, QObject *parent)
    : Storable(id, parent) {}

QIngredient::QIngredient(const QString &name, const QString &description,
                         QObject *parent)
    : Storable(parent),
      m_ingredient(Ingredient(name.toStdString(), description.toStdString())) {}

QIngredient::QIngredient(const Ingredient &ingredient, QObject *parent)
    : Storable(parent), m_ingredient(ingredient) {}

QIngredient::~QIngredient() {}

QString QIngredient::getName() const {
  return QString::fromStdString(m_ingredient.getName());
}

QString QIngredient::getDescription() const {
  return QString::fromStdString(m_ingredient.getDescription());
}

QProfile *QIngredient::getCreator() const { return m_creator; }

void QIngredient::setName(const QString &name) {
  m_ingredient.setName(name.toStdString());
  emit nameChanged();
}

void QIngredient::setDescription(const QString &description) {
  m_ingredient.setDescription(description.toStdString());
  emit descriptionChanged();
}

void QIngredient::setCreator(QProfile *profile) {
  m_creator = profile;
  emit creatorChanged();
}
