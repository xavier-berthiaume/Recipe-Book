#ifndef PROFILEFORM_H
#define PROFILEFORM_H

#include "abstractform.h"

#include <QLineEdit>

namespace Ui {
class ProfileForm;
}

class ProfileForm : public AbstractForm {
  Q_OBJECT

  bool validateForm() override;
  void extractFormData() override;
  void populateForm(const QVariantMap &data) override;
  void clearForm() override;
  void initialize();

  Ui::ProfileForm *ui;
  QLineEdit *m_usernameEdit;

  explicit ProfileForm(Storable *object, QWidget *parent = nullptr);
  explicit ProfileForm(QWidget *parent = nullptr);

public:
  // We use factory methods here since they might need to call the virtual
  // function populateForm, and since it's being called in a partially
  // constructed object it can lead to undefined behaviour.
  static ProfileForm *createForm(QWidget *parent = nullptr);
  static ProfileForm *editForm(Storable *object, QWidget *parent = nullptr);

  ~ProfileForm();
};

#endif // PROFILEFORM_H
