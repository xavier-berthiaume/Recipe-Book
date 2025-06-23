#include "qrecipeingredient.h"

QRecipeIngredient::QRecipeIngredient(QIngredient *ingredient,
                                       const QString &quantity,
                                       Units unit, QObject *parent)
    : QObject(parent)
    , m_ingredient(ingredient)
    , m_quantity(quantity)
{
    setUnit(unit);
}

QIngredient *QRecipeIngredient::getIngredient() const {
    return m_ingredient;
}

QString QRecipeIngredient::getQuantity() const {
    return m_quantity;
}

QString QRecipeIngredient::getUnit() const {
    return m_unit;
}

bool QRecipeIngredient::getIsRecipe() const {
    return m_isRecipe;
}

void QRecipeIngredient::setIngredient(QIngredient *ingredient) {
    if (ingredient == m_ingredient) return;

    m_ingredient = ingredient;
    emit ingredientChanged();
}

void QRecipeIngredient::setQuantity(const QString &quantity) {
    if (quantity == m_quantity) return;

    m_quantity = quantity;
    emit quantityChanged();
}

void QRecipeIngredient::setUnit(const QString &unit) {
    if (unit == m_unit) return;

    m_unit = unit;
    emit unitChanged();
}

void QRecipeIngredient::setUnit(Units unit) {
    QString convertedUnit = unitToString(unit);

    if (convertedUnit == m_unit) return;

    m_unit = convertedUnit;
    emit unitChanged();
}

void QRecipeIngredient::setIsRecipe(bool isRecipe) {
    if (isRecipe == m_isRecipe) return;

    m_isRecipe = isRecipe;
    emit isRecipeChanged();
}

void QRecipeIngredient::toggleIsRecipe() {
    m_isRecipe = !m_isRecipe;
    emit isRecipeChanged();
}

QString QRecipeIngredient::unitToString(Units unit) {
    switch (unit) {
    case Kilograms: return "kg";
    case Grams: return "g";
    case Milligrams: return "mg";
    case Liters: return "L";
    case Centiliters: return "cL";
    case Milliliters: return "mL";
    case Gallons: return "gal";
    case Pints: return "pt";
    case Cups: return "cups";
    case Tablespoons: return "tbsp";
    case Teaspoons: return "tsp";
    default: return "g";
    }
}
