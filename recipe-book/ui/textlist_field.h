#ifndef TEXTLIST_FIELD
#define TEXTLIST_FIELD

#include "form_field.h"

#include <QLineEdit>
#include <QListWidget>
#include <QPushButton>

class TextListField : public FormField {
  Q_OBJECT

  QStringList m_data;
  QString m_field;
  QLineEdit *m_lineEdit;
  QListWidget *m_listDisplay;
  QPushButton *m_addButton;
  QPushButton *m_removeButton;

  bool m_allowedEmpty = true;

  void addTextLine();
  void removeTextLine(int position);

  void updateDisplay();
  void styleWidget() override;

public:
  explicit TextListField(const QString &field, const QString &label,
                         QWidget *parent = nullptr);

  explicit TextListField(const QString &field, const QString &label,
                         bool allowedEmpty, QWidget *parent = nullptr);

  bool validate() override;
  QVariantMap getData() override;

  void setAddButtonText(const QString &text);
  void setRemoveButtonText(const QString &text);

signals:
  void fieldChanged();
};

#endif
