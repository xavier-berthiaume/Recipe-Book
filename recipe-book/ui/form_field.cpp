#include "form_field.h"

FormField::FormField(QWidget *parent) : QWidget(parent), m_label(new QLabel) {}

FormField::FormField(const QString &label, QWidget *parent)
    : QWidget(parent), m_label(new QLabel(label, this)) {}

QString FormField::title() const { return m_title; }

void FormField::setTitle(const QString &title) { m_title = title; }

void FormField::setLabelText(const QString &label_text) {
  m_label->setText(label_text);
}
