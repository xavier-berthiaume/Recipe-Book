#include "data/db/sqlitedbhandler.h"
#include "ui/mainwindow.h"

#include "models.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QVariantMap>

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

void testSavingToDatabase(ProfileFactory &profileFactory,
                          IngredientFactory &ingredientFactory,
                          RecipeIngredientFactory &recipeIngredientFactory,
                          RecipeFactory &recipeFactory,
                          SqliteDbHandler &database) {

  QVariantMap profileData = {{"username", "xavier"}};
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
