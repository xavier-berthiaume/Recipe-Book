#include "qt_ingredient_wrapper.h"

#include <QDebug>

QtIngredientWrapper::QtIngredientWrapper(QObject *parent) : Storable(parent) {}

QtIngredientWrapper::QtIngredientWrapper(QUuid id, QObject *parent)
    : Storable(id, parent) {}

QtIngredientWrapper::QtIngredientWrapper(const QString &name,
                                         const QString &description,
                                         QObject *parent)
    : Storable(parent),
      m_ingredient(name.toStdString(), description.toStdString()) {}

QtIngredientWrapper::QtIngredientWrapper(const Ingredient &ingredient,
                                         QObject *parent)
    : Storable(QUuid::createUuid(), parent), m_ingredient(ingredient) {}

QtIngredientWrapper::~QtIngredientWrapper() {}

QString QtIngredientWrapper::getName() const {
  return QString::fromStdString(m_ingredient.getName());
}

QString QtIngredientWrapper::getDescription() const {
  return QString::fromStdString(m_ingredient.getDescription());
}

bool QtIngredientWrapper::getIsRecipe() const { return m_is_recipe; }

QUuid QtIngredientWrapper::getLinkedRecipeId() const {
  return m_linked_recipe_id;
}

const Ingredient &QtIngredientWrapper::getIngredient() const {
  return m_ingredient;
}

void QtIngredientWrapper::setName(const QString &name) {
  std::string newName = name.toStdString();
  if (m_ingredient.getName() != newName) {
    m_ingredient.setName(newName);
    emit nameChanged();
  }
}

void QtIngredientWrapper::setDescription(const QString &description) {
  std::string newDesc = description.toStdString();
  if (m_ingredient.getDescription() != newDesc) {
    m_ingredient.setDescription(newDesc);
    emit descriptionChanged();
  }
}
