#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>

#include "applicationcleanup.h"
#include "datacache.h"
#include "ingredientfactory.h"
#include "profilefactory.h"
#include "recipefactory.h"
#include "recipeingredientfactory.h"
#include "sqlitedbmanager.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  QTranslator translator;
  const QStringList uiLanguages = QLocale::system().uiLanguages();
  for (const QString &locale : uiLanguages) {
    const QString baseName = "recipe-book_" + QLocale(locale).name();
    if (translator.load(":/i18n/" + baseName)) {
      a.installTranslator(&translator);
      break;
    }
  }

  ProfileFactory profileFactory = ProfileFactory();
  IngredientFactory ingredientFactory = IngredientFactory();
  RecipeIngredientFactory recipeIngredientFactory = RecipeIngredientFactory();
  RecipeFactory recipeFactory = RecipeFactory();

  SqliteDbManager dbManager =
      SqliteDbManager("./test.sqlite", &profileFactory, &ingredientFactory,
                      &recipeIngredientFactory, &recipeFactory);
  DataCache cache;

  QList<QObject *> profiles, ingredients, recipes;
  dbManager.readAllObjects(AbstractDbManager::ProfileType, profiles);
  cache.initializeProfileCache(profiles);

  dbManager.readAllObjects(AbstractDbManager::IngredientType, ingredients);
  cache.initializeIngredientCache(ingredients);

  dbManager.readAllObjects(AbstractDbManager::RecipeType, recipes);
  cache.initializeRecipeCache(recipes);

  MainWindow w(&cache);
  w.show();

  ApplicationCleanup cleanup(&dbManager, &cache);
  QObject::connect(&a, &QApplication::aboutToQuit, &cleanup,
                   &ApplicationCleanup::handleShutdown);

  return a.exec();
}
