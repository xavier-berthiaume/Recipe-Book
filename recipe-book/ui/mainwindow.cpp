#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QLineEdit>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), m_selectedUser(nullptr) {
  ui->setupUi(this);

  m_viewSelector = findChild<QTabWidget *>("viewNavigator");
  m_profileView = findChild<ProfileView *>("profileView");

  connect(m_profileView, &ProfileView::createObjectRequested, this,
          &MainWindow::createObjectRequested);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::handleObjectCreated(ObjectTypes type, Storable *object) {}

void MainWindow::handleObjectLoaded(ObjectTypes type, Storable *object) {
  QStatusBar *status = findChild<QStatusBar *>("statusbar");

  switch (type) {
  case PROFILEOBJECT:
    qDebug() << "Profile loaded and captured by ui";
    status->showMessage(
        QString("Profile %1 loaded")
            .arg(qobject_cast<QProfile *>(object)->getUsername()));
    break;
  case INGREDIENTOBJECT:
    qDebug() << "Ingredient loaded and captured by ui";
    break;
  case RECIPEINGREDIENTOBJECT:
    qDebug() << "Recipe ingredient loaded and captured by ui";
    break;
  case RECIPEOBJECT:
    qDebug() << "Recipe loaded and captured by ui";
    break;
  }
}
