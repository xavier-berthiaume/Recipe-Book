#include "ingredientselectordialog.h"
#include "ui_ingredientselectordialog.h"

IngredientSelectorDialog::IngredientSelectorDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::IngredientSelectorDialog)
{
    ui->setupUi(this);
}

IngredientSelectorDialog::~IngredientSelectorDialog()
{
    delete ui;
}
