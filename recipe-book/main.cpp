#include "data/db/abstractdbhandler.h"
#include "data/db/sqlitedbhandler.h"
#include "ui/mainwindow.h"

#include "models.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QVariantMap>

void testSavingToDatabase(const QString &uniqueUsername,
                          ProfileFactory &profileFactory,
                          IngredientFactory &ingredientFactory,
                          RecipeIngredientFactory &recipeIngredientFactory,
                          RecipeFactory &recipeFactory,
                          SqliteDbHandler &database) {
  QVariantMap profileData = {{"username", uniqueUsername}};
  QProfile *profile = profileFactory.createObject(profileData);

  QVariantMap ingredientData = {{"creatorId", profile->getId()},
                                {"name", "Carrot"},
                                {"description", "Orange and yummy"}};
  QIngredient *ingredient = ingredientFactory.createObject(ingredientData);

  QVariantMap recipeIngredientData = {{"ingredientId", ingredient->getId()},
                                      {"unit", Units::CUPS},
                                      {"quantity", 1.5},
                                      {"isRecipe", false}};
  QRecipeIngredient *ri =
      recipeIngredientFactory.createObject(recipeIngredientData);

  QVariantList riIds = {ri->getId()};
  QVariantMap recipeData = {
      {"creatorId", profile->getId()},
      {"name", "Carrot Soup"},
      {"description", "This is an essential recipe to learn"},
      {"notes", ""},
      {"prepTime", 40},
      {"recipeIngredientIds", riIds},
      {"instructions",
       QStringList::fromList({"Cut carrots", "Boil carrots", "Season soup"})},
      {"equipment",
       QStringList::fromList({"Kitchen knife", "Cutting board", "Stock pot"})}};
  QRecipe *recipe = recipeFactory.createObject(recipeData);

  database.saveObject(profile);
  database.saveObject(ingredient);
  database.saveObject(ri);
  database.saveObject(recipe);
}

void testReadingFromDatabase(SqliteDbHandler &database) {
  qDebug() << "Reading profile from database"
           << database.readObject(
                  PROFILEOBJECT,
                  QUuid::fromString("{1b2a8739-9d68-4600-80fd-cadcb6afce83}"));

  qDebug() << "Reading ingredient from database"
           << database.readObject(
                  INGREDIENTOBJECT,
                  QUuid::fromString("{8c1d45b1-aea5-4457-88dc-83c264a7a9d9}"));

  qDebug() << "Reading recipe ingredient from database"
           << database.readObject(
                  RECIPEINGREDIENTOBJECT,
                  QUuid::fromString("{f3a9b809-c4b9-4d21-8331-bb6ec6bfcca2}"));

  qDebug() << "Reading recipe from database"
           << database.readObject(
                  RECIPEOBJECT,
                  QUuid::fromString("{01615daa-27ec-4e81-9d8a-a11a25b68ea8}"));
}

void testBatchReadingFromDatabase(SqliteDbHandler &database) {
  qDebug() << "Reading 10 profiles from database"
           << database.readObjectRange(PROFILEOBJECT, 0, 10);

  qDebug() << "Reading 15 ingredients from database"
           << database.readObjectRange(INGREDIENTOBJECT, 0, 15);

  qDebug() << "Reading 4 recipe ingredients from database"
           << database.readObjectRange(RECIPEINGREDIENTOBJECT, 0, 4);

  qDebug() << "Reading 2 recipes from database"
           << database.readObjectRange(RECIPEOBJECT, 0, 2);
}

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  ProfileFactory profileFactory;
  IngredientFactory ingredientFactory;
  RecipeIngredientFactory recipeIngredientFactory;
  RecipeFactory recipeFactory;

  SqliteDbHandler database = SqliteDbHandler("./test.sqlite");

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
