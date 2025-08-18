#include "recipeingredientlistmodel.h"

RecipeIngredientListModel::RecipeIngredientListModel(QObject *parent)
    : GenericListModel<QRecipeIngredient>(parent) {}

void RecipeIngredientListModel::connectModelSignals(
    QRecipeIngredient *model) const {}

QHash<int, QByteArray> RecipeIngredientListModel::roleNames() const {
  return {{IngredientIdRole, "Ingredient Id"},
          {QuantityRole, "Quantity"},
          {UnitRole, "Unit"},
          {IsRecipeRole, "Is Recipe"},
          {IdRole, "Id"}};
}

QVariant RecipeIngredientListModel::data(const QModelIndex &index,
                                         int role) const {
  if (!index.isValid() || index.row() >= m_modelList.size())
    return QVariant();

  QRecipeIngredient *recipeIngredient = m_modelList.at(index.row());
  QIngredient *ingredient =
      m_ingredients.value(recipeIngredient->getIngredientId());

  switch (role) {
  case IngredientIdRole:
    return recipeIngredient->getIngredientId();

  case NameRole:
    return (ingredient ? ingredient->getName() : "Unknown");

  case QuantityRole:
    return recipeIngredient->getQuantity();

  case UnitRole:
    return recipeIngredient->getUnit();

  case IsRecipeRole:
    return recipeIngredient->getIsRecipe();

  case IdRole:
    return recipeIngredient->getId();

  default:
    return QVariant();
  }
}

QRecipeIngredient *
RecipeIngredientListModel::getRecipeIngredient(const QModelIndex &index) const {
  qDebug() << "Getting recipe ingredient at index" << index.row();
  if (!index.isValid() || index.row() >= m_modelList.size()) {
    qWarning() << "Invalid index passed";
    return nullptr;
  }

  return m_modelList[index.row()];
}

void RecipeIngredientListModel::modifyModel(int index, const QVariant &data,
                                            int role) {
  QModelIndex indx = this->index(index);
  if (!indx.isValid() || index >= m_modelList.size())
    return;

  QRecipeIngredient *recipeIngredient = m_modelList.at(index);

  switch (role) {
  case IngredientIdRole:
    recipeIngredient->setIngredientId(data.toUuid());

  case QuantityRole:
    recipeIngredient->setQuantity(data.toDouble());

  case UnitRole:
    recipeIngredient->setUnit(data.value<Units>());

  case IsRecipeRole:
    recipeIngredient->setIsRecipe(data.toBool());

  default:
    qWarning() << "Tried setting an invalid field for QRecipeIngredient";
    break;
  }
}

void RecipeIngredientListModel::addIngredientToCache(QIngredient *object) {
  if (object == nullptr)
    return;

  m_ingredients.insert(object->getId(), object);
}

void RecipeIngredientListModel::clearModel() {
  qDebug() << "Clearing recipe ingredient model";

  beginResetModel();
  qDeleteAll(m_modelList);
  m_modelList.clear();
  endResetModel();
}
