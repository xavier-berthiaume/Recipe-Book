#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "ingredient_display_box.h"
#include "recipe_display_box.h"

#include "../models/qt_ingredient_wrapper.h"
#include "../models/qt_recipe_wrapper.h"

#include <QMessageBox>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  setupMenu();

  // Create sample data
  auto* ingredientWrapper = new QtIngredientWrapper(
      "Flour", "All-purpose wheat flour", this);

  auto* recipeWrapper = new QtRecipeWrapper(
      Recipe("Pancakes", "Delicious breakfast recipe"), this);
  recipeWrapper->addInstruction("Mix dry ingredients");
  recipeWrapper->addInstruction("Add wet ingredients");
  recipeWrapper->addEquipment("Mixing bowl");
  recipeWrapper->addEquipment("Whisk");

  // Create display boxes
  auto* ingredientBox = new IngredientDisplayBox(this);
  ingredientBox->setWrapper(ingredientWrapper);
  ingredientBox->setFixedSize(300, 150);

  auto* recipeBox = new RecipeDisplayBox(this);
  recipeBox->setWrapper(recipeWrapper);
  recipeBox->setFixedSize(300, 200);

  // Add to layout
  QWidget* centralWidget = new QWidget(this);
  QVBoxLayout* layout = new QVBoxLayout(centralWidget);
  layout->addWidget(ingredientBox);
  layout->addWidget(recipeBox);
  setCentralWidget(centralWidget);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::setupMenu() {
  QAction *help = findChild<QAction *>("actionHelp");
  connect(help, &QAction::triggered, this,
          [this]() { showInfoModal(tr("Recipe Book Help Menu"), ""); });

  QAction *navigation = findChild<QAction *>("actionNavigation");
  connect(navigation, &QAction::triggered, this,
          [this]() { showInfoModal(tr("Recipe Book Navigation"), ""); });

  QAction *license = findChild<QAction *>("actionLicense");
  connect(license, &QAction::triggered, this,
          [this]() { showInfoModal(tr("License"), ""); });

  QAction *contribute = findChild<QAction *>("actionContribute");
  connect(contribute, &QAction::triggered, this, [this]() {
    showInfoModal(
        tr("Contribute"),
        tr("To contribute to this project, simply clone the project and add a "
           "pull request. Contributions are welcome in any way!"));
  });

  QAction *contact = findChild<QAction *>("actionContact");
  connect(contact, &QAction::triggered, this, [this]() {
    showInfoModal(
        tr("Contact the Developper"),
        tr("You can contact me at xavier.berthiaume@gmail.com; I always try to "
           "answer when I can, but it can certainly take a bit of time, so "
           "please don't worry if I don't answer immediately!"));
  });
}

void MainWindow::showInfoModal(const QString &title, const QString &message) {
  QMessageBox::information(this, title, message);
}
