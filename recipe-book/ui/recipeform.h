#ifndef RECIPEFORM_H
#define RECIPEFORM_H

#include "abstractform.h"
#include "recipeingredientform.h"

#include <QDialog>
#include <QLineEdit>
#include <QListView>
#include <QListWidget>
#include <QPlainTextEdit>

namespace Ui {
class RecipeForm;
}

class RecipeForm : public AbstractForm {
  Q_OBJECT

  explicit RecipeForm(QWidget *parent = nullptr);
  explicit RecipeForm(Storable *object, QWidget *parent = nullptr);

  bool validateForm() override;
  void extractFormData() override;
  void populateForm(const QVariantMap &data) override;
  void clearForm() override;
  void initialize();

  RecipeIngredientForm *m_ingredientForm = nullptr;

  QLineEdit *m_nameEdit;
  QPlainTextEdit *m_descriptionEdit;
  QPlainTextEdit *m_notesEdit;

  QLineEdit *m_instructionEdit;
  QListWidget *m_instructionWidget;
  QToolButton *m_instructionCreate;
  QToolButton *m_instructionEditButton;
  QToolButton *m_instructionRemove;

  QLineEdit *m_equipmentEdit;
  QListWidget *m_equipmentWidget;
  QToolButton *m_equipmentCreate;
  QToolButton *m_equipmentEditButton;
  QToolButton *m_equipmentRemove;

  QListView *m_recipeIngredientList;

  Ui::RecipeForm *ui;

public:
  static RecipeForm *createForm(QWidget *parent);
  static RecipeForm *editForm(Storable *object, QWidget *parent);

  ~RecipeForm();

public slots:
  void handleObjectsCounted(ObjectTypes type, int count);
  void handleObjectCreated(ObjectTypes type, Storable *object);
  void handleObjectLoaded(ObjectTypes type, Storable *object);

private slots:
  void addInstructionToList();
  void addEquipmentToList();
  void on_instructionEdit_textChanged(const QString &arg1);
  void on_equipmentEdit_textChanged(const QString &arg1);
  void on_instructionList_itemSelectionChanged();
  void on_equipmentList_itemSelectionChanged();
  void on_deleteInstructionButton_clicked();
  void on_deleteEquipmentButton_clicked();
  void on_editInstructionButton_clicked();
  void on_editEquipmentButton_clicked();
  void on_createRecipeIngredientButton_clicked();
};

#endif // RECIPEFORM_H
