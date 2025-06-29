#include "reciperootview.h"
#include "ui_reciperootview.h"

#include "ingredientselectordialog.h"
#include "recipeingredientdelegate.h"

RecipeRootView::RecipeRootView(DataCache *cache, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::RecipeRootView)
    , m_cache(cache)
    , m_recipeIngredientFactory(new RecipeIngredientFactory(this))
    , m_recipeIngredientModel(new RecipeIngredientListModel(this))
{
    ui->setupUi(this);
    m_stackedWidget = findChild<QStackedWidget *>("stackedWidget");
    m_stackedWidget->setCurrentIndex(0);

    m_formTitleLabel = m_stackedWidget->findChild<QLabel *>("formTitleLabel");
    m_confirmButton = m_stackedWidget->findChild<QPushButton *>("confirmButton");

    RecipeIngredientDelegate *delegate = new RecipeIngredientDelegate(this);
    QListView *recipeIngredientListView = findChild<QListView *>("recipeIngredientListView");
    recipeIngredientListView->setModel(m_recipeIngredientModel);
    recipeIngredientListView->setItemDelegate(delegate);
    recipeIngredientListView->setMouseTracking(true);
    recipeIngredientListView->viewport()->setAttribute(Qt::WA_Hover);

    connect(m_recipeIngredientFactory, &RecipeIngredientFactory::recipeIngredientCreated,
            this, &RecipeRootView::recipeIngredientCreated);
}

RecipeRootView::~RecipeRootView()
{
    delete ui;
}

void RecipeRootView::on_addRecipeIngredientButton_clicked()
{
    IngredientSelectorDialog *ingredientSelector = new IngredientSelectorDialog(m_cache, this);

    connect(ingredientSelector, &IngredientSelectorDialog::formSubmitted,
            m_recipeIngredientFactory, &RecipeIngredientFactory::createRecipeIngredient);

    ingredientSelector->exec();
}


void RecipeRootView::on_createButton_clicked()
{
    m_editRecipe = QModelIndex();
    m_editMode = false;

    m_formTitleLabel->setText(tr("Create a Recipe"));
    m_confirmButton->setText(tr("Create Recipe"));

    // Clear all the fields

    m_stackedWidget->setCurrentIndex(1);
}


void RecipeRootView::on_cancelButton_clicked()
{
    // Clear all the fields

    m_stackedWidget->setCurrentIndex(0);
}

void RecipeRootView::recipeIngredientCreated(QRecipeIngredient *newIngredient) {
    m_recipeIngredientModel->addRecipeIngredient(newIngredient);
}
