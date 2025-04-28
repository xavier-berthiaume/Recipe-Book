#ifndef RECIPEINGREDIENT_H
#define RECIPEINGREDIENT_H

#include "storable.h"

#include <QString>
#include <QUuid>

class RecipeIngredient : public Storable {

  QUuid recipe_id;
  QUuid ingredient_id;
  QString quantity;
  QString unit;

public:
  explicit RecipeIngredient(QUuid recipe_id, QUuid ingredient_id,
                            const QString &quantity, const QString &unit);

  QUuid getRecipeId() const;
  QUuid getIngredientId() const;
  const QString &getQuantity() const;
  const QString &getUnit() const;

  void setRecipeId(QUuid recipe_id);
  void setIngredientId(QUuid ingredient_id);
  void setQuantity(const QString &quantity);
  void setUnit(const QString &unit);
};

#endif
