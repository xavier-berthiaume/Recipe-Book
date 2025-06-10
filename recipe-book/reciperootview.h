#ifndef RECIPEROOTVIEW_H
#define RECIPEROOTVIEW_H

#include <QWidget>

namespace Ui {
class RecipeRootView;
}

class RecipeRootView : public QWidget
{
    Q_OBJECT

public:
    explicit RecipeRootView(QWidget *parent = nullptr);
    ~RecipeRootView();

private:
    Ui::RecipeRootView *ui;
};

#endif // RECIPEROOTVIEW_H
