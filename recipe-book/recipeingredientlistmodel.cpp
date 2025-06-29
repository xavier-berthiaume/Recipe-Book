#include "recipeingredientlistmodel.h"

RecipeIngredientListModel::RecipeIngredientListModel(QObject *parent)
    : QAbstractListModel{parent} {}

int RecipeIngredientListModel::rowCount(const QModelIndex &parent) const {
  Q_UNUSED(parent)

  return m_recipeIngredients.size();
}

QVariant RecipeIngredientListModel::data(const QModelIndex &index,
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

QHash<int, QByteArray> RecipeIngredientListModel::roleNames() const {
  return {{Roles::NameRole, "Name"}, {Roles::DescriptionRole, "Description"},
          {Roles::IdRole, "ID"},     {Roles::QuantityRole, "Quantity"},
          {Roles::UnitRole, "Unit"}, {Roles::IsRecipeRole, "Is Recipe"}};
}

void RecipeIngredientListModel::populate(
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

void RecipeIngredientListModel::addRecipeIngredient(
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

void RecipeIngredientListModel::modifyRecipeIngredient(int index,
                                                       const QVariant &data,
                                                       int role) {
    QModelIndex indx = this->index(index);
    if (!indx.isValid() || index >= m_recipeIngredients.size())
        return;

    QRecipeIngredient *recipeIngredient = m_recipeIngredients[index];

    switch(role) {
    case Roles::NameRole:
        break;

    case Roles::DescriptionRole:
        break;

    case Roles::QuantityRole:
        if (recipeIngredient->getQuantity() != data.toString()) {
            recipeIngredient->setQuantity(data.toString());
            emit dataChanged(indx, indx);
        }
        break;

    case Roles::UnitRole:
        if (recipeIngredient->getUnit() !=
            QRecipeIngredient::unitToString(data.value<QRecipeIngredient::Units>())) {
            recipeIngredient->setUnit(data.value<QRecipeIngredient::Units>());
            emit dataChanged(indx, indx);
        }
        break;

    case Roles::IsRecipeRole:
        if (recipeIngredient->getIsRecipe() != data.toBool()) {
            recipeIngredient->toggleIsRecipe();
            emit dataChanged(indx, indx);
        }
        break;

    default:
        break;
    }
}

void RecipeIngredientListModel::removeRecipeIngredient(int index) {
    if (index < 0 || index >= m_recipeIngredients.size()) return;

    m_recipeIngredients.removeAt(index);
}

void RecipeIngredientListModel::recipeIngredientCreated(QRecipeIngredient *recipeIngredient) {
    recipeIngredient->setParent(this);
    addRecipeIngredient(recipeIngredient);
    qDebug() << "Added recipe ingredient to RecipeIngredientModel with name "
             << QString("%1, %2%3").arg(
                    recipeIngredient->getIngredient()->getName(),
                    recipeIngredient->getQuantity(),
                    recipeIngredient->getUnit());
}
