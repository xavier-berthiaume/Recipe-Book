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

  bool saveProfile(const QProfile &profile);
  bool updateProfile(const QProfile &profile);
  QProfile *readProfile(const QUuid &id);
  bool deleteProfile(const QUuid &id);

  bool saveIngredient(const QIngredient &ingredient);
  bool updateIngredient(const QIngredient &ingredient);
  QIngredient *readIngredient(const QUuid &id);
  bool deleteIngredient(const QUuid &id);

  bool saveRecipeIngredient(const QRecipeIngredient &ingredient);
  bool updateRecipeIngredient(const QRecipeIngredient &ingredient);
  QRecipeIngredient *readRecipeIngredient(const QUuid &id);
  bool deleteRecipeIngredient(const QUuid &id);

  bool saveRecipe(const QRecipe &recipe);
  bool updateRecipe(const QRecipe &recipe);
  QRecipe *readRecipe(const QUuid &id);
  bool deleteRecipe(const QUuid &id);

  QSqlDatabase m_database;

public:
  explicit SqliteDbManager(const QString &path, QObject *parent = nullptr);

  // Marked as override to make sure it runs on parent destructor call
  ~SqliteDbManager() override;

  bool saveObject(QObject *object) override;
  bool updateObject(QObject *object) override;
  QObject *readObject(const QString &objectType, const QUuid &id) override;
  bool deleteObject(const QString &objectType, const QUuid &id) override;

  bool beginTransaction() override;
  bool commitTransaction() override;
  bool rollbackTransaction() override;

  bool openDatabase();
  void closeDatabase();
  bool createTables();
};

#endif
