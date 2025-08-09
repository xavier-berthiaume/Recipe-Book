#include "displayingredientview.h"
#include "ui_displayingredientview.h"

DisplayIngredientView::DisplayIngredientView(QIngredient *ingredient, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DisplayIngredientView)
{
    ui->setupUi(this);

    m_nameLabel = findChild<QLabel *>("nameLabel");
    m_creatorLabel = findChild<QLabel *>("creatorLabel");
    m_descriptionBrowser = findChild<QTextBrowser *>("descriptionBrowser");

    m_ingredient = ingredient;

    m_nameLabel->setText(m_ingredient->getName());
    m_descriptionBrowser->setText(m_ingredient->getDescription());
}

DisplayIngredientView::~DisplayIngredientView()
{
    delete ui;
}

void DisplayIngredientView::setCreatorName(QProfile *creator) {
    if (creator->getId() != m_ingredient->getCreatorId())
        return;

    m_creatorLabel->setText(QString("Created by %1").arg(creator->getUsername()));
}
