#include "ingredientlistmodel.h"

IngredientListModel::IngredientListModel(QObject *parent)
    : GenericListModel<QIngredient>(parent) {}

// TODO
void IngredientListModel::connectModelSignals(QIngredient *model) const {}

QHash<int, QByteArray> IngredientListModel::roleNames() const {
  return {{NameRole, "Name"}, {DescriptionRole, "Description"}, {IdRole, "Id"}};
}

QVariant IngredientListModel::data(const QModelIndex &index, int role) const {
  if (!index.isValid() || index.row() >= m_modelList.size())
    return QVariant();

  QIngredient *ingredient = m_modelList.at(index.row());

  switch (role) {
  case NameRole:
    return ingredient->getName();

  case DescriptionRole:
    return ingredient->getDescription();

  default:
    return QVariant();
  }
}

QIngredient *
IngredientListModel::getIngredient(const QModelIndex &index) const {
  qDebug() << "Getting ingredient at index" << index.row();
  if (!index.isValid() || index.row() >= m_modelList.size()) {
    qWarning() << "Invalid index passed";
    return nullptr;
  }

  return m_modelList[index.row()];
}

void IngredientListModel::modifyModel(int index, const QVariant &data,
                                      int role) {
  QModelIndex indx = this->index(index);
  if (!indx.isValid() || index >= m_modelList.size())
    return;

  QIngredient *ingredient = m_modelList[index];

  switch (role) {
  case NameRole:
    ingredient->setName(data.toString());
    break;

  case DescriptionRole:
    ingredient->setDescription(data.toString());
    break;

  default:
    qWarning() << "Tried setting an invalid field for QIngredient";
    break;
  }
}

void IngredientListModel::clearModel() {
  qDebug() << "Clearing ingredient model";

  beginResetModel();
  qDeleteAll(m_modelList);
  m_modelList.clear();
  endResetModel();
}
