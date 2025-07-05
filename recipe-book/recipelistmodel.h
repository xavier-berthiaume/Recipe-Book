#ifndef RECIPELISTMODEL_H
#define RECIPELISTMODEL_H

#include <QAbstractListModel>

#include "qrecipe.h"

class RecipeListModel : public QAbstractListModel
{
    Q_OBJECT

    QList<QRecipe *> m_recipes;

public:
    enum Roles {
        NameRole = Qt::UserRole,
        DescriptionRole,
        IdRole,
        PrepTimeRole,
        RecipeIngredientsRole,
        InstructionsRole,
        EquipmentRole,
        NoteRole
    };

    explicit RecipeListModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index,
                  int role = Qt::DisplayRole) const override;

    QHash<int, QByteArray> roleNames() const override;

    void populate(const QList<QRecipe *> &recipes);

    void addRecipe(QRecipe *recipe);

    void modifyRecipe(int index, const QVariant &data, int role = Qt::DisplayRole);

    void removeRecipe(int index);

    QRecipe *getRecipe(const QModelIndex &index);

    QRecipe *getRecipe(int index);

    void clear();
};

#endif // RECIPELISTMODEL_H
