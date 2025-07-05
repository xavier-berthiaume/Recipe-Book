#ifndef RECIPEROOTVIEW_H
#define RECIPEROOTVIEW_H

#include <QLabel>
#include <QListView>
#include <QListWidget>
#include <QModelIndex>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QStackedWidget>
#include <QTimeEdit>
#include <QWidget>

#include "datacache.h"
#include "recipeingredientfactory.h"
#include "recipeingredientlistmodel.h"
#include "recipefactory.h"
#include "recipelistmodel.h"

namespace Ui {
class RecipeRootView;
}

class RecipeRootView : public QWidget {
  Q_OBJECT

  Ui::RecipeRootView *ui;

  DataCache *m_cache;

  QStackedWidget *m_stackedWidget;
  QListView *m_recipeList;
  QLabel *m_formTitleLabel;
  QLineEdit *m_nameEdit;
  QPlainTextEdit *m_descriptionEdit;
  QTimeEdit *m_prepTimeEdit;
  QPushButton *m_recipeIngredientDeleteButton;
  QListWidget *m_instructionList;
  QLineEdit *m_instructionEdit;
  QPushButton *m_addInstructionButton;
  QPushButton *m_deleteInstructionButton;
  QListWidget *m_equipmentList;
  QLineEdit *m_equipmentEdit;
  QPushButton *m_addEquipmentButton;
  QPushButton *m_deleteEquipmentButton;
  QPushButton *m_confirmButton;

  RecipeIngredientFactory *m_recipeIngredientFactory;
  RecipeIngredientListModel *m_recipeIngredientModel;

  RecipeFactory *m_recipeFactory;
  RecipeListModel *m_recipeModel;

  QModelIndex m_editRecipe = QModelIndex();
  QModelIndex m_selectedRecipeIngredient = QModelIndex();
  QModelIndex m_selectedInstruction = QModelIndex();
  QModelIndex m_selectedEquipment = QModelIndex();
  bool m_editMode = false;

  bool validateFields();
  void clearFields();

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
  void on_equipmentLineEdit_textChanged(const QString &arg1);
  void on_addInstructionButton_clicked();
  void on_addEquipmentButton_clicked();
  void on_instructionsList_clicked(const QModelIndex &index);
  void on_equipmentList_clicked(const QModelIndex &index);
  void on_deleteInstructionButton_clicked();
  void on_deleteEquipmentButton_clicked();
  void on_formInfoChanged();
  void on_nameEdit_textChanged(const QString &arg1);
  void on_descriptionEdit_textChanged();
  void on_prepTimeEdit_timeChanged(const QTime &time);
  void recipeCreated(QRecipe *newRecipe);

signals:
  void formSubmitted(
        const QString &name,
        const QString &description,
        quint32 prepTimeMinutes,
        const QList<QRecipeIngredient *> &recipeIngredients,
        const QStringList &instructions,
        const QStringList &equipment
    );
  void formInfoChanged();
};

#endif // RECIPEROOTVIEW_H
