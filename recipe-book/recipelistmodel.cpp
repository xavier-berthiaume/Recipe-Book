#include "recipelistmodel.h"

RecipeListModel::RecipeListModel(QObject *parent)
    : QAbstractListModel{parent} {}

int RecipeListModel::rowCount(const QModelIndex &parent) const {
  Q_UNUSED(parent)

  return m_recipes.size();
}

QVariant RecipeListModel::data(const QModelIndex &index, int role) const {
  if (!index.isValid() || index.row() >= m_recipes.size())
    return QVariant();

  QRecipe *recipe = m_recipes[index.row()];

  switch (role) {
  case Roles::NameRole:
    return recipe->getName();
  case Roles::DescriptionRole:
    return recipe->getDescription();
  case Roles::PrepTimeRole:
    return recipe->getPrepTime();
  case Roles::IdRole:
    return recipe->getId();
  case Roles::RecipeIngredientsRole:
    return QVariant(); // Return the QList
  case Roles::InstructionsRole:
    return recipe->getInstructions();
  case Roles::EquipmentRole:
    return recipe->getEquipment();
  default:
    return QVariant();
  }
}

QHash<int, QByteArray> RecipeListModel::roleNames() const {
  return {{Roles::NameRole, "Name"},
          {Roles::DescriptionRole, "Description"},
          {Roles::IdRole, "ID"},
          {Roles::PrepTimeRole, "Prep Time"},
          {Roles::RecipeIngredientsRole, "Ingredients"},
          {Roles::InstructionsRole, "Instructions"},
          {Roles::EquipmentRole, "Equipment"},
          {Roles::NoteRole, "Note"}};
}

void RecipeListModel::populate(const QList<QRecipe *> &list) {
  if (list.isEmpty())
    return;

  if (!m_recipes.isEmpty()) {
    beginResetModel();
    qDeleteAll(m_recipes);
    m_recipes.clear();
    endResetModel();
  }

  beginInsertRows(QModelIndex(), rowCount(), rowCount() + list.size() - 1);
  for (QRecipe *recipe : list) {
    m_recipes.append(recipe);

    connect(recipe, &QRecipe::nameChanged, this, [this, recipe]() {
      int row = m_recipes.indexOf(recipe);
      if (row >= 0) {
        QModelIndex index = this->index(row);
        emit dataChanged(index, index, {Roles::NameRole});
      }
    });

    connect(recipe, &QRecipe::descriptionChanged, this, [this, recipe]() {
      int row = m_recipes.indexOf(recipe);
      if (row >= 0) {
        QModelIndex index = this->index(row);
        emit dataChanged(index, index, {Roles::DescriptionRole});
      }
    });

    connect(recipe, &QRecipe::prepTimeChanged, this, [this, recipe]() {
      int row = m_recipes.indexOf(recipe);
      if (row >= 0) {
        QModelIndex index = this->index(row);
        emit dataChanged(index, index, {Roles::PrepTimeRole});
      }
    });

    connect(recipe, &QRecipe::ingredientsChanged, this, [this, recipe]() {
      int row = m_recipes.indexOf(recipe);
      if (row >= 0) {
        QModelIndex index = this->index(row);
        emit dataChanged(index, index, {Roles::RecipeIngredientsRole});
      }
    });

    connect(recipe, &QRecipe::instructionsChanged, this, [this, recipe]() {
      int row = m_recipes.indexOf(recipe);
      if (row >= 0) {
        QModelIndex index = this->index(row);
        emit dataChanged(index, index, {Roles::InstructionsRole});
      }
    });

    connect(recipe, &QRecipe::equipmentChanged, this, [this, recipe]() {
      int row = m_recipes.indexOf(recipe);
      if (row >= 0) {
        QModelIndex index = this->index(row);
        emit dataChanged(index, index, {Roles::EquipmentRole});
      }
    });

    connect(recipe, &QRecipe::notesChanged, this, [this, recipe]() {
      int row = m_recipes.indexOf(recipe);
      if (row >= 0) {
        QModelIndex index = this->index(row);
        emit dataChanged(index, index, {Roles::NoteRole});
      }
    });
  }
  endInsertRows();
}

void RecipeListModel::addRecipe(QRecipe *recipe) {
  beginInsertRows(QModelIndex(), rowCount(), rowCount());
  m_recipes.append(recipe);

  connect(recipe, &QRecipe::nameChanged, this, [this, recipe]() {
    int row = m_recipes.indexOf(recipe);
    if (row >= 0) {
      QModelIndex index = this->index(row);
      emit dataChanged(index, index, {Roles::NameRole});
    }
  });

  connect(recipe, &QRecipe::descriptionChanged, this, [this, recipe]() {
    int row = m_recipes.indexOf(recipe);
    if (row >= 0) {
      QModelIndex index = this->index(row);
      emit dataChanged(index, index, {Roles::DescriptionRole});
    }
  });

  connect(recipe, &QRecipe::prepTimeChanged, this, [this, recipe]() {
    int row = m_recipes.indexOf(recipe);
    if (row >= 0) {
      QModelIndex index = this->index(row);
      emit dataChanged(index, index, {Roles::PrepTimeRole});
    }
  });

  connect(recipe, &QRecipe::ingredientsChanged, this, [this, recipe]() {
    int row = m_recipes.indexOf(recipe);
    if (row >= 0) {
      QModelIndex index = this->index(row);
      emit dataChanged(index, index, {Roles::RecipeIngredientsRole});
    }
  });

  connect(recipe, &QRecipe::instructionsChanged, this, [this, recipe]() {
    int row = m_recipes.indexOf(recipe);
    if (row >= 0) {
      QModelIndex index = this->index(row);
      emit dataChanged(index, index, {Roles::InstructionsRole});
    }
  });

  connect(recipe, &QRecipe::equipmentChanged, this, [this, recipe]() {
    int row = m_recipes.indexOf(recipe);
    if (row >= 0) {
      QModelIndex index = this->index(row);
      emit dataChanged(index, index, {Roles::EquipmentRole});
    }
  });

  connect(recipe, &QRecipe::notesChanged, this, [this, recipe]() {
    int row = m_recipes.indexOf(recipe);
    if (row >= 0) {
      QModelIndex index = this->index(row);
      emit dataChanged(index, index, {Roles::NoteRole});
    }
  });

  endInsertRows();
}

void RecipeListModel::modifyRecipe(int index, const QVariant &data, int role) {
  QModelIndex indx = this->index(index);
  if (!indx.isValid() || index >= m_recipes.size())
    return;

  QRecipe *recipe = m_recipes[index];

  switch (role) {
  case Roles::NameRole:
    if (recipe->getName() != data.toString()) {
      recipe->setName(data.toString());
      emit dataChanged(indx, indx);
    }
    break;

  case Roles::DescriptionRole:
    if (recipe->getDescription() != data.toString()) {
      recipe->setDescription(data.toString());
      emit dataChanged(indx, indx);
    }
    break;

  case Roles::PrepTimeRole:
    if (recipe->getPrepTime() != data.toUInt()) {
      recipe->setPrepTime(data.toUInt());
      emit dataChanged(indx, indx);
    }
    break;

  case Roles::RecipeIngredientsRole:
    // TODO
    break;

  case Roles::InstructionsRole:
    // You might need to improve on the equality check
    if (recipe->getInstructions() != data.toStringList()) {
      recipe->setInstructions(data.toStringList());
      emit dataChanged(indx, indx);
    }
    break;

  case Roles::EquipmentRole:
    if (recipe->getEquipment() != data.toStringList()) {
      recipe->setEquipment(data.toStringList());
      emit dataChanged(indx, indx);
    }
    break;

  default:
    break;
  }
}

void RecipeListModel::removeRecipe(int index) {
  if (index < 0 || index >= m_recipes.size())
    return;

  beginRemoveRows(QModelIndex(), index, index);
  m_recipes.removeAt(index);
  endRemoveRows();
}

QRecipe *RecipeListModel::getRecipe(const QModelIndex &index) {
  if (!index.isValid())
    return nullptr;

  return getRecipe(index.row());
}

QRecipe *RecipeListModel::getRecipe(int index) {
  if (index < 0 || index >= m_recipes.size())
    return nullptr;

  return m_recipes[index];
}

void RecipeListModel::clear() {
  beginResetModel();
  qDeleteAll(m_recipes);
  m_recipes.clear();
  endResetModel();
}
