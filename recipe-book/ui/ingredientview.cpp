#include "ingredientview.h"
#include "ingredientform.h"
#include "displayingredientview.h"
#include "ingredientlistdelegate.h"
#include "ui_ingredientview.h"

IngredientView::IngredientView(QWidget *parent)
    : AbstractView(parent), ui(new Ui::IngredientView),
      m_ingredientModel(new IngredientListModel(this)) {
  ui->setupUi(this);

  m_listView = findChild<QListView *>("ingredientListView");
  m_listView->setModel(m_ingredientModel);
  m_listView->setItemDelegate(new IngredientListDelegate(this));

  m_loadMoreButton = findChild<QToolButton *>("loadMoreButton");
  m_editButton = findChild<QToolButton *>("editButton");
  m_deleteButton = findChild<QToolButton *>("deleteButton");
  m_detailsButton = findChild<QPushButton *>("detailsButton");

  m_loadedCountIndicator = findChild<QLabel *>("loadedCountIndicator");
  m_totalCountIndicator = findChild<QLabel *>("totalCountIndicator");

  checkLoadedStatus();
}

IngredientView::~IngredientView() { delete ui; }

void IngredientView::clearModel() {
  m_ingredientModel->clearModel();
  setLoadedCount();
}

void IngredientView::handleObjectsCounted(ObjectTypes type, int count) {
  m_totalCount = count;
  m_totalCountIndicator->setText(QString::number(m_totalCount));
}

void IngredientView::handleObjectCreated(ObjectTypes type, Storable *object) {
  qDebug() << "Adding ingredient to list model";

  switch (type) {
  case INGREDIENTOBJECT:
    m_ingredientModel->addModel(qobject_cast<QIngredient *>(object));
    setLoadedCount();
    incrementTotalCount();
    break;

  default:
    break;
  }
}

void IngredientView::handleObjectLoaded(ObjectTypes type, Storable *object) {
    QList<QWidget*> children = findChildren<QWidget*>();

    switch (type) {
    case INGREDIENTOBJECT:
        qDebug() << "Adding ingredient to list model";
        m_ingredientModel->addModel(qobject_cast<QIngredient *>(object));
        setLoadedCount();
        checkLoadedStatus();
        break;

    case PROFILEOBJECT:
        qDebug() << "Adding to ingredient detailed view profile with id" << object->getId().toString();

        for(QWidget *child : children) {
            DisplayIngredientView* dialog = qobject_cast<DisplayIngredientView*>(child);
            if (dialog) {
                qDebug() << "Found ingredient detail dialog, passing profile";
                QProfile* profile = qobject_cast<QProfile*>(object);
                dialog->setCreatorName(profile);
            }
        }

    default:
        break;
    }
}

void IngredientView::setLoadedCount() {
  m_loadedCountIndicator->setText(
      QString::number(m_ingredientModel->rowCount()));
}

void IngredientView::incrementTotalCount() {
  m_totalCount++;
  m_totalCountIndicator->setText(QString::number(m_totalCount));
}

void IngredientView::decrementTotalCount() {
  m_totalCount--;
  m_totalCountIndicator->setText(QString::number(m_totalCount));
}

void IngredientView::checkLoadedStatus() {
  m_loadMoreButton->setEnabled(
      !(m_totalCount == m_ingredientModel->rowCount()));
}

void IngredientView::on_loadMoreButton_clicked()
{
  emit requestObjects(INGREDIENTOBJECT, m_ingredientModel->rowCount(), 10);
}

void IngredientView::on_createButton_clicked() {
  IngredientForm *form = IngredientForm::createForm(this);

  connect(form, &IngredientForm::createRequested, this,
          &IngredientView::createObjectRequested);

  form->exec();
}

void IngredientView::on_deleteButton_clicked()
{
    QIngredient *ingredientToDelete = m_ingredientModel->getIngredient(m_listView->currentIndex());

    if (ingredientToDelete == nullptr)
        return;

    qDebug() << "Requesting to delete ingredient with id" << ingredientToDelete->getId().toString();
    m_ingredientModel->removeModel(m_listView->currentIndex().row());

    setLoadedCount();
    decrementTotalCount();
    emit deleteObjectRequested(INGREDIENTOBJECT, ingredientToDelete);
}

void IngredientView::on_editButton_clicked()
{
    QIngredient *ingredientToUpdate = m_ingredientModel->getIngredient(m_listView->currentIndex());

    if (ingredientToUpdate == nullptr)
        return;

    IngredientForm *form = IngredientForm::editForm(ingredientToUpdate, this);

    connect(form, &IngredientForm::updateRequested, [this, ingredientToUpdate](ObjectTypes type, Storable *object, const QVariantMap &data) {
        qDebug() << "Update form submitted with data" << data;
        ingredientToUpdate->setName(data["name"].toString());
        ingredientToUpdate->setDescription(data["description"].toString());
        emit updateObjectRequested(type, object);
    });

    form->exec();
}


void IngredientView::on_ingredientListView_clicked(const QModelIndex &index)
{
  m_editButton->setEnabled(index.isValid());
  m_deleteButton->setEnabled(index.isValid());
  m_detailsButton->setEnabled(index.isValid());
}


void IngredientView::on_detailsButton_clicked()
{
    QIngredient *ingredientToRead = m_ingredientModel->getIngredient(m_listView->currentIndex());

    if (ingredientToRead == nullptr)
        return;

    DisplayIngredientView *detailView = new DisplayIngredientView(ingredientToRead, this);
    detailView->show();
    emit requestObject(PROFILEOBJECT, ingredientToRead->getCreatorId());
}

