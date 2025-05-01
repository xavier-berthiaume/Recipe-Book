#ifndef QT_INGREDIENT_WRAPPER_H
#define QT_INGREDIENT_WRAPPER_H

#include "ingredient.h"
#include "storable.h"

#include <QObject>
#include <QString>

class QtIngredientWrapper : public Storable {
  Q_OBJECT
  Q_PROPERTY(QString name READ getName WRITE setName NOTIFY nameChanged)
  Q_PROPERTY(QString description READ getDescription WRITE setDescription NOTIFY
                 descriptionChanged)

  bool m_is_recipe;
  QUuid m_linked_recipe_id;
  Ingredient m_ingredient; // The actual Ingredient instance being wrapped

public:
  explicit QtIngredientWrapper(QObject *parent = nullptr);
  explicit QtIngredientWrapper(QUuid id, QObject *parent = nullptr);
  QtIngredientWrapper(const QString &name, const QString &description,
                      QObject *parent = nullptr);
  QtIngredientWrapper(const Ingredient &ingredient, QObject *parent = nullptr);
  ~QtIngredientWrapper();

  // Property accessors
  QString getName() const;
  QString getDescription() const;
  bool getIsRecipe() const;
  QUuid getLinkedRecipeId() const;
  const Ingredient &getIngredient() const;

  // Property setters
  void setName(const QString &name);
  void setDescription(const QString &description);

signals:
  void nameChanged();
  void descriptionChanged();
};

#endif
