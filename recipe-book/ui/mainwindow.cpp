#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QLineEdit>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), m_selectedUserId() {
  ui->setupUi(this);

  m_status = findChild<QStatusBar *>("statusbar");
  m_viewSelector = findChild<QTabWidget *>("viewNavigator");
  m_profileView = findChild<ProfileView *>("profileView");
  m_ingredientView = findChild<IngredientView *>("ingredientView");
  m_recipeView = findChild<RecipeView *>("recipeView");

  connect(m_profileView, &ProfileView::createObjectRequested, this,
          &MainWindow::createObjectRequested);

  connect(m_profileView, &ProfileView::updateObjectRequested, this,
          &MainWindow::updateObjectRequested);

  // We remove the selected profile if it's the one being deleted
  connect(m_profileView, &ProfileView::deleteObjectRequested,
          [this](ObjectTypes type, Storable *object) {
            if (m_selectedUserId.isNull() &&
                m_selectedUserId == object->getId())
              m_selectedUserId = QUuid();

            emit deleteObjectRequested(type, object);
          });

  connect(m_profileView, &ProfileView::selectedProfileChanged, this,
          &MainWindow::handleProfileSelected);

  connect(m_profileView, &ProfileView::requestObjectsCount, this,
          &MainWindow::requestObjectsCounted);

  connect(m_profileView, &ProfileView::requestObjects, this,
          &MainWindow::requestObjects);

  // We tag on the selected user to the data
  connect(
      m_ingredientView, &IngredientView::createObjectRequested,
      [this](ObjectTypes type, QVariantMap &data) {
        if (!m_selectedUserId.isNull()) {
          QUuid userId = this->m_selectedUserId;
          qDebug()
              << QString(
                     "User %1 is logged in, creating ingredient using their ID")
                     .arg(userId.toString());
          data["creatorId"] = userId;
        } else {
          qWarning() << "No user currently selected, using an empty QUuid "
                        "to create ingredient";
          data["creatorId"] = QUuid().toString();
        }

        emit createObjectRequested(type, data);
      });

  connect(m_ingredientView, &IngredientView::updateObjectRequested, this,
          &MainWindow::updateObjectRequested);

  connect(m_ingredientView, &IngredientView::deleteObjectRequested, this,
          &MainWindow::deleteObjectRequested);

  connect(m_ingredientView, &IngredientView::requestObjectsCount, this,
          &MainWindow::requestObjectsCounted);

  connect(m_ingredientView, &IngredientView::requestObjects, this,
          &MainWindow::requestObjects);

  connect(m_ingredientView, &IngredientView::requestObject, this,
          &MainWindow::requestObject);

  connect(m_recipeView, &RecipeView::createObjectRequested,
          [this](ObjectTypes type, QVariantMap &data) {
            if (!m_selectedUserId.isNull()) {
              QUuid userId = this->m_selectedUserId;
              qDebug()
                  << QString(
                         "User %1 is logged in, creating recipe using their ID")
                         .arg(userId.toString());
              data["creatorId"] = userId;
            } else {
              qWarning() << "No user currently selected, using an empty QUuid "
                            "to create recipe";
              data["creatorId"] = QUuid().toString();
            }
          });

  connect(m_recipeView, &RecipeView::updateObjectRequested, this,
          &MainWindow::updateObjectRequested);

  connect(m_recipeView, &RecipeView::deleteObjectRequested, this,
          &MainWindow::deleteObjectRequested);

  connect(m_recipeView, &RecipeView::requestObjectsCount, this,
          &MainWindow::requestObjectsCounted);

  connect(m_recipeView, &RecipeView::requestObjects, this,
          &MainWindow::requestObjects);

  connect(m_recipeView, &RecipeView::requestObject, this,
          &MainWindow::requestObject);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::setupInitialState() {
  qDebug() << "Setting up main window initial state";
  m_viewSelector->setCurrentIndex(0);

  emit requestObjects(PROFILEOBJECT);
  emit requestObjectsCounted(PROFILEOBJECT);
}

void MainWindow::launchWindow() {
  setupInitialState();

  this->show();
}

void MainWindow::handleObjectsCounted(ObjectTypes type, int count) {
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

  currentView->handleObjectsCounted(type, count);
}

void MainWindow::handleObjectCreated(ObjectTypes type, Storable *object) {
  QWidget *currentWidget = m_viewSelector->currentWidget();
  if (!currentWidget) {
    qDebug() << "No current widget selected";
    return;
  }

  AbstractView *currentView = currentWidget->findChild<AbstractView *>();

  switch (type) {
  case PROFILEOBJECT:
    qDebug() << "Profile created and captured by ui";
    m_status->showMessage(
        QString("Profile %1 created")
            .arg(qobject_cast<QProfile *>(object)->getUsername()),
        5000);
    currentView->handleObjectCreated(type, object);
    break;

  case INGREDIENTOBJECT:
    qDebug() << "Ingredient created and captured by ui";
    m_status->showMessage(
        QString("Ingredient %1 created")
            .arg(qobject_cast<QIngredient *>(object)->getName()),
        5000);
    currentView->handleObjectCreated(type, object);
    break;

  case RECIPEINGREDIENTOBJECT:
    qDebug() << "Recipe ingredient created and captured by ui";
    currentView->handleObjectCreated(type, object);
    break;

  case RECIPEOBJECT:
    qDebug() << "Recipe created and captured by ui";
    m_status->showMessage(QString("Recipe %1 created")
                              .arg(qobject_cast<QRecipe *>(object)->getName()),
                          5000);
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
            .arg(qobject_cast<QProfile *>(object)->getUsername()),
        5000);
    currentView->handleObjectLoaded(type, object);
    break;

  case INGREDIENTOBJECT:
    qDebug() << "Ingredient loaded and captured by ui";
    m_status->showMessage(
        QString("Ingredient %1 loaded")
            .arg(qobject_cast<QIngredient *>(object)->getName()),
        5000);
    currentView->handleObjectLoaded(type, object);
    break;

  case RECIPEINGREDIENTOBJECT:
    qDebug() << "Recipe ingredient loaded and captured by ui";
    currentView->handleObjectLoaded(type, object);
    break;

  case RECIPEOBJECT:
    qDebug() << "Recipe loaded and captured by ui";
    m_status->showMessage(
        QString("Recipe %1 loaded")
            .arg(qobject_cast<QIngredient *>(object)->getName()),
        5000);
    currentView->handleObjectLoaded(type, object);

    break;
  }
}

void MainWindow::handleProfileSelected(QProfile *profile) {
  if (profile == nullptr)
    return;

  m_selectedUserId = profile->getId();
  qDebug() << "Selected profile has ID" << m_selectedUserId;
}

void MainWindow::on_viewNavigator_currentChanged(int index) {
  switch (index) {
  case 0:
    // Clear the other models to save memory space
    // Request data for the relevant models
    m_ingredientView->clearModel();
    // m_recipeView->clearModel();
    emit requestObjects(PROFILEOBJECT);
    emit requestObjectsCounted(PROFILEOBJECT);
    break;

  case 1:
    m_profileView->clearModel();
    // m_recipeView->clearModel();
    emit requestObjects(INGREDIENTOBJECT);
    emit requestObjectsCounted(INGREDIENTOBJECT);
    break;

  case 2:
    m_profileView->clearModel();
    m_ingredientView->clearModel();
    emit requestObjects(RECIPEOBJECT);
    emit requestObjectsCounted(RECIPEOBJECT);
    break;
  }
}
