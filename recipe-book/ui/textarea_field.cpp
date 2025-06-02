#include "textarea_field.h"

#include <QLabel>
#include <QVBoxLayout>

TextAreaField::TextAreaField(const QString &field, const QString &label,
                             QWidget *parent)
    : FormField(label, parent), m_field(field), m_textEdit(new QTextEdit) {

  QVBoxLayout *layout = new QVBoxLayout(this);
  layout->addWidget(m_label);
  layout->addWidget(m_textEdit);

  styleWidget();

  connect(m_textEdit, &QTextEdit::textChanged, [this]() {
    qDebug() << "Input has changed, valid status: " << validate();
    emit validChanged(validate());
  });
}

void TextAreaField::styleWidget() {
  // Set object names for more specific styling
  m_label->setObjectName("textAreaFieldLabel");

  // Main widget styling
  this->setStyleSheet(R"(
        TextAreaField {
            background: transparent;
            padding: 8px 0;
        }

        QLabel#textAreaFieldLabel {
            color: #424242;
            font-size: 28px;
            font-weight: 500;
            padding-bottom: 6px;
        }

    )");
}

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
