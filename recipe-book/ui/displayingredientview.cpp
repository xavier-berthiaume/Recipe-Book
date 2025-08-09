#include "displayingredientview.h"
#include "ui_displayingredientview.h"

DisplayIngredientView::DisplayIngredientView(QIngredient *ingredient, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DisplayIngredientView)
{
    ui->setupUi(this);

    m_nameLabel = findChild<QLabel *>("nameLabel");
    m_descriptionBrowser = findChild<QTextBrowser *>("descriptionBrowser");

    m_nameLabel->setText(ingredient->getName());
    m_descriptionBrowser->setText(ingredient->getDescription());
}

DisplayIngredientView::~DisplayIngredientView()
{
    delete ui;
}
