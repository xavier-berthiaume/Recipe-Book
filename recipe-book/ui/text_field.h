#ifndef TEXT_FIELD_H
#define TEXT_FIELD_H

#include "form_field.h"

#include <QLabel>
#include <QLineEdit>

class TextField : public FormField {
  Q_OBJECT

  QString m_field;
  QLabel *m_label;
  QLineEdit *m_lineEdit;

  void styleWidget() override;

public:
  explicit TextField(const QString &field, const QString &label,
                     QWidget *parent = nullptr);

  bool validate() override;
  QVariantMap getData() override;
};

#endif
