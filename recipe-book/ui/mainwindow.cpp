#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QLineEdit>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), m_selectedUser(nullptr) {
  ui->setupUi(this);

  m_status = findChild<QStatusBar *>("statusbar");
  m_viewSelector = findChild<QTabWidget *>("viewNavigator");
  m_profileView = findChild<ProfileView *>("profileView");

  connect(m_profileView, &ProfileView::createObjectRequested, this,
          &MainWindow::createObjectRequested);

  connect(m_profileView, &ProfileView::updateObjectRequested, this,
          &MainWindow::updateObjectRequested);

  connect(m_profileView, &ProfileView::deleteObjectRequested, this,
          &MainWindow::deleteObjectRequested);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::setupInitialState() {
  qDebug() << "Setting up main window initial state";
  m_viewSelector->setCurrentIndex(0);

  emit requestObjects(PROFILEOBJECT, 0, 4);
}

void MainWindow::launchWindow() {
  setupInitialState();

  this->show();
}

void MainWindow::handleObjectCreated(ObjectTypes type, Storable *object) {
  QWidget *currentWidget = m_viewSelector->currentWidget();
  if (!currentWidget) {
    qDebug() << "No current widget selected";
    return;
  }

  AbstractView *currentView = currentWidget->findChild<AbstractView *>();
  if (!currentView) {
    qDebug() << "No AbstractView found in current tab. Children are:";

    for (auto child : currentWidget->children()) {
      qDebug() << " -" << child->metaObject()->className();
    }

    return;
  }

  switch (type) {
  case PROFILEOBJECT:
    qDebug() << "Profile created and captured by ui";
    m_status->showMessage(
        QString("Profile %1 created")
            .arg(qobject_cast<QProfile *>(object)->getUsername()));
    currentView->handleObjectCreated(type, object);
    break;

  case INGREDIENTOBJECT:
    qDebug() << "Ingredient created and captured by ui";
    m_status->showMessage(
        QString("Ingredient %1 created")
            .arg(qobject_cast<QIngredient *>(object)->getName()));
    currentView->handleObjectCreated(type, object);
    break;

  case RECIPEINGREDIENTOBJECT:
    qDebug() << "Recipe ingredient created and captured by ui";
    currentView->handleObjectCreated(type, object);
    break;

  case RECIPEOBJECT:
    qDebug() << "Recipe created and captured by ui";
    m_status->showMessage(QString("Recipe %1 created")
                              .arg(qobject_cast<QRecipe *>(object)->getName()));
    currentView->handleObjectCreated(type, object);
    break;
  }
}

void MainWindow::handleObjectLoaded(ObjectTypes type, Storable *object) {
  QWidget *currentWidget = m_viewSelector->currentWidget();
  if (!currentWidget) {
    qDebug() << "No current widget selected";
    return;
  }

  AbstractView *currentView = currentWidget->findChild<AbstractView *>();
  if (!currentView) {
    qDebug() << "No AbstractView found in current tab. Children are:";

    for (auto child : currentWidget->children()) {
      qDebug() << " -" << child->metaObject()->className();
    }

    return;
  }

  switch (type) {
  case PROFILEOBJECT:
    qDebug() << "Profile loaded and captured by ui";
    m_status->showMessage(
        QString("Profile %1 loaded")
            .arg(qobject_cast<QProfile *>(object)->getUsername()));
    currentView->handleObjectLoaded(type, object);
    break;

  case INGREDIENTOBJECT:
    qDebug() << "Ingredient loaded and captured by ui";
    currentView->handleObjectLoaded(type, object);
    break;

  case RECIPEINGREDIENTOBJECT:
    qDebug() << "Recipe ingredient loaded and captured by ui";
    currentView->handleObjectLoaded(type, object);
    break;

  case RECIPEOBJECT:
    qDebug() << "Recipe loaded and captured by ui";
    currentView->handleObjectLoaded(type, object);

    break;
  }
}
