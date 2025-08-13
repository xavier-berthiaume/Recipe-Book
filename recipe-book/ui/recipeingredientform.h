#ifndef RECIPEINGREDIENTFORM_H
#define RECIPEINGREDIENTFORM_H

#include <QDialog>

namespace Ui {
class RecipeIngredientForm;
}

class RecipeIngredientForm : public QDialog
{
    Q_OBJECT

public:
    explicit RecipeIngredientForm(QWidget *parent = nullptr);
    ~RecipeIngredientForm();

private:
    Ui::RecipeIngredientForm *ui;
};

#endif // RECIPEINGREDIENTFORM_H
