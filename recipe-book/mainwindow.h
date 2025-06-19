#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QPushButton>

#include "profilerootview.h"
#include "ingredientrootview.h"
#include "reciperootview.h"
#include "datacache.h"

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

    DataCache *m_cache;

    QProfile *m_currentProfile;

public:
    MainWindow(DataCache *cache, QWidget *parent = nullptr);
    ~MainWindow();

    DataCache* cache() const { return m_cache; }

private slots:
    void on_profileButton_pressed();
    void on_ingredientButton_pressed();
    void on_recipeButton_pressed();

    void on_profileChanged(QProfile *profile);

signals:
    void profileChanged(QProfile *profile);
};
#endif // MAINWINDOW_H
