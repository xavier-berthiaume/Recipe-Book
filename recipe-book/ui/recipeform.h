#ifndef RECIPEFORM_H
#define RECIPEFORM_H

#include "abstractform.h"

#include <QDialog>
#include <QLineEdit>
#include <QListView>
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

  QLineEdit *m_nameEdit;
  QPlainTextEdit *m_descriptionEdit;
  QPlainTextEdit *m_notesEdit;
  QLineEdit *m_instructionEdit;
  QToolButton *m_instructionRemove;
  QLineEdit *m_equipmentEdit;
  QToolButton *m_equipmentRemove;
  QListView *m_recipeIngredientList;

  Ui::RecipeForm *ui;

public:
  static RecipeForm *createForm(QWidget *parent);
  static RecipeForm *editForm(Storable *object, QWidget *parent);

  ~RecipeForm();
};

#endif // RECIPEFORM_H
