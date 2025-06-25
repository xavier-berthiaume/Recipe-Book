#include "recipeingredientmodellist.h"

RecipeIngredientModelList::RecipeIngredientModelList(QObject *parent)
    : QAbstractListModel{parent} {}

int RecipeIngredientModelList::rowCount(const QModelIndex &parent) const {
  Q_UNUSED(parent)

  return m_recipeIngredients.size();
}

QVariant RecipeIngredientModelList::data(const QModelIndex &index,
                                         int role) const {
  if (!index.isValid() || index.row() >= m_recipeIngredients.size())
    return QVariant();

  QRecipeIngredient *recipeIngredient = m_recipeIngredients[index.row()];

  switch (role) {
  case Roles::NameRole:
    return recipeIngredient->getIngredient()->getName();
  case Roles::DescriptionRole:
    return recipeIngredient->getIngredient()->getDescription();
  case Roles::IdRole:
    return recipeIngredient->getId();
  case Roles::QuantityRole:
    return recipeIngredient->getQuantity();
  case Roles::UnitRole:
    return recipeIngredient->getUnit();
  case Roles::IsRecipeRole:
    return recipeIngredient->getIsRecipe();
  default:
    return QVariant();
  }
}

QHash<int, QByteArray> RecipeIngredientModelList::roleNames() const {
  return {{Roles::NameRole, "Name"}, {Roles::DescriptionRole, "Description"},
          {Roles::IdRole, "ID"},     {Roles::QuantityRole, "Quantity"},
          {Roles::UnitRole, "Unit"}, {Roles::IsRecipeRole, "Is Recipe"}};
}

void RecipeIngredientModelList::populate(
    const QList<QRecipeIngredient *> &list) {
  if (list.isEmpty())
    return;

  if (!m_recipeIngredients.isEmpty()) {
    beginResetModel();
    qDeleteAll(m_recipeIngredients);
    m_recipeIngredients.clear();
    endResetModel();
  }

  beginInsertRows(QModelIndex(), rowCount(), rowCount() + list.size() - 1);
  for (QRecipeIngredient *recipeIngredient : list) {
    m_recipeIngredients.append(recipeIngredient);

    // Connect all the signals
    connect(recipeIngredient, &QRecipeIngredient::ingredientChanged, this,
            [this, recipeIngredient]() {
              int row = m_recipeIngredients.indexOf(recipeIngredient);
              if (row >= 0) {
                QModelIndex index = this->index(row);
                emit dataChanged(index, index, {Roles::NameRole});
                emit dataChanged(index, index, {Roles::DescriptionRole});
              }
            });

    connect(recipeIngredient, &QRecipeIngredient::quantityChanged, this,
            [this, recipeIngredient]() {
              int row = m_recipeIngredients.indexOf(recipeIngredient);
              if (row >= 0) {
                QModelIndex index = this->index(row);
                emit dataChanged(index, index, {Roles::QuantityRole});
              }
            });

    connect(recipeIngredient, &QRecipeIngredient::unitChanged, this,
            [this, recipeIngredient]() {
              int row = m_recipeIngredients.indexOf(recipeIngredient);
              if (row >= 0) {
                QModelIndex index = this->index(row);
                emit dataChanged(index, index, {Roles::UnitRole});
              }
            });

    connect(recipeIngredient, &QRecipeIngredient::isRecipeChanged, this,
            [this, recipeIngredient]() {
              int row = m_recipeIngredients.indexOf(recipeIngredient);
              if (row >= 0) {
                QModelIndex index = this->index(row);
                emit dataChanged(index, index, {Roles::IsRecipeRole});
              }
            });
  }
  endInsertRows();
}

void RecipeIngredientModelList::addRecipeIngredient(
    QRecipeIngredient *recipeIngredient) {
  beginInsertRows(QModelIndex(), rowCount(), rowCount());
  m_recipeIngredients.append(recipeIngredient);

  // Connect all the signals
  connect(recipeIngredient, &QRecipeIngredient::ingredientChanged, this,
          [this, recipeIngredient]() {
            int row = m_recipeIngredients.indexOf(recipeIngredient);
            if (row >= 0) {
              QModelIndex index = this->index(row);
              emit dataChanged(index, index, {Roles::NameRole});
              emit dataChanged(index, index, {Roles::DescriptionRole});
            }
          });

  connect(recipeIngredient, &QRecipeIngredient::quantityChanged, this,
          [this, recipeIngredient]() {
            int row = m_recipeIngredients.indexOf(recipeIngredient);
            if (row >= 0) {
              QModelIndex index = this->index(row);
              emit dataChanged(index, index, {Roles::QuantityRole});
            }
          });

  connect(recipeIngredient, &QRecipeIngredient::unitChanged, this,
          [this, recipeIngredient]() {
            int row = m_recipeIngredients.indexOf(recipeIngredient);
            if (row >= 0) {
              QModelIndex index = this->index(row);
              emit dataChanged(index, index, {Roles::UnitRole});
            }
          });

  connect(recipeIngredient, &QRecipeIngredient::isRecipeChanged, this,
          [this, recipeIngredient]() {
            int row = m_recipeIngredients.indexOf(recipeIngredient);
            if (row >= 0) {
              QModelIndex index = this->index(row);
              emit dataChanged(index, index, {Roles::IsRecipeRole});
            }
          });
  endInsertRows();
}
