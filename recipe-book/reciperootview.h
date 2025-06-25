#ifndef RECIPEROOTVIEW_H
#define RECIPEROOTVIEW_H

#include <QWidget>
#include <QStackedWidget>
#include <QModelIndex>
#include <QPushButton>
#include <QLabel>

#include "datacache.h"
#include "recipeingredientfactory.h"

namespace Ui {
class RecipeRootView;
}

class RecipeRootView : public QWidget
{
    Q_OBJECT

    DataCache *m_cache;

    RecipeIngredientFactory *m_recipeIngredientFactory;

    QStackedWidget *m_stackedWidget;
    QLabel *m_formTitleLabel;
    QPushButton *m_confirmButton;

    QModelIndex m_editRecipe = QModelIndex();
    bool m_editMode = false;

public:
    explicit RecipeRootView(DataCache *cache = nullptr, QWidget *parent = nullptr);
    ~RecipeRootView();

private slots:

    void on_addRecipeIngredientButton_clicked();

    void on_createButton_clicked();

    void on_cancelButton_clicked();

private:
    Ui::RecipeRootView *ui;
};

#endif // RECIPEROOTVIEW_H
