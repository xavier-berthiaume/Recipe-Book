#ifndef INGREDIENTSELECTORDIALOG_H
#define INGREDIENTSELECTORDIALOG_H

#include <QDialog>
#include <QListView>
#include <QDoubleSpinBox>
#include <QComboBox>

#include "datacache.h"
#include "ingredientlistmodel.h"
#include "ingredientselectiondelegate.h"

namespace Ui {
class IngredientSelectorDialog;
}

class IngredientSelectorDialog : public QDialog
{
    Q_OBJECT

    Ui::IngredientSelectorDialog *ui;

    DataCache *m_cache;
    IngredientListModel *ingredientModel;
    IngredientSelectionDelegate *delegate;

    QPushButton *m_ingredientButton;
    QPushButton *m_recipeButton;
    QPushButton *m_okButton;
    QDoubleSpinBox *m_quantitySpinbox;
    QComboBox *m_unitCombobox;
    QListView *m_listView;

    bool validateFields();
public:
    explicit IngredientSelectorDialog(DataCache *cache = nullptr, QWidget *parent = nullptr);
    ~IngredientSelectorDialog();

private slots:
    void on_ingredientButton_pressed();

    void on_recipeButton_pressed();

    void on_quantitySpinbox_valueChanged(double arg1);
    void on_unitCombobox_currentIndexChanged(int index);
    void on_listView_indexesMoved(const QModelIndexList &indexes);
};

#endif // INGREDIENTSELECTORDIALOG_H
