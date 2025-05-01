#include "ui/mainwindow.h"

#include "models/qt_ingredient_wrapper.h"
#include "models/qt_recipe_wrapper.h"
#include "models/qt_user_wrapper.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <qlogging.h>

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
  MainWindow w;
  w.show();

  // Test the creation of a user
  User user = User();
  user.setUsername("Bob");
  QtUserWrapper wuser = QtUserWrapper(user);
  wuser.setPassword("password");

  qDebug() << "Printing user\n"
           << wuser.getId().toByteArray() << "\n"
           << wuser.getUsername() << "\n"
           << wuser.getPasswordHash() << "\n";

  // Test the creation of a recipe
  Recipe recipe = Recipe();
  recipe.setName("This is a test recipe");
  recipe.setDescription("loren ipsum dolor sit amet.");
  recipe.setNote("Feeds 10000");
  QtRecipeWrapper wrecipe = QtRecipeWrapper(recipe);

  qDebug() << "Printing recipe\n"
           << wrecipe.getId().toByteArray() << "\n"
           << wrecipe.getName() << "\n"
           << wrecipe.getDescription() << "\n"
           << wrecipe.getNotes() << "\n";

  // Test the creation of an ingredient
  Ingredient ingredient = Ingredient();
  ingredient.setName("Spicy pepper");
  ingredient.setDescription("A really spicy pepper");
  QtIngredientWrapper wingredient = QtIngredientWrapper(ingredient);

  qDebug() << "Printing ingredient\n"
           << wingredient.getId().toByteArray() << "\n"
           << wingredient.getName() << "\n"
           << wingredient.getDescription() << "\n";

  return a.exec();
}
