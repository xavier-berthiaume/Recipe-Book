#include "sqlitedbhandler.h"

#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <stdexcept>

SqliteDbHandler::SqliteDbHandler(const QString &path, QObject *parent)
    : AbstractDbHandler(parent),
      m_saver(new SqliteDbHandler::SqliteSaver(this, this)),
      m_updater(new SqliteDbHandler::SqliteUpdater(this, this)),
      m_reader(new SqliteDbHandler::SqliteReader(this, this)),
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

Storable *SqliteDbHandler::readObject(ObjectTypes type, const QUuid &id) {
  return nullptr;
}

QList<Storable *> SqliteDbHandler::readObjectRange(ObjectTypes type, int offset,
                                                   int count) {
  return {};
}

QList<Storable *> SqliteDbHandler::readAllObjects(ObjectTypes type) {
  return {};
}

bool SqliteDbHandler::removeObject(Storable *object) { return true; }

DatabaseVisitor *SqliteDbHandler::getSaver() { return m_saver; }

DatabaseVisitor *SqliteDbHandler::getUpdater() { return m_updater; }

DatabaseVisitor *SqliteDbHandler::getReader() { return m_reader; }

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
      "is_recipe) VALUES (:id, :ingredient_id, :quantity, :unit, :is_recipe)");
  query.bindValue(":id", object->getId().toString());
  query.bindValue(":ingredient_id", object->getIngredientId().toString());
  query.bindValue(":quantity", object->getQuantity());
  query.bindValue(":unit", object->getUnit());
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
  for (const auto &ingredientId : object->getIngredientIds()) {
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

  query.prepare(
      "UPDATE profiles SET username = :username, updated_at = CURRENT_TIMESTAMP"
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
      "UPDATE recipe_ingredients SET ingredient_id = :ingredient_id, quantity "
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
}

SqliteDbHandler::SqliteReader::SqliteReader(SqliteDbHandler *handler,
                                            QObject *parent)
    : DatabaseVisitor(parent), m_handler(handler) {}

SqliteDbHandler::SqliteReader::~SqliteReader() {}

void SqliteDbHandler::SqliteReader::visit(QProfile *object) {}

void SqliteDbHandler::SqliteReader::visit(QIngredient *object) {}

void SqliteDbHandler::SqliteReader::visit(QRecipeIngredient *object) {}

void SqliteDbHandler::SqliteReader::visit(QRecipe *object) {}

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
