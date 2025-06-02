#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLabel>
#include <QMainWindow>

#include "../models/ingredient_factory.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

  Ui::MainWindow *ui;

  IngredientFactory *ingredientFactory;
  QList<QtIngredientWrapper *> ingredientCache;

  void setupFactories();
  void setupMenu();
  void showInfoModal(const QString &title, const QString &message);

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();
};
#endif // MAINWINDOW_H
