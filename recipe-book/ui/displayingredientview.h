#ifndef DISPLAYINGREDIENTVIEW_H
#define DISPLAYINGREDIENTVIEW_H

#include "../models.h"

#include <QDialog>
#include <QLabel>
#include <QTextBrowser>

namespace Ui {
class DisplayIngredientView;
}

class DisplayIngredientView : public QDialog
{
    Q_OBJECT

    Ui::DisplayIngredientView *ui;

    QIngredient *m_ingredient;
    QLabel *m_nameLabel;
    QLabel *m_creatorLabel;
    QTextBrowser *m_descriptionBrowser;

public:
    explicit DisplayIngredientView(QIngredient *ingredient, QWidget *parent = nullptr);
    ~DisplayIngredientView();

    void setCreatorName(QProfile *creator);
};

#endif // DISPLAYINGREDIENTVIEW_H
