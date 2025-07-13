#include "sqlitedbmanager.h"
#include "qprofile.h"

#include <QDebug>
#include <QList>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlRecord>
#include <QtSql/qsqlquery.h>

SqliteDbManager::SqliteDbManager(
    const QString &path, ProfileFactory *profileFactory,
    IngredientFactory *ingredientFactory,
    RecipeIngredientFactory *recipeingredientFactory,
    RecipeFactory *recipeFactory, QObject *parent)
    : AbstractDbManager(profileFactory, ingredientFactory,
                        recipeingredientFactory, recipeFactory, parent) {

  m_database = QSqlDatabase::addDatabase("QSQLITE");
  m_database.setDatabaseName(path);

  if (!openDatabase()) {
    qCritical() << "Failed to open database";
  }

  if (!createTables()) {
    qCritical() << "Failed to create tables";
  }
}

SqliteDbManager::~SqliteDbManager() { closeDatabase(); }

bool SqliteDbManager::saveObject(QObject *object) {
  if (!object)
    return false;

  const QString className = object->metaObject()->className();

  if (className == "QProfile") {
    // Try casting to its matching class
    QProfile *profile = (QProfile *)object;
    return saveProfile(*profile);
  } else if (className == "QIngredient") {
    QIngredient *ingredient = (QIngredient *)object;
    return saveIngredient(*ingredient);
  } else if (className == "QRecipeIngredient") {
    QRecipeIngredient *recipeIngredient = (QRecipeIngredient *)object;
    return saveRecipeIngredient(*recipeIngredient);
  } else if (className == "QRecipe") {
    QRecipe *recipe = (QRecipe *)object;
    return saveRecipe(*recipe);
  }

  qWarning() << "Invalid class name tried to be saved to database";
  return false;
}

bool SqliteDbManager::updateObject(QObject *object) {
  if (!object)
    return false;

  const QString className = object->metaObject()->className();

  if (className == "QProfile") {
    QProfile *profile = (QProfile *)object;
    return updateProfile(*profile);
  } else if (className == "QIngredient") {
    QIngredient *ingredient = (QIngredient *)object;
    return updateIngredient(*ingredient);
  } else if (className == "QRecipeIngredient") {
    QRecipeIngredient *recipeIngredient = (QRecipeIngredient *)object;
    return updateRecipeIngredient(*recipeIngredient);
  } else if (className == "QRecipe") {
    QRecipe *recipe = (QRecipe *)object;
    return updateRecipe(*recipe);
  }

  qWarning() << "Invalid class name tried to be saved to database";
  return false;
}

QObject *SqliteDbManager::readObject(const QString &objectType,
                                     const QUuid &id) {

  if (objectType == "Profile") {
    return readProfile(id);
  } else if (objectType == "Ingredient") {
    return readIngredient(id);
  } else if (objectType == "RecipeIngredient") {
    return readRecipeIngredient(id);
  } else if (objectType == "Recipe") {
    return readRecipe(id);
  }

  qWarning() << "Invalid object type";
  return nullptr;
}

bool SqliteDbManager::deleteObject(const QString &objectType, const QUuid &id) {

  if (objectType == "Profile") {
    return deleteProfile(id);
  } else if (objectType == "Ingredient") {
    return deleteIngredient(id);
  } else if (objectType == "RecipeIngredient") {
    return deleteRecipeIngredient(id);
  } else if (objectType == "Recipe") {
    return deleteRecipe(id);
  }

  qWarning() << "Invalid object type";
  return false;
}

bool SqliteDbManager::beginTransaction() { return m_database.transaction(); }

bool SqliteDbManager::commitTransaction() { return m_database.commit(); }

bool SqliteDbManager::rollbackTransaction() { return m_database.rollback(); }

bool SqliteDbManager::openDatabase() {

  if (!m_database.isOpen()) {
    if (!m_database.open()) {
      qCritical() << "Error opening database:" << m_database.lastError().text();
      qCritical() << "Database path:" << m_database.databaseName();
      return false;
    }
    qDebug() << "Database opened successfully";
  }
  return true;

  return true;
}

void SqliteDbManager::closeDatabase() {

  if (m_database.isOpen()) {
    m_database.close();
  }
}

bool SqliteDbManager::createTables() {

  QSqlQuery query;

  bool success = query.exec("CREATE TABLE IF NOT EXISTS profiles ("
                            "id TEXT PRIMARY KEY,"
                            "username TEXT UNIQUE NOT NULL,"
                            "created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,"
                            "updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP"
                            ")");

  if (!success) {
    qCritical() << "Failed to create users table." << query.lastError().text();
    return false;
  }

  success = query.exec(
      "CREATE TABLE IF NOT EXISTS ingredients ("
      "id TEXT PRIMARY KEY,"
      "name TEXT NOT NULL,"
      "description TEXT,"
      "creator_id TEXT NOT NULL,"
      "created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,"
      "updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,"
      "FOREIGN KEY (creator_id) REFERENCES profiles(id) ON DELETE CASCADE"
      ")");

  if (!success) {
    qCritical() << "Failed to create ingredients table."
                << query.lastError().text();
    return false;
  }

  success = query.exec(
      "CREATE TABLE IF NOT EXISTS recipe_ingredients ("
      "id TEXT PRIMARY KEY,"
      "ingredient_id TEXT NOT NULL,"
      "quantity TEXT NOT NULL,"
      "unit TEXT NOT NULL,"
      "is_recipe BOOLEAN DEFAULT FALSE,"
      "created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,"
      "updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,"
      "FOREIGN KEY (ingredient_id) REFERENCES ingredients(id) ON DELETE CASCADE"
      ")");

  if (!success) {
    qCritical() << "Failed to create recipe_ingredients table."
                << query.lastError().text();
    return false;
  }

  // Since recipe inherits from ingredient, we use the name, description and
  // creator_id fields of the ingreidents table instead of creating new fields
  // here
  success =
      query.exec("CREATE TABLE IF NOT EXISTS recipes ("
                 "id TEXT PRIMARY KEY,"
                 "prep_time INTEGER DEFAULT 0,"
                 "notes TEXT,"
                 "created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,"
                 "updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,"
                 "FOREIGN KEY (id) REFERENCES ingredients(id) ON DELETE CASCADE"
                 ")");

  if (!success) {
    qCritical() << "Failed to create recipe table." << query.lastError().text();
    return false;
  }

  success = query.exec(
      "CREATE TABLE IF NOT EXISTS recipe_instructions ("
      "id INTEGER PRIMARY KEY AUTOINCREMENT,"
      "recipe_id TEXT NOT NULL,"
      "instruction TEXT NOT NULL,"
      "step_order INTEGER NOT NULL,"
      "FOREIGN KEY (recipe_id) REFERENCES recipes(id) ON DELETE CASCADE"
      ")");

  if (!success) {
    qCritical() << "Failed to create recipe instruction table."
                << query.lastError().text();
    return false;
  }

  success = query.exec(
      "CREATE TABLE IF NOT EXISTS recipe_equipment ("
      "id INTEGER PRIMARY KEY AUTOINCREMENT,"
      "recipe_id TEXT NOT NULL,"
      "equipment TEXT NOT NULL,"
      "FOREIGN KEY (recipe_id) REFERENCES recipes(id) ON DELETE CASCADE"
      ")");

  if (!success) {
    qCritical() << "Failed to create recipe instruction table."
                << query.lastError().text();
    return false;
  }

  success = query.exec(
      "CREATE TABLE IF NOT EXISTS recipe_ingredient_associations ("
      "recipe_id TEXT NOT NULL,"
      "recipe_ingredient_id TEXT NOT NULL,"
      "PRIMARY KEY (recipe_id, recipe_ingredient_id),"
      "FOREIGN KEY (recipe_id) REFERENCES recipes(id) ON DELETE CASCADE,"
      "FOREIGN KEY (recipe_ingredient_id) REFERENCES recipe_ingredients(id) ON "
      "DELETE CASCADE"
      ")");

  return true;
}

bool SqliteDbManager::saveProfile(const QProfile &profile) {

  QSqlQuery query;

  query.prepare("INSERT INTO profiles (id, username) VALUES (:id, :username)");
  query.bindValue(":id", profile.getId().toString());
  query.bindValue(":username", profile.getUsername());

  if (!query.exec()) {
    qWarning() << "Failed to save profile:" << query.lastError().text();
    return false;
  }

  return true;
}

bool SqliteDbManager::updateProfile(const QProfile &profile) {

  QSqlQuery query;

  query.prepare(
      "UPDATE profiles SET username = :username, updated_at = CURRENT_TIMESTAMP"
      "WHERE id=:id");
  query.bindValue(":username", profile.getUsername());
  query.bindValue(":id", profile.getId().toString());

  if (!query.exec()) {
    qWarning() << "Failed to update profile:" << query.lastError().text();
    return false;
  }

  if (query.numRowsAffected() == 0) {
    qWarning() << "No profile found to update with ID:"
               << profile.getId().toString();
    return false;
  }

  return true;
}

QProfile *SqliteDbManager::readProfile(const QUuid &id) {

  QSqlQuery query;

  query.prepare("SELECT * FROM profiles WHERE id = :id");
  query.bindValue(":id", id.toString());

  if (!query.exec()) {
    qWarning() << "Failed to read profile with id:" << id.toString() << "-"
               << query.lastError().text();
    return nullptr;
  }

  if (!query.next()) {
    qDebug() << "No profile found with ID:" << id.toString();
    return nullptr;
  }

  return m_profileFactory->loadProfile(id, query.value("username").toString());
}

bool SqliteDbManager::readAllProfiles(QList<QProfile *> &emptyProfileList) {
  emptyProfileList.clear();

  QSqlQuery query("SELECT id FROM profiles");
  if (!query.exec()) {
    qWarning() << "Failed to read profile IDs:" << query.lastError().text();
    return false;
  }

  while (query.next()) {
    QUuid id = QUuid::fromString(query.value("id").toString());
    QProfile *profile = readProfile(id);
    if (profile) {
      emptyProfileList.append(profile);
    } else {
      qWarning() << "Failed to load profile with ID:" << id.toString();
    }
  }

  return true;
}

bool SqliteDbManager::deleteProfile(const QUuid &id) {

  QSqlQuery query;

  query.prepare("DELETE FROM profiles WHERE id = :id");
  query.bindValue(":id", id.toString());

  if (!query.exec()) {
    qWarning() << "Failed to delete profile:" << query.lastError().text();
    return false;
  }

  if (query.numRowsAffected() == 0) {
    qWarning() << "No profile found to delete with ID:" << id.toString();
    return false;
  }

  return true;
}

bool SqliteDbManager::saveIngredient(const QIngredient &ingredient) {

  QSqlQuery query;

  query.prepare(
      "INSERT INTO ingredients (id, name, description, creator_id) VALUES ("
      ":id, :name, :description, :creator_id)");
  query.bindValue(":id", ingredient.getId().toString());
  query.bindValue(":name", ingredient.getName());
  query.bindValue(":description", ingredient.getDescription());
  query.bindValue(":creator_id", ingredient.getCreator()->getId().toString());

  if (!query.exec()) {
    qWarning() << "Failed to save ingredient" << query.lastError().text();
    return false;
  }

  return true;
}

bool SqliteDbManager::updateIngredient(const QIngredient &ingredient) {

  QSqlQuery query;

  query.prepare("UPDATE ingredients SET name = :name, description = "
                ":description, creator_id = :creator_id, updated_at = "
                "CURRENT_TIMESTAMP WHERE id = :id");
  query.bindValue(":name", ingredient.getName());
  query.bindValue(":description", ingredient.getDescription());
  query.bindValue(":creator_id", ingredient.getCreator()->getId().toString());
  query.bindValue(":id", ingredient.getId().toString());

  if (!query.exec()) {
    qWarning() << "Failed to update profile:" << query.lastError().text();
    return false;
  }

  if (query.numRowsAffected() == 0) {
    qWarning() << "No ingredient found to update with ID:"
               << ingredient.getId().toString();
    return false;
  }

  return true;
}

QIngredient *SqliteDbManager::readIngredient(const QUuid &id) {

  QSqlQuery query;

  query.prepare("SELECT * FROM ingredients WHERE id = :id");
  query.bindValue(":id", id.toString());

  if (!query.exec()) {
    qWarning() << "Failed to read ingredient with id:" << id.toString() << "-"
               << query.lastError().text();
    return nullptr;
  }

  if (!query.next()) {
    qWarning() << "No ingredient found with ID:" << id.toString();
    return nullptr;
  }

  QUuid creator_id = QUuid::fromString(query.value("creator_id").toString());
  QProfile *creator = readProfile(creator_id);
  if (!creator) {
    qWarning() << "Failed to load creator for ingredient:" << id.toString();
    return nullptr;
  }

  return m_ingredientFactory->loadIngredient(
      id, creator, query.value("name").toString(),
      query.value("description").toString());
}

bool SqliteDbManager::readAllIngredients(
    QList<QIngredient *> &emptyIngredientList) {
  emptyIngredientList.clear();

  QSqlQuery query("SELECT id FROM ingredients");
  if (!query.exec()) {
    qWarning() << "Failed to read ingredient IDs:" << query.lastError().text();
    return false;
  }

  while (query.next()) {
    QUuid id = QUuid::fromString(query.value("id").toString());
    QIngredient *ingredient = readIngredient(id);
    if (ingredient) {
      emptyIngredientList.append(ingredient);
    } else {
      qWarning() << "Failed to load ingredient with ID:" << id.toString();
    }
  }

  return true;
}

bool SqliteDbManager::deleteIngredient(const QUuid &id) {

  QSqlQuery query;

  query.prepare("DELETE FROM ingredients WHERE id = :id");
  query.bindValue(":id", id.toString());

  if (!query.exec()) {
    qWarning() << "Failed to delete profile:" << query.lastError().text();
    return false;
  }

  if (query.numRowsAffected() == 0) {
    qWarning() << "No ingredient found to delete with ID:" << id;
    return false;
  }

  return true;
}

bool SqliteDbManager::saveRecipeIngredient(
    const QRecipeIngredient &ingredient) {

  QSqlQuery query;

  query.prepare(
      "INSERT INTO recipe_ingredients (id, ingredient_id, quantity, unit, "
      "is_recipe) VALUES (:id, :ingredient_id, :quantity, :unit, :is_recipe)");
  query.bindValue(":id", ingredient.getId().toString());
  query.bindValue(":ingredient_id",
                  ingredient.getIngredient()->getId().toString());
  query.bindValue(":quantity", ingredient.getQuantity());
  query.bindValue(":unit", ingredient.getUnit());
  query.bindValue(":is_recipe", ingredient.getIsRecipe());

  if (!query.exec()) {
    qWarning() << "Failed to save recipe ingredient"
               << query.lastError().text();
    return false;
  }

  qDebug() << "Saved recipe ingredient with ID:"
           << ingredient.getId().toString();

  return true;
}

bool SqliteDbManager::updateRecipeIngredient(
    const QRecipeIngredient &ingredient) {

  QSqlQuery query;

  query.prepare(
      "UPDATE recipe_ingredients SET ingredient_id = :ingredient_id, quantity "
      "= :quantity, unit = :unit, is_recipe = :is_recipe WHERE id = :id");
  query.bindValue(":ingredient_id",
                  ingredient.getIngredient()->getId().toString());
  query.bindValue(":quantity", ingredient.getQuantity());
  query.bindValue(":unit", ingredient.getUnit());
  query.bindValue(":is_recipe", ingredient.getIsRecipe());
  query.bindValue(":id", ingredient.getId().toString());

  if (!query.exec()) {
    qWarning() << "Failed to update recipe ingredient:"
               << query.lastError().text();
    return false;
  }

  if (query.numRowsAffected() == 0) {
    qWarning() << "No recipe ingredient found to update with ID:"
               << ingredient.getId().toString();
    return false;
  }

  return true;
}

QRecipeIngredient *SqliteDbManager::readRecipeIngredient(const QUuid &id) {

  QSqlQuery query;

  query.prepare("SELECT * FROM recipe_ingredients WHERE id = :id");
  query.bindValue(":id", id.toString());

  if (!query.exec()) {
    qWarning() << "Failed to read recipe ingredient with id:" << id.toString()
               << "-" << query.lastError().text();
    return nullptr;
  }

  if (!query.next()) {
    qWarning() << "No recipe ingredient found with ID:" << id.toString();
    return nullptr;
  }

  QIngredient *ingredient =
      readIngredient(QUuid(query.value("ingredient_id").toString()));
  if (!ingredient) {
    qWarning() << "Failed to load base ingredient for recipe ingredient:"
               << id.toString();
    return nullptr;
  }

  QRecipeIngredient::Units unit =
      QRecipeIngredient::unitOptions()[query.value("unit").toString()];

  return m_recipeingredientFactory->loadRecipeIngredient(
      id, ingredient, query.value("quantity").toString(), unit,
      query.value("is_recipe").toBool());
}

bool SqliteDbManager::readAllRecipeIngredients(
    QList<QRecipeIngredient *> &emptyRecipeIngredientList) {
  emptyRecipeIngredientList.clear();

  QSqlQuery query("SELECT id FROM recipe_ingredients");
  if (!query.exec()) {
    qWarning() << "Failed to read recipe ingredient IDs:"
               << query.lastError().text();
    return false;
  }

  while (query.next()) {
    QUuid id = QUuid::fromString(query.value("id").toString());
    QRecipeIngredient *ri = readRecipeIngredient(id);
    if (ri) {
      emptyRecipeIngredientList.append(ri);
    } else {
      qWarning() << "Failed to load recipe ingredient with ID:"
                 << id.toString();
    }
  }

  return true;
}

bool SqliteDbManager::deleteRecipeIngredient(const QUuid &id) {

  QSqlQuery query;

  query.prepare("DELETE FROM recipe_ingredients WHERE id = :id");
  query.bindValue(":id", id.toString());

  if (!query.exec()) {
    qWarning() << "Failed to delete recipe ingredient:"
               << query.lastError().text();
    return false;
  }

  if (query.numRowsAffected() == 0) {
    qWarning() << "No recipe ingredients found to delete with ID:"
               << id.toString();
    return false;
  }

  return true;
}

bool SqliteDbManager::saveRecipe(const QRecipe &recipe) {

  if (!beginTransaction()) {
    qWarning() << "Failed to begin transaction for saving recipe";
    return false;
  }

  if (!saveIngredient(recipe)) {
    rollbackTransaction();
    qWarning() << "Failed to save base ingredient part of recipe";
    return false;
  }

  QSqlQuery query;

  query.prepare("INSERT INTO recipes (id, prep_time, notes) VALUES (:id, "
                ":prep_time, :notes)");
  query.bindValue(":id", recipe.getId().toString());
  query.bindValue(":prep_time", recipe.getPrepTime());
  query.bindValue(":notes", recipe.getNotes());

  if (!query.exec()) {
    rollbackTransaction();
    qWarning() << "Failed to save recipe" << query.lastError().text();
  }

  for (QRecipeIngredient *ri : recipe.getIngredients()) {
    qDebug() << "Saving recipe ingredient" << ri->getId().toString();
    if (!saveRecipeIngredient(*ri)) {
      rollbackTransaction();
      qWarning() << "Failed to save recipe ingredient details";
      return false;
    }

    query.prepare("INSERT INTO recipe_ingredient_associations "
                  "(recipe_id, recipe_ingredient_id) "
                  "VALUES (:recipe_id, :recipe_ingredient_id)");
    query.bindValue(":recipe_id", recipe.getId().toString());
    query.bindValue(":recipe_ingredient_id", ri->getId().toString());

    if (!query.exec()) {
      rollbackTransaction();
      qWarning() << "Failed to associate recipe ingredient:"
                 << query.lastError().text();
      return false;
    }
  }

  QStringList instructions = recipe.getInstructions();
  for (int i = 0; i < instructions.size(); ++i) {
    query.prepare("INSERT INTO recipe_instructions "
                  "(recipe_id, instruction, step_order) "
                  "VALUES (:recipe_id, :instruction, :step_order)");
    query.bindValue(":recipe_id", recipe.getId().toString());
    query.bindValue(":instruction", instructions[i]);
    query.bindValue(":step_order", i);

    if (!query.exec()) {
      rollbackTransaction();
      qWarning() << "Failed to save instruction:" << query.lastError().text();
      return false;
    }
  }

  QStringList equipment = recipe.getEquipment();
  for (const QString &eq : equipment) {
    query.prepare("INSERT INTO recipe_equipment "
                  "(recipe_id, equipment) "
                  "VALUES (:recipe_id, :equipment)");
    query.bindValue(":recipe_id", recipe.getId().toString());
    query.bindValue(":equipment", eq);

    if (!query.exec()) {
      rollbackTransaction();
      qWarning() << "Failed to save equipment:" << query.lastError().text();
      return false;
    }
  }

  if (!commitTransaction()) {
    qWarning() << "Failed to commit transaction for recipe save";
    rollbackTransaction();
    return false;
  }

  return true;
}

bool SqliteDbManager::updateRecipe(const QRecipe &recipe) {

  if (!beginTransaction()) {
    qWarning() << "Failed to begin transaction for updating recipe";
    return false;
  }

  if (!updateIngredient(recipe)) {
    rollbackTransaction();
    qWarning() << "Failed to update base ingredient part of recipe";
    return false;
  }

  QSqlQuery query;

  query.prepare("UPDATE recipes SET prep_time = :prep_time, notes = :notes "
                "WHERE id = :id");
  query.bindValue(":prep_time", recipe.getPrepTime());
  query.bindValue(":notes", recipe.getNotes());
  query.bindValue(":id", recipe.getId());

  if (!query.exec()) {
    rollbackTransaction();
    qWarning() << "Failed to update recipe" << query.lastError().text();
    return false;
  }

  if (!updateRecipeIngredientList(recipe)) {
    rollbackTransaction();
    qWarning() << "Failed to update recipe ingredients";
    return false;
  }

  if (!updateInstructionList(recipe)) {
    rollbackTransaction();
    qWarning() << "Failed to update instructions";
    return false;
  }

  if (!updateEquipmentList(recipe)) {
    rollbackTransaction();
    qWarning() << "Failed to update equipment";
    return false;
  }

  if (!commitTransaction()) {
    qWarning() << "Failed to commit transaction for recipe update";
    rollbackTransaction();
    return false;
  }

  return true;
}

bool SqliteDbManager::updateRecipeIngredientList(const QRecipe &recipe) {

  QSet<QUuid> existingIngredientIds;
  QSqlQuery query;

  query.prepare(
      "SELECT recipe_ingredient_id FROM recipe_ingredient_associations "
      "WHERE recipe_id = :recipe_id");
  query.bindValue(":recipe_id", recipe.getId().toString());

  if (query.exec()) {
    while (query.next()) {
      existingIngredientIds.insert(
          QUuid(query.value("recipe_ingredient_id").toString()));
    }
  } else {
    qWarning() << "Failed to fetch existing ingredients:"
               << query.lastError().text();
    return false;
  }

  QSet<QUuid> currentIngredientIds;
  for (QRecipeIngredient *ri : recipe.getIngredients()) {
    currentIngredientIds.insert(ri->getId());

    // If the recipe ingredient is already created and associated, then update
    // it otherwise create it Either way create the association if it doesn't
    // already exist
    if (existingIngredientIds.contains(ri->getId())) {
      if (!updateRecipeIngredient(*ri)) {
        qWarning() << "Failed to update recipe ingredient";
        return false;
      }

      existingIngredientIds.remove(ri->getId());
    } else {
      if (!saveRecipeIngredient(*ri)) {
        qWarning() << "Failed to save new recipe ingredient";
        return false;
      }
    }

    QSqlQuery query;
    query.prepare("INSERT OR IGNORE INTO recipe_ingredient_associations "
                  "(recipe_id, recipe_ingredient_id) "
                  "VALUES (:recipe_id, :recipe_ingredient_id)");
    query.bindValue(":recipe_id", recipe.getId().toString());
    query.bindValue(":recipe_ingredient_id", ri->getId().toString());

    if (!query.exec()) {
      qWarning() << "Failed to associate recipe ingredient:"
                 << query.lastError().text();
      return false;
    }
  }

  // Delete associations for ingredients that are no longer part of the recipe
  // Delete orphaned ingredients
  for (const QUuid &id : existingIngredientIds) {
    QSqlQuery query;
    query.prepare("DELETE FROM recipe_ingredient_associations "
                  "WHERE recipe_id = :recipe_id AND "
                  "recipe_ingredient_id = :ingredient_id");
    query.bindValue(":recipe_id", recipe.getId().toString());
    query.bindValue(":ingredient_id", id.toString());

    if (!query.exec()) {
      qWarning() << "Failed to remove association:" << query.lastError().text();
      return false;
    }

    query.prepare("SELECT COUNT(*) FROM recipe_ingredient_associations "
                  "WHERE recipe_ingredient_id = :ingredient_id");
    query.bindValue(":ingredient_id", id.toString());

    if (query.exec() && query.next()) {
      if (query.value(0).toInt() == 0) {
        deleteRecipeIngredient(id);
      }
    }
  }

  return true;
}

bool SqliteDbManager::updateInstructionList(const QRecipe &recipe) {

  QSqlQuery query;

  query.prepare(
      "DELETE * FROM recipe_instructions WHERE recipe_id = :recipe_id");
  query.bindValue(":recipe_id", recipe.getId().toString());

  if (!query.exec()) {
    qWarning() << "Failed to delete old instructions"
               << query.lastError().text();
    return false;
  }

  QStringList instructions = recipe.getInstructions();
  for (int i = 0; i < instructions.size(); ++i) {
    query.prepare("INSERT INTO recipe_instructions "
                  "(recipe_id, instruction, step_order) "
                  "VALUES (:recipe_id, :instruction, :step_order)");
    query.bindValue(":recipe_id", recipe.getId().toString());
    query.bindValue(":instruction", instructions[i]);
    query.bindValue(":step_order", i);

    if (!query.exec()) {
      qWarning() << "Failed to insert instruction:" << query.lastError().text();
      return false;
    }
  }

  return true;
}

bool SqliteDbManager::updateEquipmentList(const QRecipe &recipe) {

  QSqlQuery query;

  query.prepare("DELETE * FROM recipe_equipment WHERE recipe_id = :recipe_id");
  query.bindValue(":recipe_id", recipe.getId().toString());

  if (!query.exec()) {
    qWarning() << "Failed to delete old equipment" << query.lastError().text();
    return false;
  }

  QStringList equipment = recipe.getEquipment();
  for (int i = 0; i < equipment.size(); i++) {
    query.prepare("INSERT INTO recipe_equipment (recipe_id, equipment) VALUES "
                  "(:recipe_id, :equipment)");
    query.bindValue(":recipe_id", recipe.getId().toString());
    query.bindValue(":equipment", equipment[i]);

    if (!query.exec()) {
      qWarning() << "Failed to insert equipment:" << query.lastError().text();
      return false;
    }
  }

  return true;
}

QRecipe *SqliteDbManager::readRecipe(const QUuid &id) {

  quint32 prepTime;
  QString name, description, notes;
  QStringList instructions, equipment;
  QList<QRecipeIngredient *> ingredients;
  QProfile *creator;

  QSqlQuery query;

  query.prepare("SELECT * FROM ingredients WHERE id = :id");
  query.bindValue(":id", id.toString());

  if (!query.exec()) {
    qWarning() << "Failed to read base ingredient from recipe:"
               << query.lastError().text();
    return nullptr;
  }

  if (!query.next()) {
    qWarning() << "No recipe found with ID:" << id.toString();
    return nullptr;
  }

  name = query.value("name").toString();
  description = query.value("description").toString();
  creator = readProfile(QUuid(query.value("creator_id").toString()));

  query.prepare("SELECT * FROM recipes WHERE id = :id");
  query.bindValue(":id", id.toString());

  if (!query.exec()) {
    qWarning() << "Failed to read recipe:" << query.lastError().text();
    return nullptr;
  }

  notes = query.value("notes").toString();
  prepTime = query.value("prep_time").toUInt();

  query.prepare("SELECT instruction FROM recipe_instructions "
                "WHERE recipe_id = :recipe_id ORDER BY step_order");
  query.bindValue(":recipe_id", id.toString());

  if (query.exec()) {
    while (query.next()) {
      instructions.append(query.value("instruction").toString());
    }
  } else {
    qWarning() << "Failed to load instructions:" << query.lastError().text();
  }

  query.prepare("SELECT equipment FROM recipe_equipment "
                "WHERE recipe_id = :recipe_id");
  query.bindValue(":recipe_id", id.toString());

  if (query.exec()) {
    while (query.next()) {
      equipment.append(query.value("equipment").toString());
    }
  } else {
    qWarning() << "Failed to load equipment:" << query.lastError().text();
  }

  query.prepare(
      "SELECT recipe_ingredient_id FROM recipe_ingredient_associations "
      "WHERE recipe_id = :recipe_id");
  query.bindValue(":recipe_id", id.toString());

  if (query.exec()) {
    while (query.next()) {
      QUuid riId = QUuid(query.value("recipe_ingredient_id").toString());
      QRecipeIngredient *ri = readRecipeIngredient(riId);
      if (ri) {
        ingredients.append(ri);
      } else {
        qWarning() << "Failed to load recipe ingredient:" << riId.toString();
      }
    }
  } else {
    qWarning() << "Failed to load recipe ingredients:"
               << query.lastError().text();
  }

  return m_recipeFactory->loadRecipe(id, creator, name, description, prepTime,
                                     ingredients, instructions, equipment,
                                     notes);
}

bool SqliteDbManager::readAllRecipes(QList<QRecipe *> &emptyRecipeList) {
  emptyRecipeList.clear();

  QSqlQuery query("SELECT id FROM recipes");
  if (!query.exec()) {
    qWarning() << "Failed to read recipe IDs:" << query.lastError().text();
    return false;
  }

  while (query.next()) {
    QUuid id = QUuid::fromString(query.value("id").toString());
    QRecipe *recipe = readRecipe(id);
    if (recipe) {
      emptyRecipeList.append(recipe);
    } else {
      qWarning() << "Failed to load recipe with ID:" << id.toString();
    }
  }

  return true;
  return true;
}

bool SqliteDbManager::deleteRecipe(const QUuid &id) {

  QSqlQuery query;

  query.prepare("DELETE FROM recipes WHERE id = :id");
  query.bindValue(":id", id.toString());

  if (!query.exec()) {
    qWarning() << "Failed to delete recipe:" << query.lastError().text();
    return false;
  }

  if (query.numRowsAffected() == 0) {
    qWarning() << "No recipe found to delete with ID:" << id.toString();
    return false;
  }

  return true;
}

bool SqliteDbManager::readAllObjects(ObjectType type,
                                     QList<QObject *> &objects) {
  objects.clear();

  switch (type) {
  case ProfileType:
    return readAllObjectsImpl<QProfile>(objects);
  case IngredientType:
    return readAllObjectsImpl<QIngredient>(objects);
  case RecipeIngredientType:
    return readAllObjectsImpl<QRecipeIngredient>(objects);
  case RecipeType:
    return readAllObjectsImpl<QRecipe>(objects);
  default:
    qWarning() << "Unknown object type requested:" << type;
    return false;
  }
}
