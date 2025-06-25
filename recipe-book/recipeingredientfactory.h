#ifndef RECIPEINGREDIENTFACTORY_H
#define RECIPEINGREDIENTFACTORY_H

#include <QObject>

#include "qrecipeingredient.h"

class RecipeIngredientFactory : public QObject
{
    Q_OBJECT
public:
    explicit RecipeIngredientFactory(QObject *parent = nullptr);

    void createRecipeIngredient(QIngredient *ingredient,
                                const QString &quantity,
                                QRecipeIngredient::Units unit,
                                bool isRecipe);

signals:
    void recipeIngredientCreated(QRecipeIngredient *newRecipeIngredient);
};

#endif // RECIPEINGREDIENTFACTORY_H
