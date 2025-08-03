#include "data/cache/memorycache.h"
#include "data/dataprovider.h"
#include "data/db/abstractdbhandler.h"
#include "data/db/sqlitedbhandler.h"
#include "models/factorymanager.h"
#include "objecttypes.h"
#include "ui/mainwindow.h"

#include <QApplication>
#include <QDebug>
#include <QLocale>
#include <QObject>
#include <QTranslator>
#include <QVariantMap>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  AbstractDbHandler *database = new SqliteDbHandler("./test.sqlite");
  MemoryCache *cache = new MemoryCache();
  DataProvider provider = DataProvider(cache, database, &a);
  database->setParent(&provider);
  cache->setParent(&provider);

  FactoryManager factories = FactoryManager(&a);

  MainWindow w;

  QTranslator translator;
  const QStringList uiLanguages = QLocale::system().uiLanguages();
  for (const QString &locale : uiLanguages) {
    const QString baseName = "recipe-book_" + QLocale(locale).name();
    if (translator.load(":/i18n/" + baseName)) {
      a.installTranslator(&translator);
      break;
    }
  }

  QObject::connect(&provider, &DataProvider::objectLoaded, &factories,
                   qOverload<ObjectTypes, const QVariantMap &>(
                       &FactoryManager::onDataLoaded));

  QObject::connect(&provider, &DataProvider::objectsLoaded, &factories,
                   qOverload<ObjectTypes, const QList<QVariantMap> &>(
                       &FactoryManager::onDataLoaded));

  QObject::connect(
      &factories, &FactoryManager::objectCreated,
      [database, &provider, &w](ObjectTypes type, Storable *object) {
        database->onObjectCreation(object);
        w.handleObjectCreated(type, object);
        provider.objectsChanged(type);
      });

  QObject::connect(&factories, &FactoryManager::objectLoaded, &w,
                   &MainWindow::handleObjectLoaded);

  QObject::connect(&w, &MainWindow::requestObject, &provider,
                   &DataProvider::objectRequested);

  QObject::connect(&w, &MainWindow::requestObjects, &provider,
                   &DataProvider::objectsRequested);

  QObject::connect(&w, &MainWindow::createObjectRequested, &factories,
                   &FactoryManager::onFormSubmitted);

  QObject::connect(&w, &MainWindow::updateObjectRequested,
                   [database, &provider](ObjectTypes type, Storable *object) {
                     database->updateObject(object);
                     provider.invalidateObject(type, object->getId());
                   });

  QObject::connect(&w, &MainWindow::deleteObjectRequested,
                   [database, &provider](ObjectTypes type, Storable *object) {
                     qDebug() << "Passing on object deletion request for type"
                              << static_cast<int>(type) << "and id"
                              << object->getId();
                     database->removeObject(object);
                     provider.invalidateObjectType(type);
                   });

  w.launchWindow();

  return a.exec();
}
