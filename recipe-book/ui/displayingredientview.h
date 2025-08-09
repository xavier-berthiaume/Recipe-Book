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

    QLabel *m_nameLabel;
    QTextBrowser *m_descriptionBrowser;

public:
    explicit DisplayIngredientView(QIngredient *ingredient, QWidget *parent = nullptr);
    ~DisplayIngredientView();
};

#endif // DISPLAYINGREDIENTVIEW_H
