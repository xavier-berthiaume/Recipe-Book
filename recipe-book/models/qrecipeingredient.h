#ifndef QRECIPEINGREDIENT_H
#define QRECIPEINGREDIENT_H

#include "recipeingredient.h"
#include "storable.h"

class QRecipeIngredient : public Storable {
  Q_OBJECT

  Q_PROPERTY(QUuid ingredientId READ getIngredientId)
  Q_PROPERTY(QString unit READ getUnit WRITE setUnit NOTIFY unitChanged)
  Q_PROPERTY(
      double quantity READ getQuantity WRITE setQuantity NOTIFY quantityChanged)

  RecipeIngredient m_ingredient;

public:
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

  static QString unitToString(Units unit);
  static Units stringToUnits(const QString &unit);

  explicit QRecipeIngredient(const QUuid &ingredientId, Units unit,
                             double quantity, QObject *parent = nullptr);

  explicit QRecipeIngredient(const QUuid &id, const QUuid &ingredientId,
                             Units unit, double quantity,
                             QObject *parent = nullptr);

  QUuid getIngredientId() const;
  QString getUnit() const;
  double getQuantity() const;

  void setIngredientId(const QString &ingredientId);
  void setUnit(const QString &unit);
  void setUnit(Units unit);
  void setQuantity(double quantity);

signals:
  void ingredientIdChanged();
  void unitChanged();
  void quantityChanged();
};

#endif
