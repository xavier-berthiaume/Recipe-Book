#include "sqlitedbhandler.h"
#include "abstractdbhandler.h"

#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <qcontainerfwd.h>
#include <qlogging.h>
#include <stdexcept>

SqliteDbHandler::SqliteDbHandler(const QString &path, QObject *parent)
    : AbstractDbHandler(parent),
      m_saver(new SqliteDbHandler::SqliteSaver(this, this)),
      m_updater(new SqliteDbHandler::SqliteUpdater(this, this)),
      m_deleter(new SqliteDbHandler::SqliteDeleter(this, this)) {

  m_db = QSqlDatabase::addDatabase("QSQLITE");
  m_db.setDatabaseName(path);

  if (!openDatabase()) {
    qCritical() << "Failed to open database";
  }

  if (!createTables()) {
    qCritical() << "Failed to create tables";
  }
}

SqliteDbHandler::~SqliteDbHandler() { closeDatabase(); }

bool SqliteDbHandler::beginTransaction() { return m_db.transaction(); }

bool SqliteDbHandler::rollbackTransaction() { return m_db.rollback(); }

bool SqliteDbHandler::commitTransaction() { return m_db.commit(); }

bool SqliteDbHandler::openDatabase() {
  if (!m_db.isOpen()) {
    if (!m_db.open()) {
      qCritical() << "Error opening db:" << m_db.lastError().text();
      qCritical() << "Database path:" << m_db.databaseName();
      return false;
    }
    qDebug() << "Database opened successfully";
  }
  return true;

  return true;
}

void SqliteDbHandler::closeDatabase() {
  if (m_db.isOpen()) {
    m_db.close();
  }
}

bool SqliteDbHandler::createTables() {
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

void SqliteDbHandler::saveObject(Storable *object) {
  if (!object)
    return;

  try {
    if (!beginTransaction()) {
      throw std::runtime_error("Failed to begin transaction");
    }

    object->accept(m_saver);

    if (!commitTransaction()) {
      throw std::runtime_error("Failed to commit transaction");
    }
  } catch (const std::exception &e) {
    rollbackTransaction();
    qWarning() << "Save failed:" << e.what();
    return;
  }
}

void SqliteDbHandler::updateObject(Storable *object) {
  if (!object)
    return;

  try {
    if (!beginTransaction()) {
      throw std::runtime_error("Failed to begin transaction");
    }

    object->accept(m_updater);

    if (!commitTransaction()) {
      throw std::runtime_error("Failed to commit transaction");
    }
  } catch (const std::exception &e) {
    rollbackTransaction();
    qWarning() << "Update failed:" << e.what();
    return;
  }
}

QVariantMap SqliteDbHandler::readObject(ObjectTypes type, const QUuid &id) {
  switch (type) {
  case PROFILEOBJECT:
    return readProfile(id);
  case INGREDIENTOBJECT:
    return readIngredient(id);
  case RECIPEINGREDIENTOBJECT:
    return readRecipeIngredient(id);
  case RECIPEOBJECT:
    return readRecipe(id);
  }

  qWarning() << "Tried reading invalid object type from database";
  return {};
}

QVariantMap SqliteDbHandler::readProfile(const QUuid &id) {
  QSqlQuery query;

  query.prepare("SELECT * FROM profiles WHERE id = :id");
  query.bindValue(":id", id.toString());

  if (!query.exec()) {
    qWarning() << "Failed to read profile with id:" << id.toString() << "-"
               << query.lastError().text();
    return {};
  }

  if (!query.next()) {
    qDebug() << "No profile found with ID:" << id.toString();
    return {};
  }

  return {{"id", id}, {"username", query.value("username").toString()}};
}

QVariantMap SqliteDbHandler::readIngredient(const QUuid &id) {
  QSqlQuery query;

  query.prepare("SELECT * FROM ingredients WHERE id = :id");
  query.bindValue(":id", id.toString());

  if (!query.exec()) {
    qWarning() << "Failed to read ingredient with id:" << id.toString() << "-"
               << query.lastError().text();
    return {};
  }

  if (!query.next()) {
    qWarning() << "No ingredient found with ID:" << id.toString();
    return {};
  }

  QUuid creator_id = QUuid::fromString(query.value("creator_id").toString());
  QString name = query.value("name").toString();
  QString description = query.value("description").toString();

  return {{"id", id},
          {"creatorId", creator_id},
          {"name", name},
          {"description", description}};
}

QVariantMap SqliteDbHandler::readRecipeIngredient(const QUuid &id) {
  QSqlQuery query;

  query.prepare("SELECT * FROM recipe_ingredients WHERE id = :id");
  query.bindValue(":id", id.toString());

  if (!query.exec()) {
    qWarning() << "Failed to read recipe ingredient with id:" << id.toString()
               << "-" << query.lastError().text();
    return {};
  }

  if (!query.next()) {
    qWarning() << "No recipe ingredient found with ID:" << id.toString();
    return {};
  }

  Units unit = QRecipeIngredient::stringToUnits(query.value("unit").toString());

  return {{"id", id},
          {"ingredientId", query.value("ingredient_id").toUuid()},
          {"unit", unit},
          {"quantity", query.value("quantity").toDouble()},
          {"isRecipe", query.value("is_recipe").toBool()}};
}

QVariantMap SqliteDbHandler::readRecipe(const QUuid &id) {
  QVariantMap data;

  // Read the ingredient portion of the recipe
  data = readIngredient(id);

  QSqlQuery query;
  query.prepare("SELECT * FROM recipes WHERE id = :id");
  query.bindValue(":id", id.toString());

  if (!query.exec()) {
    qWarning() << "Failed to read recipe:" << query.lastError().text();
    return {};
  }

  query.next();
  data["notes"] = query.value("notes").toString();
  data["prepTime"] = query.value("prep_time").toUInt();

  QStringList instructions, equipment;
  query.prepare("SELECT instruction FROM recipe_instructions "
                "WHERE recipe_id = :recipe_id ORDER BY step_order");
  query.bindValue(":recipe_id", id.toString());

  if (query.exec()) {
    while (query.next()) {
      instructions.append(query.value("instruction").toString());
    }
  } else {
    qWarning() << "Failed to load instructions:" << query.lastError().text();
    return {};
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
    return {};
  }

  data["instructions"] = instructions;
  data["equipment"] = equipment;

  QVariantList riIds;
  query.prepare(
      "SELECT recipe_ingredient_id FROM recipe_ingredient_associations "
      "WHERE recipe_id = :recipe_id");
  query.bindValue(":recipe_id", id.toString());

  if (query.exec()) {
    while (query.next()) {
      QUuid riId = query.value("recipe_ingredient_id").toUuid();
      riIds.push_back(riId);
    }
  } else {
    qWarning() << "Failed to load recipe ingredients:"
               << query.lastError().text();
    return {};
  }

  data["recipeIngredientIds"] = riIds;

  return data;
}

QList<QVariantMap> SqliteDbHandler::readObjectRange(ObjectTypes type,
                                                    int offset, int count) {
  switch (type) {
  case PROFILEOBJECT:
    return readProfilesRange(offset, count);
  case INGREDIENTOBJECT:
    return readIngredientsRange(offset, count);
  case RECIPEINGREDIENTOBJECT:
    return readRecipeIngredientsRange(offset, count);
  case RECIPEOBJECT:
    return readRecipesRange(offset, count);
  default:
    qWarning() << "Tried reading invalid object type range from database";
    return {};
  }
}

QList<QVariantMap> SqliteDbHandler::readProfilesRange(int offset, int count) {
  QList<QVariantMap> result;
  QSqlQuery query;

  query.prepare("SELECT * FROM profiles ORDER BY created_at DESC LIMIT :count "
                "OFFSET :offset");
  query.bindValue(":count", count);
  query.bindValue(":offset", offset);

  if (!query.exec()) {
    qWarning() << "Failed to read profiles range:" << query.lastError().text();
    return result;
  }

  while (query.next()) {
    QUuid id = query.value("id").toUuid();
    result.append(
        {{"id", id}, {"username", query.value("username").toString()}});
  }

  return result;
}

QList<QVariantMap> SqliteDbHandler::readIngredientsRange(int offset,
                                                         int count) {
  QList<QVariantMap> result;
  QSqlQuery query;

  query.prepare("SELECT * FROM ingredients ORDER BY created_at DESC LIMIT "
                ":count OFFSET :offset");
  query.bindValue(":count", count);
  query.bindValue(":offset", offset);

  if (!query.exec()) {
    qWarning() << "Failed to read ingredients range:"
               << query.lastError().text();
    return result;
  }

  while (query.next()) {
    QUuid id = query.value("id").toUuid();
    QUuid creatorId = query.value("creator_id").toUuid();
    QString name = query.value("name").toString();
    QString description = query.value("description").toString();

    result.append({{"id", id},
                   {"creatorId", creatorId},
                   {"name", name},
                   {"description", description}});
  }

  return result;
}

QList<QVariantMap> SqliteDbHandler::readRecipeIngredientsRange(int offset,
                                                               int count) {
  QList<QVariantMap> result;
  QSqlQuery query;

  query.prepare("SELECT * FROM recipe_ingredients ORDER BY created_at DESC "
                "LIMIT :count OFFSET :offset");
  query.bindValue(":count", count);
  query.bindValue(":offset", offset);

  if (!query.exec()) {
    qWarning() << "Failed to read recipe ingredients range:"
               << query.lastError().text();
    return result;
  }

  while (query.next()) {
    QUuid id = query.value("id").toUuid();
    QUuid ingredientId = query.value("ingredient_id").toUuid();

    result.append({{"id", id},
                   {"ingredient_id", ingredientId},
                   {"quantity", query.value("quantity").toDouble()},
                   {"unit", query.value("unit").toString()}});
  }

  return result;
}

QList<QVariantMap> SqliteDbHandler::readRecipesRange(int offset, int count) {
  QList<QVariantMap> result;
  QSqlQuery query;

  // First get the recipe IDs in the requested range
  query.prepare("SELECT id FROM recipes ORDER BY created_at DESC LIMIT :count "
                "OFFSET :offset");
  query.bindValue(":count", count);
  query.bindValue(":offset", offset);

  if (!query.exec()) {
    qWarning() << "Failed to read recipe IDs range:"
               << query.lastError().text();
    return result;
  }

  // Collect all recipe IDs
  QList<QUuid> recipeIds;
  while (query.next()) {
    recipeIds.append(QUuid::fromString(query.value("id").toString()));
  }

  // Now read each recipe individually
  for (const QUuid &id : recipeIds) {
    QVariantMap recipe = readRecipe(id);
    if (!recipe.isEmpty()) {
      result.append(recipe);
    }
  }

  return result;
}

QList<QVariantMap> SqliteDbHandler::readAllObjects(ObjectTypes type) {
  return {};
}

bool SqliteDbHandler::removeObject(Storable *object) { return true; }

DatabaseVisitor *SqliteDbHandler::getSaver() { return m_saver; }

DatabaseVisitor *SqliteDbHandler::getUpdater() { return m_updater; }

DatabaseVisitor *SqliteDbHandler::getDeleter() { return m_deleter; }

SqliteDbHandler::SqliteSaver::SqliteSaver(SqliteDbHandler *handler,
                                          QObject *parent)
    : DatabaseVisitor(parent), m_handler(handler) {}

SqliteDbHandler::SqliteSaver::~SqliteSaver() {}

void SqliteDbHandler::SqliteSaver::visit(QProfile *object) {
  QSqlQuery query;

  query.prepare("INSERT INTO profiles (id, username) VALUES (:id, :username)");
  query.bindValue(":id", object->getId().toString());
  query.bindValue(":username", object->getUsername());

  if (!query.exec()) {
    qWarning() << "Failed to save profile:" << query.lastError().text();
  } else {
    qDebug() << "Successfully saved profile to database";
  }
}

void SqliteDbHandler::SqliteSaver::visit(QIngredient *object) {
  QSqlQuery query;

  query.prepare(
      "INSERT INTO ingredients (id, name, description, creator_id) VALUES ("
      ":id, :name, :description, :creator_id)");
  query.bindValue(":id", object->getId().toString());
  query.bindValue(":name", object->getName());
  query.bindValue(":description", object->getDescription());
  query.bindValue(":creator_id", object->getCreatorId().toString());

  if (!query.exec()) {
    qWarning() << "Failed to save ingredient" << query.lastError().text();
  } else {
    qDebug() << "Successfully saved ingredient to database";
  }
}

void SqliteDbHandler::SqliteSaver::visit(QRecipeIngredient *object) {
  QSqlQuery query;

  query.prepare(
      "INSERT INTO recipe_ingredients (id, ingredient_id, quantity, unit, "
      "is_recipe) VALUES (:id, :ingredient_id, :quantity, :unit, "
      ":is_recipe)");
  query.bindValue(":id", object->getId().toString());
  query.bindValue(":ingredient_id", object->getIngredientId().toString());
  query.bindValue(":quantity", object->getQuantity());
  query.bindValue(":unit", QRecipeIngredient::unitToString(object->getUnit()));
  query.bindValue(":is_recipe", object->getIsRecipe());

  if (!query.exec()) {
    qWarning() << "Failed to save recipe ingredient"
               << query.lastError().text();
  } else {
    qDebug() << "Successfully saved recipeingredient to database";
  }
}

void SqliteDbHandler::SqliteSaver::visit(QRecipe *object) {
  // Ingredient portion of recipe
  visit(static_cast<QIngredient *>(object));

  // Recipe portion
  QSqlQuery query;

  query.prepare("INSERT INTO recipes (id, prep_time, notes) VALUES (:id, "
                ":prep_time, :notes)");
  query.bindValue(":id", object->getId().toString());
  query.bindValue(":prep_time", object->getPrepTime());
  query.bindValue(":notes", object->getNotes());

  if (!query.exec()) {
    throw std::runtime_error(QString("Failed to save recipe: %1")
                                 .arg(query.lastError().text())
                                 .toStdString());
  }

  // Instructions
  QStringList instructions = object->getInstructions();
  for (int i = 0; i < instructions.size(); ++i) {
    query.prepare("INSERT INTO recipe_instructions "
                  "(recipe_id, instruction, step_order) "
                  "VALUES (:recipe_id, :instruction, :step_order)");
    query.bindValue(":recipe_id", object->getId().toString());
    query.bindValue(":instruction", instructions[i]);
    query.bindValue(":step_order", i);

    if (!query.exec()) {
      throw std::runtime_error(QString("Failed to save recipe instruction: %1")
                                   .arg(query.lastError().text())
                                   .toStdString());
    }
  }

  // Equipment
  QStringList equipment = object->getEquipment();
  for (const QString &eq : equipment) {
    query.prepare("INSERT INTO recipe_equipment "
                  "(recipe_id, equipment) "
                  "VALUES (:recipe_id, :equipment)");
    query.bindValue(":recipe_id", object->getId().toString());
    query.bindValue(":equipment", eq);

    if (!query.exec()) {
      throw std::runtime_error(QString("Failed to save recipe equipment: %1")
                                   .arg(query.lastError().text())
                                   .toStdString());
    }
  }

  // Recipe Ingredients
  for (const QUuid &ingredientId : object->getIngredientIds()) {
    query.prepare("INSERT INTO recipe_ingredient_associations (recipe_id, "
                  "recipe_ingredient_id) "
                  "VALUES (:recipe_id, :recipe_ingredient_id)");

    query.bindValue(":recipe_id", object->getId().toString());
    query.bindValue(":recipe_ingredient_id", ingredientId.toString());

    if (!query.exec()) {
      throw std::runtime_error(
          QString("Failed to save recipe ingredient association: %1")
              .arg(query.lastError().text())
              .toStdString());
    }
  }

  qDebug() << "Successfully saved recipe to database";
}

SqliteDbHandler::SqliteUpdater::SqliteUpdater(SqliteDbHandler *handler,
                                              QObject *parent)
    : DatabaseVisitor(parent), m_handler(handler) {}

SqliteDbHandler::SqliteUpdater::~SqliteUpdater() {}

void SqliteDbHandler::SqliteUpdater::visit(QProfile *object) {
  QSqlQuery query;

  query.prepare("UPDATE profiles SET username = :username, updated_at = "
                "CURRENT_TIMESTAMP"
                "WHERE id=:id");
  query.bindValue(":username", object->getUsername());
  query.bindValue(":id", object->getId().toString());

  if (!query.exec()) {
    qWarning() << "Failed to update profile";
    throw std::runtime_error(QString("Failed to update profile: %1")
                                 .arg(query.lastError().text())
                                 .toStdString());
  } else {
    qDebug() << "Successfully updated profile in database";
  }

  if (query.numRowsAffected() == 0) {
    qWarning() << "No profile found to update with ID:"
               << object->getId().toString();
  }
}

void SqliteDbHandler::SqliteUpdater::visit(QIngredient *object) {
  QSqlQuery query;

  query.prepare("UPDATE ingredients SET name = :name, description = "
                ":description, creator_id = :creator_id, updated_at = "
                "CURRENT_TIMESTAMP WHERE id = :id");
  query.bindValue(":name", object->getName());
  query.bindValue(":description", object->getDescription());
  query.bindValue(":creator_id", object->getCreatorId().toString());
  query.bindValue(":id", object->getId().toString());

  if (!query.exec()) {
    qWarning() << "Failed to update ingredient";
    throw std::runtime_error(QString("Failed to update ingredient: %1")
                                 .arg(query.lastError().text())
                                 .toStdString());
  } else {
    qDebug() << "Successfully updated ingredient in database";
  }

  if (query.numRowsAffected() == 0) {
    qWarning() << "No object->found to update with ID:"
               << object->getId().toString();
  }
}

void SqliteDbHandler::SqliteUpdater::visit(QRecipeIngredient *object) {
  QSqlQuery query;

  query.prepare(
      "UPDATE recipe_ingredients SET ingredient_id = :ingredient_id, "
      "quantity "
      "= :quantity, unit = :unit, is_recipe = :is_recipe WHERE id = :id");
  query.bindValue(":ingredient_id", object->getIngredientId().toString());
  query.bindValue(":quantity", object->getQuantity());
  query.bindValue(":unit", object->getUnit());
  query.bindValue(":is_recipe", object->getIsRecipe());
  query.bindValue(":id", object->getId().toString());

  if (!query.exec()) {
    qWarning() << "Failed to update recipe ingredient";
    throw std::runtime_error(QString("Failed to update recipe ingredient: %1")
                                 .arg(query.lastError().text())
                                 .toStdString());
  }

  if (query.numRowsAffected() == 0) {
    qWarning() << "No recipe ingredient found to update with ID:"
               << object->getId().toString();
  } else {
    qDebug() << "Successfully updated recipe ingredient in database";
  }
}

void SqliteDbHandler::SqliteUpdater::visit(QRecipe *object) {
  visit(static_cast<QIngredient *>(object));

  QSqlQuery query;

  query.prepare("UPDATE recipes SET prep_time = :prep_time, notes = :notes "
                "WHERE id = :id");
  query.bindValue(":prep_time", object->getPrepTime());
  query.bindValue(":notes", object->getNotes());
  query.bindValue(":id", object->getId());

  if (!query.exec()) {
    qWarning() << "Failed to update recipe";
    throw std::runtime_error(QString("Failed to update recipe: %1")
                                 .arg(query.lastError().text())
                                 .toStdString());
  }

  query.prepare(
      "DELETE * FROM recipe_instructions WHERE recipe_id = :recipe_id");
  query.bindValue(":recipe_id", object->getId().toString());

  if (!query.exec()) {
    qWarning() << "Failed to delete old instructions"
               << query.lastError().text();
    throw std::runtime_error(QString("Failed to update recipe: %1")
                                 .arg(query.lastError().text())
                                 .toStdString());
  }

  QStringList instructions = object->getInstructions();
  for (int i = 0; i < instructions.size(); ++i) {
    query.prepare("INSERT INTO recipe_instructions "
                  "(recipe_id, instruction, step_order) "
                  "VALUES (:recipe_id, :instruction, :step_order)");
    query.bindValue(":recipe_id", object->getId().toString());
    query.bindValue(":instruction", instructions[i]);
    query.bindValue(":step_order", i);

    if (!query.exec()) {
      qWarning() << "Failed to insert instruction:" << query.lastError().text();
      throw std::runtime_error(QString("Failed to update recipe: %1")
                                   .arg(query.lastError().text())
                                   .toStdString());
    }
  }

  query.prepare("DELETE * FROM recipe_equipment WHERE recipe_id = :recipe_id");
  query.bindValue(":recipe_id", object->getId().toString());

  if (!query.exec()) {
    qWarning() << "Failed to delete old equipment" << query.lastError().text();
    throw std::runtime_error(QString("Failed to update recipe: %1")
                                 .arg(query.lastError().text())
                                 .toStdString());
  }

  QStringList equipment = object->getEquipment();
  for (int i = 0; i < equipment.size(); i++) {
    query.prepare("INSERT INTO recipe_equipment (recipe_id, equipment) VALUES "
                  "(:recipe_id, :equipment)");
    query.bindValue(":recipe_id", object->getId().toString());
    query.bindValue(":equipment", equipment[i]);

    if (!query.exec()) {
      qWarning() << "Failed to insert equipment:" << query.lastError().text();
      throw std::runtime_error(QString("Failed to update recipe: %1")
                                   .arg(query.lastError().text())
                                   .toStdString());
    }
  }

  // TODO: Update recipe ingredients associated to the recipe
  // Delete the existing associations and simply re-create new ones
  query.prepare(
      "DELETE * FROM recipe_ingredient_associations WHERE recipe_id = :id");
  query.bindValue(":id", object->getId().toString());

  if (!query.exec()) {
    qWarning()
        << "Failed to remove old recipe to recipe ingredient associations";
    throw std::runtime_error(QString("Failed to update recipe: %1")
                                 .arg(query.lastError().text())
                                 .toStdString());
  }

  for (const QUuid &ingredientId : object->getIngredientIds()) {
    query.prepare("INSERT INTO recipe_ingredient_associations (recipe_id, "
                  "recipe_ingredient_id) "
                  "VALUES (:recipe_id, :recipe_ingredient_id)");

    query.bindValue(":recipe_id", object->getId().toString());
    query.bindValue(":recipe_ingredient_id", ingredientId.toString());

    if (!query.exec()) {
      throw std::runtime_error(
          QString("Failed to update recipe ingredient association: %1")
              .arg(query.lastError().text())
              .toStdString());
    }
  }
}

SqliteDbHandler::SqliteDeleter::SqliteDeleter(SqliteDbHandler *handler,
                                              QObject *parent)
    : DatabaseVisitor(parent), m_handler(handler) {}

SqliteDbHandler::SqliteDeleter::~SqliteDeleter() {}

void SqliteDbHandler::SqliteDeleter::visit(QProfile *object) {
  QSqlQuery query;

  query.prepare("DELETE FROM profiles WHERE id = :id");
  query.bindValue(":id", object->getId().toString());

  if (!query.exec()) {
    qWarning() << "Failed to delete profile:" << query.lastError().text();
    throw std::runtime_error(QString("Failed to delete profile: %1")
                                 .arg(query.lastError().text())
                                 .toStdString());
  }

  if (query.numRowsAffected() == 0) {
    qWarning() << "No profile found to delete with ID:"
               << object->getId().toString();
  }
}

void SqliteDbHandler::SqliteDeleter::visit(QIngredient *object) {
  QSqlQuery query;

  query.prepare("DELETE FROM ingredients WHERE id = :id");
  query.bindValue(":id", object->getId().toString());

  if (!query.exec()) {
    qWarning() << "Failed to delete ingredient:" << query.lastError().text();
    throw std::runtime_error(QString("Failed to delete ingredient: %1")
                                 .arg(query.lastError().text())
                                 .toStdString());
  }

  if (query.numRowsAffected() == 0) {
    qWarning() << "No ingredient found to delete with ID:" << object->getId();
  }
}

void SqliteDbHandler::SqliteDeleter::visit(QRecipeIngredient *object) {
  QSqlQuery query;

  query.prepare("DELETE FROM recipe_ingredients WHERE id = :id");
  query.bindValue(":id", object->getId().toString());

  if (!query.exec()) {
    qWarning() << "Failed to delete recipe ingredient:"
               << query.lastError().text();
    throw std::runtime_error(QString("Failed to delete recipe ingredient: %1")
                                 .arg(query.lastError().text())
                                 .toStdString());
  }

  if (query.numRowsAffected() == 0) {
    qWarning() << "No recipe ingredient found to delete with ID:"
               << object->getId();
  }
}

void SqliteDbHandler::SqliteDeleter::visit(QRecipe *object) {
  QSqlQuery query;

  query.prepare("DELETE FROM recipes WHERE id = :id");
  query.bindValue(":id", object->getId().toString());

  if (!query.exec()) {
    qWarning() << "Failed to delete recipe:" << query.lastError().text();
    throw std::runtime_error(QString("Failed to delete recipe: %1")
                                 .arg(query.lastError().text())
                                 .toStdString());
  }

  if (query.numRowsAffected() == 0) {
    qWarning() << "No recipe found to delete with ID:" << object->getId();
  }
}
