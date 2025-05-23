#include "textlist_field.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QVBoxLayout>
#include <qboxlayout.h>

TextListField::TextListField(const QString &field, const QString &label,
                             QWidget *parent)
    : FormField(parent), m_field(field), m_lineEdit(new QLineEdit),
      m_listDisplay(new QListWidget), m_addButton(new QPushButton),
      m_removeButton(new QPushButton) {

  QVBoxLayout *layout = new QVBoxLayout(this);
  layout->addWidget(new QLabel(label));
  layout->addWidget(m_lineEdit);
  layout->addWidget(m_listDisplay);

  QWidget *buttonswidget = new QWidget(this);
  QHBoxLayout *buttons = new QHBoxLayout(this);
  m_addButton->setText("Add");
  m_removeButton->setText("Remove");
  buttons->addWidget(m_addButton);
  buttons->addWidget(m_removeButton);
  buttonswidget->setLayout(buttons);

  layout->addWidget(buttonswidget);

  m_listDisplay->addItems(m_data);

  connect(m_addButton, &QPushButton::clicked, [this]() {
    m_data.push_back(this->m_lineEdit->text());
    qDebug() << "Added item '" << this->m_lineEdit->text() << "'";
    this->m_lineEdit->clear();

    this->updateDisplay();
    emit fieldChanged();
  });

  connect(m_removeButton, &QPushButton::clicked, [this]() {
    // Get selected items
    QList<QListWidgetItem *> selectedItems = m_listDisplay->selectedItems();

    // Remove them one by one
    for (QListWidgetItem *item : selectedItems) {
      qDebug() << "Removing item '" << m_listDisplay->row(item) << "'";
      m_data.removeAt(m_listDisplay->row(item));
      delete m_listDisplay->takeItem(m_listDisplay->row(item));
    }

    this->updateDisplay();
    emit fieldChanged();
  });
}

TextListField::TextListField(const QString &field, const QString &label,
                             bool allowedEmpty, QWidget *parent)
    : TextListField(field, label, parent) {
  m_allowedEmpty = allowedEmpty;
}

void TextListField::styleWidget() {}

void TextListField::updateDisplay() {
  m_listDisplay->clear();
  m_listDisplay->addItems(m_data);
}

bool TextListField::validate() {
  if (m_allowedEmpty) {
    return m_allowedEmpty;
  }

  return !m_data.isEmpty();
}

QVariantMap TextListField::getData() { return {{m_field, m_data}}; }

void TextListField::setAddButtonText(const QString &text) {
  m_addButton->setText(text);
}

void TextListField::setRemoveButtonText(const QString &text) {
  m_removeButton->setText(text);
}
