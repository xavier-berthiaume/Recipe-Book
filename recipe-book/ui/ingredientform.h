#ifndef INGREDIENTFORM_H
#define INGREDIENTFORM_H

#include "abstractform.h"

#include <QLineEdit>
#include <QPlainTextEdit>

namespace Ui {
class IngredientForm;
}

class IngredientForm : public AbstractForm {
  Q_OBJECT

  explicit IngredientForm(QWidget *parent = nullptr);
  explicit IngredientForm(Storable *object, QWidget *parent = nullptr);

  bool validateForm() override;
  void extractFormData() override;
  void populateForm(const QVariantMap &data) override;
  void clearForm() override;
  void initialize();

  QLineEdit *m_nameEdit;
  QPlainTextEdit *m_descriptionEdit;

  Ui::IngredientForm *ui;

public:
  static IngredientForm *createForm(QWidget *parent);
  static IngredientForm *editForm(Storable *object, QWidget *parent);

  ~IngredientForm();
};

#endif // INGREDIENTFORM_H
