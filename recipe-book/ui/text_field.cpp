#include "text_field.h"

#include <QStyle>
#include <QVBoxLayout>

TextField::TextField(const QString &field, const QString &label,
                     QWidget *parent)
    : FormField(label, parent), m_field(field), m_lineEdit(new QLineEdit) {
  QVBoxLayout *layout = new QVBoxLayout(this);
  // this->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);

  m_label->setText(label);
  // m_label->setAlignment(Qt::AlignHCenter | Qt::AlignBottom);
  // m_label->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);

  layout->addWidget(m_label, 0, Qt::AlignHCenter);
  layout->addWidget(m_lineEdit, 0, Qt::AlignTop);

  styleWidget();

  connect(m_lineEdit, &QLineEdit::textChanged,
          [this]() { emit validChanged(validate()); });
}

void TextField::styleWidget() {
  // Set object names for more specific styling
  m_label->setObjectName("textFieldLabel");
  m_lineEdit->setObjectName("textFieldInput");

  m_label->setWordWrap(true);

  // Main widget styling
  this->setStyleSheet(R"(
        TextField {
            background: transparent;
            padding: 8px 0;
        }
        
        QLabel#textFieldLabel {
            color: #424242;
            font-size: 28px;
            font-weight: 500;
            padding-bottom: 6px;
        }
        
        QLineEdit#textFieldInput {
            border: 1px solid #e0e0e0;
            border-radius: 4px;
            padding: 10px 12px;
            font-size: 15px;
            background: white;
            selection-background-color: #4CAF50;
            selection-color: white;
            min-height: 36px;
        }
        
        QLineEdit#textFieldInput:focus {
            border: 2px solid #4CAF50;
            padding: 9px 11px; /* Adjust for thicker border */
        }
        
        QLineEdit#textFieldInput:disabled {
            background: #f5f5f5;
            color: #9e9e9e;
        }
        
        QLineEdit#textFieldInput[valid="true"] {
            border-color: #8BC34A;
        }
        
        QLineEdit#textFieldInput[valid="false"] {
            border-color: #f44336;
            background-color: #ffebee;
        }
    )");

  // Update style when validation changes
  connect(this, &TextField::validChanged, [this](bool valid) {
    m_lineEdit->setProperty("valid", valid);
    m_lineEdit->style()->unpolish(m_lineEdit);
    m_lineEdit->style()->polish(m_lineEdit);
  });
}

bool TextField::validate() { return !m_lineEdit->text().trimmed().isEmpty(); }

QVariantMap TextField::getData() { return {{m_field, m_lineEdit->text()}}; }
