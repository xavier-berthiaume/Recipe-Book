#ifndef FORM_FIELD_H
#define FORM_FIELD_H

#include <QLabel>
#include <QVariantMap>
#include <QWidget>

class FormField : public QWidget {
  Q_OBJECT

protected:
  QString m_title;

  QLabel *m_label;

  virtual void styleWidget() = 0;

public:
  explicit FormField(QWidget *parent = nullptr);
  explicit FormField(const QString &label, QWidget *parent = nullptr);

  virtual bool validate() = 0;
  virtual QVariantMap getData() = 0;
  virtual QString title() const;

  void setTitle(const QString &title);
  void setLabelText(const QString &label_text);

signals:
  void validChanged(bool isValid);
};

#endif
