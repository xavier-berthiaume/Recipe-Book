#ifndef RECIPEROOTVIEW_H
#define RECIPEROOTVIEW_H

#include <QLabel>
#include <QListView>
#include <QModelIndex>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QStackedWidget>
#include <QTimeEdit>
#include <QWidget>

#include "datacache.h"
#include "recipeingredientfactory.h"
#include "recipeingredientlistmodel.h"

namespace Ui {
class RecipeRootView;
}

class RecipeRootView : public QWidget {
  Q_OBJECT

  Ui::RecipeRootView *ui;

  DataCache *m_cache;

  RecipeIngredientFactory *m_recipeIngredientFactory;

  QStackedWidget *m_stackedWidget;
  QLabel *m_formTitleLabel;
  QLineEdit *nameEdit;
  QPlainTextEdit *descriptionEdit;
  QTimeEdit *prepTimeEdit;
  QPushButton *m_recipeIngredientDeleteButton;
  QLineEdit *m_instructionEdit;
  QPushButton *m_addInstructionButton;
  QPushButton *m_deleteInstructionButton;
  QLineEdit *m_equipmentEdit;
  QPushButton *m_addEquipmentButton;
  QPushButton *m_deleteEquipmentButton;
  QPushButton *m_confirmButton;

  RecipeIngredientListModel *m_recipeIngredientModel;

  QModelIndex m_editRecipe = QModelIndex();
  QModelIndex m_selectedRecipeIngredient = QModelIndex();
  bool m_editMode = false;

public:
  explicit RecipeRootView(DataCache *cache = nullptr,
                          QWidget *parent = nullptr);
  ~RecipeRootView();

private slots:

  void on_addRecipeIngredientButton_clicked();

  void on_createButton_clicked();

  void on_cancelButton_clicked();

  void recipeIngredientCreated(QRecipeIngredient *newRecipeIngredient);

  void on_confirmButton_clicked();

  void on_recipeIngredientListView_activated(const QModelIndex &index);

  void on_recipeIngredientListView_clicked(const QModelIndex &index);

  void on_deleteRecipeIngredientButton_clicked();

  void on_instructionLineEdit_textChanged(const QString &arg1);

  signals:
  void formSubmitted();
};

#endif // RECIPEROOTVIEW_H
