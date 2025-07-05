#ifndef RECIPEFACTORY_H
#define RECIPEFACTORY_H

#include <QObject>

#include "qrecipe.h"
#include "qrecipeingredient.h"

class RecipeFactory : public QObject {
  Q_OBJECT
public:
  explicit RecipeFactory(QObject *parent = nullptr);

  void createRecipe(QProfile *currentUser, const QString &name,
                    const QString &description, quint32 prepTime,
                    const QList<QRecipeIngredient *> &ingredients,
                    const QStringList &instructions,
                    const QStringList &equipment);

signals:
  void recipeCreated(QRecipe *newRecipe);
};

#endif // RECIPEFACTORY_H
