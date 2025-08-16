#include "qrecipeingredient.h"
#include "../database.h"

#include <QDebug>

QString QRecipeIngredient::unitToString(Units unit) {
  switch (unit) {
  case UNITLESS:
    return "";
  case KILOGRAMS:
    return "kg";
  case GRAMS:
    return "g";
  case MILLIGRAMS:
    return "mg";
  case LITERS:
    return "L";
  case CENTILITERS:
    return "cL";
  case MILLILITERS:
    return "mL";
  case GALLONS:
    return "gal";
  case PINTS:
    return "pt";
  case CUPS:
    return "cups";
  case TEASPOONS:
    return "tsp";
  case TABLESPOONS:
    return "tbl";
  default:
    qWarning() << "Invalid conversion of" << unit << "to string.";
    return "";
  }
}

Units QRecipeIngredient::stringToUnits(const QString &unit) {
  static const QHash<QString, Units> unitMap = {
      {"", UNITLESS},      {"kg", KILOGRAMS},  {"g", GRAMS},
      {"mg", MILLIGRAMS},  {"L", LITERS},      {"cL", CENTILITERS},
      {"mL", MILLILITERS}, {"gal", GALLONS},   {"pt", PINTS},
      {"cups", CUPS},      {"tsp", TEASPOONS}, {"tbl", TABLESPOONS}};

  QString lowerUnit = unit.toLower().trimmed();
  if (unitMap.contains(lowerUnit)) {
    return unitMap[lowerUnit];
  }

  qWarning() << "Unknown unit string:" << unit;
  return INVALID;
}

QMap<QString, Units> QRecipeIngredient::getUnitList() {
  return {{"", UNITLESS},      {"kg", KILOGRAMS},  {"g", GRAMS},
          {"mg", MILLIGRAMS},  {"L", LITERS},      {"cL", CENTILITERS},
          {"mL", MILLILITERS}, {"gal", GALLONS},   {"pt", PINTS},
          {"cups", CUPS},      {"tsp", TEASPOONS}, {"tbl", TABLESPOONS}};
}

QRecipeIngredient::QRecipeIngredient(const QUuid &ingredientId, Units unit,
                                     double quantity, bool isRecipe,
                                     QObject *parent)
    : Storable(parent),
      m_ingredient(ingredientId.toString().toStdString(),
                   unitToString(unit).toStdString(), quantity, isRecipe) {}

QRecipeIngredient::QRecipeIngredient(const QUuid &id, const QUuid &ingredientId,
                                     Units unit, double quantity, bool isRecipe,
                                     QObject *parent)
    : Storable(id, parent),
      m_ingredient(ingredientId.toString().toStdString(),
                   unitToString(unit).toStdString(), quantity, isRecipe) {}

QUuid QRecipeIngredient::getIngredientId() const {
  return QUuid::fromString(m_ingredient.getIngredientId());
}

Units QRecipeIngredient::getUnit() const {
  return stringToUnits(QString::fromStdString(m_ingredient.getUnit()));
}

double QRecipeIngredient::getQuantity() const {
  return m_ingredient.getQuantity();
}

bool QRecipeIngredient::getIsRecipe() const {
  return m_ingredient.getIsRecipe();
}

void QRecipeIngredient::setIngredientId(const QString &ingredientId) {
  if (ingredientId == QString::fromStdString(m_ingredient.getIngredientId()))
    return;

  m_ingredient.setIngredientId(ingredientId.toStdString());
  emit ingredientIdChanged();
}

void QRecipeIngredient::setUnit(Units unit) {
  QString unitString = unitToString(unit);

  if (unitString == QString::fromStdString(m_ingredient.getUnit()))
    return;

  m_ingredient.setUnit(unitString.toStdString());
  emit unitChanged();
}

void QRecipeIngredient::setQuantity(double quantity) {
  if (quantity == m_ingredient.getQuantity())
    return;

  m_ingredient.setQuantity(quantity);
  emit quantityChanged();
}

void QRecipeIngredient::setIsRecipe(bool isRecipe) {
  if (isRecipe == m_ingredient.getIsRecipe())
    return;

  m_ingredient.setIsRecipe(isRecipe);
  emit isRecipeChanged();
}

void QRecipeIngredient::accept(DatabaseVisitor *visitor) {
  visitor->visit(this);
}
