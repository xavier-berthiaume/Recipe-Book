#include "reciperootview.h"
#include "ingredientselectordialog.h"
#include "recipeingredientdelegate.h"
#include "recipelistdelegate.h"
#include "ui_reciperootview.h"

#include <QMessageBox>
#include <qnamespace.h>

RecipeRootView::RecipeRootView(DataCache *cache, QWidget *parent)
    : QWidget(parent), ui(new Ui::RecipeRootView), m_cache(cache),
      m_recipeIngredientFactory(new RecipeIngredientFactory(this)),
      m_recipeIngredientModel(new RecipeIngredientListModel(this)),
      m_recipeFactory(new RecipeFactory(this)),
      m_recipeModel(new RecipeListModel(this)) {
  ui->setupUi(this);
  m_stackedWidget = findChild<QStackedWidget *>("stackedWidget");
  m_stackedWidget->setCurrentIndex(0);

  m_formTitleLabel = m_stackedWidget->findChild<QLabel *>("formTitleLabel");
  m_nameEdit = m_stackedWidget->findChild<QLineEdit *>("nameEdit");
  m_descriptionEdit =
      m_stackedWidget->findChild<QPlainTextEdit *>("descriptionEdit");
  m_prepTimeEdit = m_stackedWidget->findChild<QTimeEdit *>("prepTimeEdit");
  m_recipeIngredientDeleteButton =
      m_stackedWidget->findChild<QPushButton *>("deleteRecipeIngredientButton");
  m_instructionList =
      m_stackedWidget->findChild<QListWidget *>("instructionsList");
  m_instructionEdit =
      m_stackedWidget->findChild<QLineEdit *>("instructionLineEdit");
  m_deleteInstructionButton =
      m_stackedWidget->findChild<QPushButton *>("deleteInstructionButton");
  m_addInstructionButton =
      m_stackedWidget->findChild<QPushButton *>("addInstructionButton");
  m_equipmentList = m_stackedWidget->findChild<QListWidget *>("equipmentList");
  m_equipmentEdit =
      m_stackedWidget->findChild<QLineEdit *>("equipmentLineEdit");
  m_addEquipmentButton =
      m_stackedWidget->findChild<QPushButton *>("addEquipmentButton");
  m_deleteEquipmentButton =
      m_stackedWidget->findChild<QPushButton *>("deleteEquipmentButton");
  m_confirmButton = m_stackedWidget->findChild<QPushButton *>("confirmButton");

  RecipeListDelegate *recipeDelegate = new RecipeListDelegate(this);
  m_recipeList = m_stackedWidget->findChild<QListView *>("recipeListView");
  m_recipeList->setModel(m_recipeModel);
  m_recipeList->setItemDelegate(recipeDelegate);
  m_recipeList->setMouseTracking(true);
  m_recipeList->viewport()->setAttribute(Qt::WA_Hover);

  RecipeIngredientDelegate *delegate = new RecipeIngredientDelegate(this);
  QListView *recipeIngredientListView =
      findChild<QListView *>("recipeIngredientListView");
  recipeIngredientListView->setModel(m_recipeIngredientModel);
  recipeIngredientListView->setItemDelegate(delegate);
  recipeIngredientListView->setMouseTracking(true);
  recipeIngredientListView->viewport()->setAttribute(Qt::WA_Hover);

  connect(m_recipeIngredientFactory,
          &RecipeIngredientFactory::recipeIngredientCreated, this,
          &RecipeRootView::recipeIngredientCreated);

  connect(m_recipeFactory, &RecipeFactory::recipeCreated, this,
          &RecipeRootView::recipeCreated);

  connect(this, &RecipeRootView::formInfoChanged, this,
          &RecipeRootView::on_formInfoChanged);
}

RecipeRootView::~RecipeRootView() { delete ui; }

void RecipeRootView::clearFields() {
  m_nameEdit->clear();
  m_descriptionEdit->clear();
  m_prepTimeEdit->setTime(QTime(0, 0));

  m_recipeIngredientModel->clear();
  m_instructionList->clear();
  m_equipmentList->clear();
}

bool RecipeRootView::validateFields() {

  qDebug() << "Validating fields";

  qDebug() << "Name Field:" << m_nameEdit->text();
  if (m_nameEdit->text().isEmpty()) {
    qDebug() << "Invalid name";
    return false;
  }

  qDebug() << "Description Field:" << m_descriptionEdit->toPlainText();
  if (m_descriptionEdit->toPlainText().isEmpty()) {
    qDebug() << "Invalid description";
    return false;
  }

  qDebug() << "Time Field:" << m_prepTimeEdit->time();
  if (m_prepTimeEdit->time() == QTime()) {
    qDebug() << "invalid time";
    return false;
  }

  qDebug() << "Recipe Ingredits:" << m_recipeIngredientModel->rowCount();
  if (m_recipeIngredientModel->rowCount() == 0) {
    qDebug() << "invalid recipe ingredients";
    return false;
  }

  qDebug() << "Instructions:" << m_instructionList->count();
  if (m_instructionList->count() == 0) {
    qDebug() << "invalid instructions";
    return false;
  }

  return true;
}

void RecipeRootView::on_addRecipeIngredientButton_clicked() {
  IngredientSelectorDialog *ingredientSelector =
      new IngredientSelectorDialog(m_cache, this);

  connect(ingredientSelector, &IngredientSelectorDialog::formSubmitted,
          m_recipeIngredientFactory,
          &RecipeIngredientFactory::createRecipeIngredient);

  if (ingredientSelector->exec() == QDialog::Accepted) {
    emit formInfoChanged();
  }
}

void RecipeRootView::on_createButton_clicked() {
  m_editRecipe = QModelIndex();
  m_editMode = false;

  m_formTitleLabel->setText(tr("Create a Recipe"));
  m_confirmButton->setText(tr("Create Recipe"));

  clearFields();
  m_stackedWidget->setCurrentIndex(1);
}

void RecipeRootView::on_cancelButton_clicked() {

  clearFields();
  m_stackedWidget->setCurrentIndex(0);
}

void RecipeRootView::recipeIngredientCreated(QRecipeIngredient *newIngredient) {
  m_recipeIngredientModel->addRecipeIngredient(newIngredient);
}

void RecipeRootView::on_confirmButton_clicked() {
  if (m_cache->getSelectedProfile() == nullptr) {
    QMessageBox::warning(
        this, tr("Profile Required"),
        tr("<html><div style='line-height:1.5;'>"
           "<b>No profile selected</b><br>"
           "Please select a profile from the Profiles page before "
           "creating ingredients or recipes."
           "<br></div></html>"),
        QMessageBox::Ok, QMessageBox::Ok);
    return;
  }

  QString name = m_nameEdit->text();
  QString description = m_descriptionEdit->toPlainText();
  QTime prepTime = m_prepTimeEdit->time();
  quint32 convertedPrepTime = prepTime.hour() * 60 + prepTime.minute();

  QList<QRecipeIngredient *> recipeIngredients =
      m_recipeIngredientModel->getList();

  QStringList instructions;
  for (int i = 0; i < m_instructionList->count(); i++) {
    instructions.push_back(m_instructionList->item(i)->text());
  }

  QStringList equipment;
  for (int i = 0; i < m_equipmentList->count(); i++) {
    equipment.push_back(m_equipmentList->item(i)->text());
  }

  if (m_editMode && m_editRecipe.isValid()) {

  } else {
    m_recipeFactory->createRecipe(m_cache->getSelectedProfile(), name,
                                  description, convertedPrepTime,
                                  recipeIngredients, instructions, equipment);
  }
  on_cancelButton_clicked();
}

void RecipeRootView::on_recipeIngredientListView_activated(
    const QModelIndex &index) {
  if (index.isValid() && index.row() < m_recipeIngredientModel->rowCount()) {
    m_recipeIngredientDeleteButton->setEnabled(true);
    m_selectedRecipeIngredient = index;
  } else {
    m_recipeIngredientDeleteButton->setEnabled(false);
    m_selectedRecipeIngredient = QModelIndex();
  }
}

void RecipeRootView::on_recipeIngredientListView_clicked(
    const QModelIndex &index) {
  if (index.isValid() && index.row() < m_recipeIngredientModel->rowCount()) {
    m_recipeIngredientDeleteButton->setEnabled(true);
    m_selectedRecipeIngredient = index;
  } else {
    m_recipeIngredientDeleteButton->setEnabled(false);
    m_selectedRecipeIngredient = QModelIndex();
  }
}

void RecipeRootView::on_deleteRecipeIngredientButton_clicked() {
  if (!m_selectedRecipeIngredient.isValid() ||
      m_selectedRecipeIngredient.row() >= m_recipeIngredientModel->rowCount())
    return;

  m_recipeIngredientModel->removeRecipeIngredient(
      m_selectedRecipeIngredient.row());
  emit formInfoChanged();

  QListView *recipeIngredientListView =
      findChild<QListView *>("recipeIngredientListView");
  m_selectedRecipeIngredient = recipeIngredientListView->currentIndex();

  if (m_selectedRecipeIngredient == QModelIndex()) {
    m_recipeIngredientDeleteButton->setEnabled(false);
  }
}

void RecipeRootView::on_instructionLineEdit_textChanged(const QString &arg1) {
  m_addInstructionButton->setEnabled(!arg1.isEmpty());
}

void RecipeRootView::on_equipmentLineEdit_textChanged(const QString &arg1) {
  m_addEquipmentButton->setEnabled(!arg1.isEmpty());
}

void RecipeRootView::on_addInstructionButton_clicked() {
  m_instructionList->addItem(m_instructionEdit->text());
  m_instructionEdit->clear();
  emit formInfoChanged();
}

void RecipeRootView::on_addEquipmentButton_clicked() {
  m_equipmentList->addItem(m_equipmentEdit->text());
  m_equipmentEdit->clear();
  emit formInfoChanged();
}

void RecipeRootView::on_instructionsList_clicked(const QModelIndex &index) {
  if (index.isValid() && index.row() < m_instructionList->count()) {
    m_selectedInstruction = index;
    m_deleteInstructionButton->setEnabled(true);
  } else {
    m_selectedInstruction = QModelIndex();
    m_deleteInstructionButton->setEnabled(false);
  }
}

void RecipeRootView::on_equipmentList_clicked(const QModelIndex &index) {
  if (index.isValid() && index.row() < m_equipmentList->count()) {
    m_selectedEquipment = index;
    m_deleteEquipmentButton->setEnabled(true);
  } else {
    m_selectedEquipment = QModelIndex();
    m_deleteEquipmentButton->setEnabled(false);
  }
}

void RecipeRootView::on_deleteInstructionButton_clicked() {
  if (!m_selectedInstruction.isValid() ||
      m_selectedInstruction.row() >= m_instructionList->count())
    return;

  int rowToRemove = m_selectedInstruction.row();

  QListWidgetItem *item = m_instructionList->takeItem(rowToRemove);
  if (item) {
    delete item;

    m_selectedInstruction = QModelIndex();
    m_instructionList->clearSelection();
    emit formInfoChanged();

    m_deleteInstructionButton->setEnabled(false);

    qDebug() << "Instruction at row" << rowToRemove << "deleted";
  } else {
    qWarning() << "Failed to delete instruction at row" << rowToRemove;
  }
}

void RecipeRootView::on_deleteEquipmentButton_clicked() {
  if (!m_selectedEquipment.isValid() ||
      m_selectedEquipment.row() < m_equipmentList->count())
    return;

  int rowToRemove = m_selectedEquipment.row();

  QListWidgetItem *item = m_equipmentList->takeItem(rowToRemove);

  if (item) {
    delete item;

    m_selectedEquipment = QModelIndex();
    m_equipmentList->clearSelection();
    emit formInfoChanged();

    m_deleteInstructionButton->setEnabled(false);

    qDebug() << "Equipment at row" << rowToRemove << "deleted";
  } else {
    qWarning() << "Failed to delete equipment at row" << rowToRemove;
  }
}

void RecipeRootView::on_formInfoChanged() {
  m_confirmButton->setEnabled(validateFields());
}

void RecipeRootView::on_nameEdit_textChanged(const QString &arg1) {
  emit formInfoChanged();
}

void RecipeRootView::on_descriptionEdit_textChanged() {
  emit formInfoChanged();
}

void RecipeRootView::on_prepTimeEdit_timeChanged(const QTime &time) {
  emit formInfoChanged();
}

void RecipeRootView::recipeCreated(QRecipe *newRecipe) {
  newRecipe->setParent(this);
  m_cache->addRecipeToCache(newRecipe);
  m_recipeModel->addRecipe(newRecipe);
}
