#ifndef QRECIPEINGREDIENT_H
#define QRECIPEINGREDIENT_H

#include "recipeingredient.h"
#include "storable.h"

enum Units {
  INVALID = -1,
  UNITLESS,
  KILOGRAMS,
  GRAMS,
  MILLIGRAMS,
  LITERS,
  CENTILITERS,
  MILLILITERS,
  GALLONS,
  PINTS,
  CUPS,
  TEASPOONS,
  TABLESPOONS
};

class QRecipeIngredient : public Storable {
  Q_OBJECT

  Q_ENUM(Units)
  Q_PROPERTY(QUuid ingredientId READ getIngredientId)
  Q_PROPERTY(Units unit READ getUnit WRITE setUnit NOTIFY unitChanged)
  Q_PROPERTY(
      double quantity READ getQuantity WRITE setQuantity NOTIFY quantityChanged)
  Q_PROPERTY(
      bool isRecipe READ getIsRecipe WRITE setIsRecipe NOTIFY isRecipeChanged)

  RecipeIngredient m_ingredient;

public:
  static QString unitToString(Units unit);
  static Units stringToUnits(const QString &unit);
  static QMap<QString, Units> getUnitList();

  explicit QRecipeIngredient(const QUuid &ingredientId, Units unit,
                             double quantity, bool isRecipe,
                             QObject *parent = nullptr);

  explicit QRecipeIngredient(const QUuid &id, const QUuid &ingredientId,
                             Units unit, double quantity, bool isRecipe,
                             QObject *parent = nullptr);

  QUuid getIngredientId() const;
  Units getUnit() const;
  double getQuantity() const;
  bool getIsRecipe() const;

  void setIngredientId(const QString &ingredientId);
  void setUnit(Units unit);
  void setQuantity(double quantity);
  void setIsRecipe(bool isRecipe);

  void accept(DatabaseVisitor *visitor) override;

signals:
  void ingredientIdChanged();
  void unitChanged();
  void quantityChanged();
  void isRecipeChanged();
};

#endif
