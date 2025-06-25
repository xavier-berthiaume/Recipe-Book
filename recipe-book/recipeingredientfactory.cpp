#include "recipeingredientfactory.h"

#include <QDebug>

RecipeIngredientFactory::RecipeIngredientFactory(QObject *parent)
    : QObject{parent}
{}

void RecipeIngredientFactory::createRecipeIngredient(QIngredient *ingredient,
                                                     const QString &quantity,
                                                     QRecipeIngredient::Units unit,
                                                     bool isRecipe) {

    QRecipeIngredient *newRecipeIngredient = new QRecipeIngredient(ingredient, quantity, unit);
    newRecipeIngredient->setIsRecipe(isRecipe);

    qDebug() << QString("Created RecipeIngredient %1 -> %2%3").arg(ingredient->getName(),
                                                                   quantity,
                                                                   QRecipeIngredient::unitToString(unit));
    emit recipeIngredientCreated(newRecipeIngredient);
}
