#ifndef INGREDIENTROOTVIEW_H
#define INGREDIENTROOTVIEW_H

#include <QWidget>

namespace Ui {
class IngredientRootView;
}

class IngredientRootView : public QWidget
{
    Q_OBJECT

public:
    explicit IngredientRootView(QWidget *parent = nullptr);
    ~IngredientRootView();

private:
    Ui::IngredientRootView *ui;
};

#endif // INGREDIENTROOTVIEW_H
