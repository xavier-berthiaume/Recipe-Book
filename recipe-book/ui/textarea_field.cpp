#include "textarea_field.h"

#include <QLabel>
#include <QVBoxLayout>

TextAreaField::TextAreaField(const QString &field, const QString &label,
                             QWidget *parent)
    : FormField(parent), m_field(field), m_textEdit(new QTextEdit) {

  QVBoxLayout *layout = new QVBoxLayout(this);
  layout->addWidget(new QLabel(label));
  layout->addWidget(m_textEdit);

  connect(m_textEdit, &QTextEdit::textChanged,
          [this]() { emit validChanged(validate()); });
}

void TextAreaField::styleWidget() {}

bool TextAreaField::validate() {
  QString text = m_textEdit->toPlainText().trimmed();
  if (text.isEmpty())
    return false;
  if (text.length() > m_maxLength)
    return false;

  return true;
}

QVariantMap TextAreaField::getData() {
  return {{m_field, m_textEdit->toPlainText()}};
}

void TextAreaField::setMaxLength(quint32 maxLength) { m_maxLength = maxLength; }
