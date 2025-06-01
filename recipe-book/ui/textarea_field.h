#ifndef TEXTAREA_FIELD_H
#define TEXTAREA_FIELD_H

#include "form_field.h"

#include <QLabel>
#include <QTextEdit>
#include <QtTypes>

class TextAreaField : public FormField {
  Q_OBJECT

  quint32 m_maxLength = 2048;
  QString m_field;
  QTextEdit *m_textEdit;

  void styleWidget() override;

public:
  explicit TextAreaField(const QString &field, const QString &label,
                         QWidget *parent = nullptr);

  bool validate() override;
  QVariantMap getData() override;

  void setMaxLength(quint32 maxLength);
};

#endif
