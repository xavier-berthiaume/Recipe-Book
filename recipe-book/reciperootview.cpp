#include "reciperootview.h"
#include "ingredientselectordialog.h"
#include "recipeingredientdelegate.h"
#include "ui_reciperootview.h"

RecipeRootView::RecipeRootView(DataCache *cache, QWidget *parent)
    : QWidget(parent), ui(new Ui::RecipeRootView), m_cache(cache),
      m_recipeIngredientFactory(new RecipeIngredientFactory(this)),
      m_recipeIngredientModel(new RecipeIngredientListModel(this)) {
  ui->setupUi(this);
  m_stackedWidget = findChild<QStackedWidget *>("stackedWidget");
  m_stackedWidget->setCurrentIndex(0);

  m_formTitleLabel = m_stackedWidget->findChild<QLabel *>("formTitleLabel");
  m_recipeIngredientDeleteButton = m_stackedWidget->findChild<QPushButton *>("deleteRecipeIngredientButton");
  m_instructionEdit = m_stackedWidget->findChild<QLineEdit *>("instructionLineEdit");
  m_deleteInstructionButton = m_stackedWidget->findChild<QPushButton *>("deleteInstructionButton");
  m_equipmentEdit = m_stackedWidget->findChild<QLineEdit *>("equipmentLineEdit");
  m_deleteEquipmentButton = m_stackedWidget->findChild<QPushButton *>("deleteEquipmentButton");
  m_confirmButton = m_stackedWidget->findChild<QPushButton *>("confirmButton");

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
}

RecipeRootView::~RecipeRootView() { delete ui; }

void RecipeRootView::on_addRecipeIngredientButton_clicked() {
  IngredientSelectorDialog *ingredientSelector =
      new IngredientSelectorDialog(m_cache, this);

  connect(ingredientSelector, &IngredientSelectorDialog::formSubmitted,
          m_recipeIngredientFactory,
          &RecipeIngredientFactory::createRecipeIngredient);

  ingredientSelector->exec();
}

void RecipeRootView::on_createButton_clicked() {
  m_editRecipe = QModelIndex();
  m_editMode = false;

  m_formTitleLabel->setText(tr("Create a Recipe"));
  m_confirmButton->setText(tr("Create Recipe"));

  // Clear all the fields

  m_stackedWidget->setCurrentIndex(1);
}

void RecipeRootView::on_cancelButton_clicked() {
  // Clear all the fields

  m_stackedWidget->setCurrentIndex(0);
}

void RecipeRootView::recipeIngredientCreated(QRecipeIngredient *newIngredient) {
  m_recipeIngredientModel->addRecipeIngredient(newIngredient);
}

void RecipeRootView::on_confirmButton_clicked() { emit formSubmitted(); }


void RecipeRootView::on_recipeIngredientListView_activated(const QModelIndex &index)
{
    if (index.isValid() && index.row() < m_recipeIngredientModel->rowCount()) {
        m_recipeIngredientDeleteButton->setEnabled(true);
        m_selectedRecipeIngredient = index;
    } else {
        m_recipeIngredientDeleteButton->setEnabled(false);
        m_selectedRecipeIngredient = QModelIndex();
    }
}


void RecipeRootView::on_recipeIngredientListView_clicked(const QModelIndex &index)
{
    if (index.isValid() && index.row() < m_recipeIngredientModel->rowCount()) {
        m_recipeIngredientDeleteButton->setEnabled(true);
        m_selectedRecipeIngredient = index;
    } else {
        m_recipeIngredientDeleteButton->setEnabled(false);
        m_selectedRecipeIngredient = QModelIndex();
    }
}


void RecipeRootView::on_deleteRecipeIngredientButton_clicked()
{
    if (!m_selectedRecipeIngredient.isValid()
        || m_selectedRecipeIngredient.row() >= m_recipeIngredientModel->rowCount())
        return;

    m_recipeIngredientModel->removeRecipeIngredient(m_selectedRecipeIngredient.row());

    QListView *recipeIngredientListView =
        findChild<QListView *>("recipeIngredientListView");
    m_selectedRecipeIngredient = recipeIngredientListView->currentIndex();

    if (m_selectedRecipeIngredient == QModelIndex()) {
        m_recipeIngredientDeleteButton->setEnabled(false);
    }
}


void RecipeRootView::on_instructionLineEdit_textChanged(const QString &arg1)
{

}

