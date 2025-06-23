#include "ingredientlistmodel.h"

IngredientListModel::IngredientListModel(QObject *parent)
    : QAbstractListModel{parent}
{}

int IngredientListModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent)
    return m_ingredients.size();
}

QVariant IngredientListModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid() && index.row() >= m_ingredients.size()) return QVariant();

    QIngredient *ingredient = m_ingredients[index.row()];

    switch(role) {
    case Roles::NameRole:
        return ingredient->getName();

    case Roles::DescriptionRole:
        return ingredient->getDescription();

    case Roles::IdRole:
        return ingredient->getId();

    case Roles::CreatorRole:
        return QVariant::fromValue<QProfile *>(ingredient->getCreator());

    default:
        return QVariant();
    }
}

QHash<int, QByteArray> IngredientListModel::roleNames() const {
    return {
        {Roles::NameRole, "Name"},
        {Roles::DescriptionRole, "Description"},
        {Roles::IdRole, "ID"},
        {Roles::CreatorRole, "Creator"}
    };
}

void IngredientListModel::populate(const QList<QIngredient *> &list) {

    if (list.isEmpty()) return;

    if (!m_ingredients.isEmpty()) {
        beginResetModel();
        qDeleteAll(m_ingredients);
        m_ingredients.clear();
        endResetModel();
    }

    beginInsertRows(QModelIndex(), rowCount(), rowCount() + list.size() - 1);
    for (QIngredient *ingredient : list) {
        m_ingredients.append(ingredient);

        connect(ingredient, &QIngredient::nameChanged, this, [this, ingredient]() {
            int row = m_ingredients.indexOf(ingredient);
            if (row >= 0) {
                QModelIndex index = this->index(row);
                emit dataChanged(index, index, {Roles::NameRole});
            }
        });

        connect(ingredient, &QIngredient::descriptionChanged, this, [this, ingredient]() {
            int row = m_ingredients.indexOf(ingredient);
            if (row >= 0) {
                QModelIndex index = this->index(row);
                emit dataChanged(index, index, {Roles::DescriptionRole});
            }
        });
    }

    endInsertRows();
}

void IngredientListModel::addIngredient(QIngredient *ingredient) {

    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_ingredients.append(ingredient);

    connect(ingredient, &QIngredient::nameChanged, this, [this, ingredient]() {
        int row = m_ingredients.indexOf(ingredient);
        if (row >= 0) {
            QModelIndex index = this->index(row);
            emit dataChanged(index, index);
        }
    });

    connect(ingredient, &QIngredient::descriptionChanged, this, [this, ingredient]() {
        int row = m_ingredients.indexOf(ingredient);
        if (row >= 0) {
            QModelIndex index = this->index(row);
            emit dataChanged(index, index);
        }
    });
    endInsertRows();
}

void IngredientListModel::modifyIngredient(int index, const QVariant &data, int role) {

    QModelIndex indx = this->index(index);
    if (!indx.isValid() || index >= m_ingredients.size()) return;

    QIngredient *ingredient = m_ingredients[index];

    switch (role) {
    case IngredientListModel::NameRole:
        if (ingredient->getName() != data.toString()) {
            ingredient->setName(data.toString());
            emit dataChanged(indx, indx);
        }
        break;

    case IngredientListModel::DescriptionRole:
        if (ingredient->getDescription() != data.toString()) {
            ingredient->setDescription(data.toString());
            emit dataChanged(indx, indx);
        }
        break;

    default:
        break;
    }
}

void IngredientListModel::removeIngredient(int index) {
    if (index < 0 || index >= m_ingredients.size()) return;

    beginRemoveRows(QModelIndex(), index, index);
    m_ingredients.removeAt(index);
    endRemoveRows();
}

void IngredientListModel::ingredientCreated(QIngredient *ingredient) {
    ingredient->setParent(this);
    addIngredient(ingredient);
    qDebug() << "Added ingredient to IngredientListModel with name " << ingredient->getName();
}
