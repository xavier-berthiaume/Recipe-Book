#ifndef SQLITEDBMANAGER_H
#define SQLITEDBMANAGER_H

#include "abstractdbmanager.h"
#include "qingredient.h"
#include "qprofile.h"
#include "qrecipe.h"
#include "qrecipeingredient.h"

#include <QtSql/QSqlDatabase>
#include <QtSql/qsqldatabase.h>

class SqliteDbManager : public AbstractDbManager {
  Q_OBJECT

  // Templated helper function for the readAllObject function
  template <typename T> bool readAllObjectsImpl(QList<QObject *> &objects) {
    QList<T *> specificList;
    bool success = false;

    if constexpr (std::is_same_v<T, QProfile>) {
      success = readAllProfiles(specificList);
    } else if constexpr (std::is_same_v<T, QIngredient>) {
      success = readAllIngredients(specificList);
    } else if constexpr (std::is_same_v<T, QRecipeIngredient>) {
      success = readAllRecipeIngredients(specificList);
    } else if constexpr (std::is_same_v<T, QRecipe>) {
      success = readAllRecipes(specificList);
    }

    if (success) {
      for (T *obj : specificList) {
        objects.append(static_cast<QObject *>(obj));
      }
    }
    return success;
  }

  bool saveProfile(const QProfile &profile);
  bool updateProfile(const QProfile &profile);
  // Both the following functions return new objects with dangling pointers.
  // Whatever calls these must set the parent to the objects
  QProfile *readProfile(const QUuid &id);
  bool readAllProfiles(QList<QProfile *> &emptyProfileList);
  bool deleteProfile(const QUuid &id);

  bool saveIngredient(const QIngredient &ingredient);
  bool updateIngredient(const QIngredient &ingredient);
  // Both the following functions return new objects with dangling pointers.
  // Whatever calls these must set the parent to the objects
  QIngredient *readIngredient(const QUuid &id);
  bool readAllIngredients(QList<QIngredient *> &emptyIngredientList);
  bool deleteIngredient(const QUuid &id);

  bool saveRecipeIngredient(const QRecipeIngredient &ingredient);
  bool updateRecipeIngredient(const QRecipeIngredient &ingredient);
  // Both the following functions return new objects with dangling pointers.
  // Whatever calls these must set the parent to the objects
  QRecipeIngredient *readRecipeIngredient(const QUuid &id);
  bool readAllRecipeIngredients(
      QList<QRecipeIngredient *> &emptyRecipeIngredientList);
  bool deleteRecipeIngredient(const QUuid &id);

  bool saveRecipe(const QRecipe &recipe);
  bool updateRecipe(const QRecipe &recipe);
  bool updateRecipeIngredientList(const QRecipe &recipe);
  bool updateInstructionList(const QRecipe &recipe);
  bool updateEquipmentList(const QRecipe &recipe);
  // Both the following functions return new objects with dangling pointers.
  // Whatever calls these must set the parent to the objects
  QRecipe *readRecipe(const QUuid &id);
  bool readAllRecipes(QList<QRecipe *> &emptyRecipeList);
  bool deleteRecipe(const QUuid &id);

  QSqlDatabase m_database;

public:
  explicit SqliteDbManager(
      const QString &path, ProfileFactory *profileFactory = nullptr,
      IngredientFactory *ingredientFactory = nullptr,
      RecipeIngredientFactory *recipeingredientFactory = nullptr,
      RecipeFactory *recipeFactory = nullptr, QObject *parent = nullptr);

  // Marked as override to make sure it runs on parent destructor call
  ~SqliteDbManager() override;

  bool saveObject(QObject *object) override;
  bool updateObject(QObject *object) override;
  QObject *readObject(const QString &objectType, const QUuid &id) override;
  bool readAllObjects(ObjectType type, QList<QObject *> &objects) override;
  bool deleteObject(const QString &objectType, const QUuid &id) override;

  bool beginTransaction() override;
  bool commitTransaction() override;
  bool rollbackTransaction() override;

  bool openDatabase();
  void closeDatabase();
  bool createTables();
};

#endif
