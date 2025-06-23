#include "reciperootview.h"
#include "ui_reciperootview.h"

#include "ingredientselectordialog.h"

RecipeRootView::RecipeRootView(DataCache *cache, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::RecipeRootView)
    , m_cache(cache)
{
    ui->setupUi(this);
}

RecipeRootView::~RecipeRootView()
{
    delete ui;
}

void RecipeRootView::on_pushButton_clicked()
{
    IngredientSelectorDialog *ingredientSelector = new IngredientSelectorDialog(m_cache, this);

    ingredientSelector->exec();
}

