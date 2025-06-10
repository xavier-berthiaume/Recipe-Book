#include "ingredientrootview.h"
#include "ui_ingredientrootview.h"

IngredientRootView::IngredientRootView(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::IngredientRootView)
{
    ui->setupUi(this);
}

IngredientRootView::~IngredientRootView()
{
    delete ui;
}
