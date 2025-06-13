#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QPushButton>

#include "profilerootview.h"
#include "ingredientrootview.h"
#include "reciperootview.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    Ui::MainWindow *ui;

    ProfileRootView *m_profilePage;
    IngredientRootView *m_ingredientPage;
    RecipeRootView *m_recipePage;

    QStackedWidget *m_centerStack;

    QPushButton *profileButton;
    QPushButton *ingredientButton;
    QPushButton *recipeButton;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void on_profileButton_pressed();
    void on_ingredientButton_pressed();
    void on_recipeButton_pressed();
};
#endif // MAINWINDOW_H
