#ifndef INGREDIENTROOTVIEW_H
#define INGREDIENTROOTVIEW_H

#include <QWidget>
#include <QStackedWidget>

#include "ingredientlistmodel.h"
#include "ingredientfactory.h"
#include "datacache.h"

namespace Ui {
class IngredientRootView;
}

class IngredientRootView : public QWidget
{
    Q_OBJECT

    Ui::IngredientRootView *ui;

    DataCache *m_cache;

    QStackedWidget *m_stackedWidget;
    IngredientListModel *m_model;
    IngredientFactory *m_factory;

    QModelIndex m_editIngredient = QModelIndex();
    bool m_editMode = false;

public:
    explicit IngredientRootView(DataCache *cache = nullptr, QWidget *parent = nullptr);
    ~IngredientRootView();

private slots:
    void on_createButton_clicked();
    void on_cancelButton_clicked();
    void on_nameLineEdit_textChanged(const QString &arg1);
    void on_descriptionEdit_textChanged();
    void on_confirmButton_clicked();

    void editButtonClicked(const QModelIndex &index);
    void deleteButtonClicked(const QModelIndex &index);

    void ingredientCreated(QIngredient *newIngredient);
};

#endif // INGREDIENTROOTVIEW_H
