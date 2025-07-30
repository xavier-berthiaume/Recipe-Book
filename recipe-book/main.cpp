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
  DataProvider *provider = new DataProvider(cache, database, &a);
  database->setParent(provider);
  cache->setParent(provider);

  FactoryManager *factories = new FactoryManager(&a);

  QObject::connect(provider, &DataProvider::objectLoaded, factories,
                   qOverload<ObjectTypes, const QVariantMap &>(
                       &FactoryManager::onDataLoaded));

  QObject::connect(provider, &DataProvider::objectsLoaded, factories,
                   qOverload<ObjectTypes, const QList<QVariantMap> &>(
                       &FactoryManager::onDataLoaded));

  QObject::connect(factories, &FactoryManager::objectCreated,
                   [database, provider](ObjectTypes type, Storable *object) {
                     database->onObjectCreation(object);
                     provider->objectsChanged(type);
                   });

  QTranslator translator;
  const QStringList uiLanguages = QLocale::system().uiLanguages();
  for (const QString &locale : uiLanguages) {
    const QString baseName = "recipe-book_" + QLocale(locale).name();
    if (translator.load(":/i18n/" + baseName)) {
      a.installTranslator(&translator);
      break;
    }
  }

  MainWindow w;
  w.show();

  return a.exec();
}
