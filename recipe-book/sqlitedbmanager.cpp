#include "sqlitedbmanager.h"

#include <QDebug>
#include <QtSql/QSqlError>

SqliteDbManager::SqliteDbManager(const QString &path, QObject *parent)
    : AbstractDbManager(parent) {

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

  if (className == "Profile") {
    // Try casting to its matching class
    QProfile *profile = return saveProfile();
  } else if (className == "Ingredient") {
    return saveIngredient();
  } else if (className == "RecipeIngredient") {
    return saveRecipeIngredient();
  } else if (className == "Recipe") {
    return saveRecipe();
  } else {
    qWarning() << "Invalid class name tried to be saved to database";
    return false;
  }

  return true;
}

bool SqliteDbManager::updateObject(QObject *object) { return true; }

QObject *SqliteDbManager::readObject(const QString &objectType,
                                     const QUuid &id) {

  return new QObject(); // Delete later
}

bool SqliteDbManager::deleteObject(const QString &objectType, const QUuid &id) {

  return new QObject();
}

bool SqliteDbManager::beginTransaction() { return true; }

bool SqliteDbManager::commitTransaction() { return true; }

bool SqliteDbManager::rollbackTransaction() { return true; }

bool SqliteDbManager::openDatabase() {

  if (!m_database.isOpen()) {
    qCritical() << "Database error:" << m_database.lastError().text();
    return false;
  }

  return true;
}

void SqliteDbManager::closeDatabase() {

  if (m_database.isOpen()) {
    m_database.close();
  }
}

bool SqliteDbManager::createTables() { return true; }

bool SqliteDbManager::saveProfile(const QProfile &profile) { return true; }

bool SqliteDbManager::updateProfile(const QProfile &profile) { return true; }

QProfile *SqliteDbManager::readProfile(const QUuid &id) {

  return new QProfile();
}

bool SqliteDbManager::deleteProfile(const QUuid &id) { return true; }

bool SqliteDbManager::saveIngredient(const QIngredient &ingredient) {

  return true;
}

bool SqliteDbManager::updateIngredient(const QIngredient &ingredient) {

  return true;
}

QIngredient *SqliteDbManager::readIngredient(const QUuid &id) {

  return new QIngredient();
}

bool SqliteDbManager::deleteIngredient(const QUuid &id) { return true; }

bool saveRecipeIngredient(const QRecipeIngredient &ingredient) { return true; }

bool SqliteDbManager::updateRecipeIngredient(
    const QRecipeIngredient &ingredient) {

  return true;
}

QRecipeIngredient *SqliteDbManager::readRecipeIngredient(const QUuid &id) {

  return new QRecipeIngredient();
}

bool SqliteDbManager::deleteRecipeIngredient(const QUuid &id) { return true; }

bool SqliteDbManager::saveRecipe(const QRecipe &recipe) { return true; }
bool SqliteDbManager::updateRecipe(const QRecipe &recipe) { return true; }

QRecipe *SqliteDbManager::readRecipe(const QUuid &id) { return new QRecipe(); }

bool SqliteDbManager::deleteRecipe(const QUuid &id) { return true; }
