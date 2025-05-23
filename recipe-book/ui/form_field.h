#ifndef FORM_FIELD_H
#define FORM_FIELD_H

#include <QVariantMap>
#include <QWidget>

class FormField : public QWidget {
  Q_OBJECT

protected:
  QString m_title;

  virtual void styleWidget() = 0;

public:
  explicit FormField(QWidget *parent = nullptr) : QWidget(parent) {}

  virtual bool validate() = 0;
  virtual QVariantMap getData() = 0;
  virtual QString title() const { return m_title; };

  void setTitle(const QString &title) { m_title = title; }

signals:
  void validChanged(bool isValid);
};

#endif
