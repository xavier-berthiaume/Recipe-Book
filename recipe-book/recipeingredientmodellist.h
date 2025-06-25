#ifndef RECIPEINGREDIENTMODELLIST_H
#define RECIPEINGREDIENTMODELLIST_H

#include <QAbstractListModel>
#include <QObject>

#include "qrecipeingredient.h"

class RecipeIngredientModelList : public QAbstractListModel {
  Q_OBJECT

  QList<QRecipeIngredient *> m_recipeIngredients;

public:
  enum Roles {
    NameRole = Qt::UserRole,
    DescriptionRole,
    IdRole,
    QuantityRole,
    UnitRole,
    IsRecipeRole
  };

  explicit RecipeIngredientModelList(QObject *parent = nullptr);

  int rowCount(const QModelIndex &parent = QModelIndex()) const override;

  QVariant data(const QModelIndex &index,
                int role = Qt::DisplayRole) const override;

  QHash<int, QByteArray> roleNames() const override;

  void populate(const QList<QRecipeIngredient *> &recipeIngredients);

  void addRecipeIngredient(QRecipeIngredient *recipeIngredient);

  void modifyRecipeIngredient(int index, const QVariant &data,
                              int role = Qt::DisplayRole);

  void removeRecipeIngredient(int index);

public slots:
  void recipeIngredientCreated(QRecipeIngredient *recipeIngredient);
};

#endif // RECIPEINGREDIENTMODELLIST_H
