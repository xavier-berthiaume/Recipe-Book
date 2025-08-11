#ifndef RECIPELISTMODEL_H
#define RECIPELISTMODEL_H

#include "genericlistmodel.h"
#include "../models.h"

class RecipeListModel : public GenericListModel<QRecipe>
{
    Q_OBJECT

protected:
    void connectModelSignals(QRecipe *model) const override;

public:
    enum Roles {
        NameRole = Qt::UserRole + 1,
        DescriptionRole,
        NotesRole,
        PrepTimeRole,
        InstructionsRole,
        EquipmentRole,
        IngredientsRole,
        IdRole,
    };
    explicit RecipeListModel(QObject *parent = nullptr);

    QHash<int, QByteArray> roleNames() const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QRecipe *getRecipe(const QModelIndex &index) const;

    void modifyModel(int index, const QVariant &data, int role = Qt::DisplayRole) override;

    void clearModel();
};

#endif // RECIPELISTMODEL_H
