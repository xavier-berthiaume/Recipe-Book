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

  // Reads objects from database
  class SqliteReader : public DatabaseVisitor {
    SqliteDbHandler *m_handler;

  public:
    explicit SqliteReader(SqliteDbHandler *handler, QObject *parent = nullptr);
    ~SqliteReader();

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

  SqliteSaver *m_saver;
  SqliteUpdater *m_updater;
  SqliteReader *m_reader;
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
  Storable *readObject(ObjectTypes type, const QUuid &id) override;
  QList<Storable *> readObjectRange(ObjectTypes type, int offset,
                                    int count) override;
  QList<Storable *> readAllObjects(ObjectTypes type) override;
  bool removeObject(Storable *object) override;

  DatabaseVisitor *getSaver() override;
  DatabaseVisitor *getUpdater() override;
  DatabaseVisitor *getReader() override;
  DatabaseVisitor *getDeleter() override;
};

#endif
