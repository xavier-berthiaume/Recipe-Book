#include "sqlitedbhandler.h"

#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>

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
    throw;
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
    throw;
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

void SqliteDbHandler::SqliteSaver::visit(QProfile *object) {}

void SqliteDbHandler::SqliteSaver::visit(QIngredient *object) {}

void SqliteDbHandler::SqliteSaver::visit(QRecipeIngredient *object) {}

void SqliteDbHandler::SqliteSaver::visit(QRecipe *object) {}

SqliteDbHandler::SqliteUpdater::SqliteUpdater(SqliteDbHandler *handler,
                                              QObject *parent)
    : DatabaseVisitor(parent), m_handler(handler) {}

SqliteDbHandler::SqliteUpdater::~SqliteUpdater() {}

void SqliteDbHandler::SqliteUpdater::visit(QProfile *object) {}

void SqliteDbHandler::SqliteUpdater::visit(QIngredient *object) {}

void SqliteDbHandler::SqliteUpdater::visit(QRecipeIngredient *object) {}

void SqliteDbHandler::SqliteUpdater::visit(QRecipe *object) {}

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

void SqliteDbHandler::SqliteDeleter::visit(QProfile *object) {}

void SqliteDbHandler::SqliteDeleter::visit(QIngredient *object) {}

void SqliteDbHandler::SqliteDeleter::visit(QRecipeIngredient *object) {}

void SqliteDbHandler::SqliteDeleter::visit(QRecipe *object) {}
