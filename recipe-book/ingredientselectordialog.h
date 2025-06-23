#ifndef INGREDIENTSELECTORDIALOG_H
#define INGREDIENTSELECTORDIALOG_H

#include <QDialog>

namespace Ui {
class IngredientSelectorDialog;
}

class IngredientSelectorDialog : public QDialog
{
    Q_OBJECT

public:
    explicit IngredientSelectorDialog(QWidget *parent = nullptr);
    ~IngredientSelectorDialog();

private:
    Ui::IngredientSelectorDialog *ui;
};

#endif // INGREDIENTSELECTORDIALOG_H
