#include "recipelistmodel.h"

RecipeListModel::RecipeListModel(QObject *parent)
    : GenericListModel<QRecipe>(parent) {}

void RecipeListModel::connectModelSignals(QRecipe *model) const {}

QHash<int, QByteArray> RecipeListModel::roleNames() const {

  return {{NameRole, "Name"},           {DescriptionRole, "DescriptionRole"},
          {NotesRole, "Notes"},         {InstructionsRole, "Instructions"},
          {EquipmentRole, "Equipment"}, {IngredientsRole, "Ingredients"}};
}

QVariant RecipeListModel::data(const QModelIndex &index, int role) const {
  if (!index.isValid() || index.row() >= m_modelList.size())
    return QVariant();

  QRecipe *recipe = m_modelList.at(index.row());
  switch (role) {
  case NameRole:
    return recipe->getName();
  case DescriptionRole:
    return recipe->getDescription();
  case NotesRole:
    return recipe->getNotes();
  case InstructionsRole:
    return recipe->getInstructions();
  case EquipmentRole:
    return recipe->getEquipment();
  case IngredientsRole:
    return QVariant::fromValue(recipe->getIngredientIds());
  case IdRole:
    return recipe->getId();
  default:
    return QVariant();
  }
}

QRecipe *RecipeListModel::getRecipe(const QModelIndex &index) const {
  if (!index.isValid() || index.row() >= m_modelList.size())
    return nullptr;

  return m_modelList.at(index.row());
}

void RecipeListModel::modifyModel(int index, const QVariant &data, int role) {
  QModelIndex idx = this->index(index);
  if (!idx.isValid() || index >= m_modelList.size())
    return;

  QRecipe *recipe = m_modelList[index];

  switch (role) {
  case NameRole:
    recipe->setName(data.toString());
    break;

  case DescriptionRole:
    recipe->setDescription(data.toString());
    break;

  case NotesRole:
    recipe->setNotes(data.toString());
    break;

  case InstructionsRole:
    recipe->setInstructions(data.toStringList());
    break;

  case EquipmentRole:
    recipe->setEquipment(data.toStringList());
    break;

  case IngredientsRole:
    recipe->setIngredientIds(data.value<QList<QUuid>>());
    break;

  default:
    qWarning() << "Tried setting an invalid field for QIngredient";
    break;
  }
}

void RecipeListModel::clearModel() {
  qDebug() << "Clearing recipe model";

  beginResetModel();
  qDeleteAll(m_modelList);
  m_modelList.clear();
  endResetModel();
}
