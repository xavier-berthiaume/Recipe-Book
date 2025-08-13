#include "recipeview.h"
#include "recipelistdelegate.h"
#include "ui_recipeview.h"
#include "recipeform.h"

RecipeView::RecipeView(QWidget *parent)
    : AbstractView(parent), ui(new Ui::RecipeView),
      m_recipeModel(new RecipeListModel(this)) {
  ui->setupUi(this);

  m_listView = findChild<QListView *>("listView");
  m_listView->setModel(m_recipeModel);
  m_listView->setItemDelegate(new RecipeListDelegate(this));

  m_loadMoreButton = findChild<QToolButton *>("loadMoreButton");
  m_editButton = findChild<QToolButton *>("editButton");
  m_deleteButton = findChild<QToolButton *>("deleteButton");

  m_loadedCountIndicator = findChild<QLabel *>("loadedCountIndicator");
  m_totalCountIndicator = findChild<QLabel *>("totalCountIndicator");

  checkLoadedStatus();
}

RecipeView::~RecipeView() { delete ui; }

void RecipeView::setLoadedCount() {
  m_loadedCountIndicator->setText(QString::number(m_recipeModel->rowCount()));
}

void RecipeView::incrementTotalCount() {
  m_totalCount++;
  m_totalCountIndicator->setText(QString::number(m_totalCount));
}

void RecipeView::decrementTotalCount() {
  m_totalCount--;
  m_totalCountIndicator->setText(QString::number(m_totalCount));
}

void RecipeView::checkLoadedStatus() {
  m_loadMoreButton->setEnabled(!(m_totalCount == m_recipeModel->rowCount()));
}

void RecipeView::clearModel() {
  m_recipeModel->clearModel();
  setLoadedCount();
}

void RecipeView::handleObjectsCounted(ObjectTypes type, int count) {
  m_totalCount = count;
  m_totalCountIndicator->setText(QString::number(m_totalCount));
}

void RecipeView::handleObjectCreated(ObjectTypes type, Storable *object) {
  switch (type) {
  case RECIPEOBJECT:
    m_recipeModel->addModel(qobject_cast<QRecipe *>(object));
    setLoadedCount();
    incrementTotalCount();
    break;

  default:
    break;
  }
}

void RecipeView::handleObjectLoaded(ObjectTypes type, Storable *object) {
  switch (type) {
  case RECIPEOBJECT:
    m_recipeModel->addModel(qobject_cast<QRecipe *>(object));
    setLoadedCount();
    checkLoadedStatus();
    break;

  default:
    break;
  }
}

void RecipeView::on_createButton_clicked()
{
    RecipeForm *form = RecipeForm::createForm(this);

    connect(form, &RecipeForm::createRequested, this, &RecipeView::createObjectRequested);

    form->exec();
}

