#ifndef SQLITEDBHANDLER_H
#define SQLITEDBHANDLER_H

#include "abstractdbhandler.h"

#include <QtSql/QSqlDatabase>

class SqliteDbHandler : public AbstractDbHandler {
  Q_OBJECT

  // Saves objects to database
  class SqliteSaver : public DatabaseVisitor {
    SqliteDbHandler *m_handler;

  public:
    explicit SqliteSaver(SqliteDbHandler *handler, QObject *parent = nullptr);
    ~SqliteSaver();

    void visit(QProfile *) override;
    void visit(QIngredient *) override;
    void visit(QRecipeIngredient *) override;
    void visit(QRecipe *) override;
  };

  // Updates objects in database
  class SqliteUpdater : public DatabaseVisitor {
    SqliteDbHandler *m_handler;

  public:
    explicit SqliteUpdater(SqliteDbHandler *handler, QObject *parent = nullptr);
    ~SqliteUpdater();

    void visit(QProfile *) override;
    void visit(QIngredient *) override;
    void visit(QRecipeIngredient *) override;
    void visit(QRecipe *) override;
  };

  // Deletes objects in database
  class SqliteDeleter : public DatabaseVisitor {
    SqliteDbHandler *m_handler;

  public:
    explicit SqliteDeleter(SqliteDbHandler *handler, QObject *parent = nullptr);
    ~SqliteDeleter();

    void visit(QProfile *) override;
    void visit(QIngredient *) override;
    void visit(QRecipeIngredient *) override;
    void visit(QRecipe *) override;
  };

  bool createTables();
  bool openDatabase();
  void closeDatabase();

  QVariantMap readProfile(const QUuid &id);
  QVariantMap readIngredient(const QUuid &id);
  QVariantMap readRecipeIngredient(const QUuid &id);
  QVariantMap readRecipe(const QUuid &id);

  QList<QVariantMap> readProfilesRange(int offset, int count);
  QList<QVariantMap> readIngredientsRange(int offset, int count);
  QList<QVariantMap> readRecipeIngredientsRange(int offset, int count);
  QList<QVariantMap> readRecipesRange(int offset, int count);

  SqliteSaver *m_saver;
  SqliteUpdater *m_updater;
  SqliteDeleter *m_deleter;

  QSqlDatabase m_db;

protected:
  bool beginTransaction() override;
  bool rollbackTransaction() override;
  bool commitTransaction() override;

public:
  explicit SqliteDbHandler(const QString &path, QObject *parent = nullptr);
  ~SqliteDbHandler();

  void saveObject(Storable *toSave) override;
  void updateObject(Storable *toUpdate) override;
  QVariantMap readObject(ObjectTypes type, const QUuid &id) override;
  QList<QVariantMap> readObjectRange(ObjectTypes type, int offset,
                                     int count) override;
  QList<QVariantMap> readAllObjects(ObjectTypes type) override;
  void removeObject(Storable *object) override;

  DatabaseVisitor *getSaver() override;
  DatabaseVisitor *getUpdater() override;
  DatabaseVisitor *getDeleter() override;
};

#endif
