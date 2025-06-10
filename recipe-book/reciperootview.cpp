#include "reciperootview.h"
#include "ui_reciperootview.h"

RecipeRootView::RecipeRootView(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::RecipeRootView)
{
    ui->setupUi(this);
}

RecipeRootView::~RecipeRootView()
{
    delete ui;
}
