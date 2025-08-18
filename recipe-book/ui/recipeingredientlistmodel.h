#ifndef RECIPEINGREDIENTLISTMODEL_H
#define RECIPEINGREDIENTLISTMODEL_H

#include "../models.h"
#include "genericlistmodel.h"
#include <qhash.h>

class RecipeIngredientListModel : public GenericListModel<QRecipeIngredient> {
  Q_OBJECT

  QHash<QUuid, QIngredient *> m_ingredients;

protected:
  void connectModelSignals(QRecipeIngredient *model) const override;

public:
  enum Roles {
    IngredientIdRole = Qt::UserRole + 1,
    NameRole,
    QuantityRole,
    UnitRole,
    IsRecipeRole,
    IdRole
  };

  explicit RecipeIngredientListModel(QObject *parent = nullptr);

  QHash<int, QByteArray> roleNames() const override;

  QVariant data(const QModelIndex &index,
                int role = Qt::DisplayRole) const override;

  QRecipeIngredient *getRecipeIngredient(const QModelIndex &index) const;

  void modifyModel(int index, const QVariant &data,
                   int role = Qt::DisplayRole) override;

  void addIngredientToCache(QIngredient *object);

  void clearModel();
};

#endif
