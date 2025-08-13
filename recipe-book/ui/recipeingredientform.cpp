#include "recipeingredientform.h"
#include "ui_recipeingredientform.h"

RecipeIngredientForm::RecipeIngredientForm(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::RecipeIngredientForm)
{
    ui->setupUi(this);
}

RecipeIngredientForm::~RecipeIngredientForm()
{
    delete ui;
}
