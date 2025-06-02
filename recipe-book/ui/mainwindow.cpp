#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "ingredient_carousel_form.h"

#include <QMessageBox>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  setupMenu();
  setupFactories();

  // Somewhere here you need to have a way of initializing the caches with data
  // from the database
  // initializeCaches();

  // Add to layout
  IngredientCarouselForm *form = new IngredientCarouselForm(this);
  connect(form, &CarouselForm::formCompleted, ingredientFactory,
          &IngredientFactory::ingredientFormSubmitted);

  setCentralWidget(form);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::setupFactories() {
  // Setup the ingredient factory and connect its creation signal to the
  // ingredient cache
  ingredientFactory = new IngredientFactory(this);
  connect(ingredientFactory, &IngredientFactory::createdNewIngredient,
          [this](QtIngredientWrapper *newIngredient) {
            newIngredient->setParent(this);
            this->ingredientCache.append(newIngredient);
            qDebug() << "The current ingredient cache is "
                     << this->ingredientCache;
          });
}

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
