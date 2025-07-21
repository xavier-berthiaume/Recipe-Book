#ifndef CAROUSEL_FORM_H
#define CAROUSEL_FORM_H

#include "form_field.h"

#include <QPushButton>
#include <QStackedWidget>

class CarouselForm : public QWidget {
  Q_OBJECT

  QStackedWidget *m_stack;
  QPushButton *m_prevBtn;
  QPushButton *m_nextBtn;
  QPushButton *m_cancelBtn;
  QList<FormField *> m_steps;
  int m_currentIndex = 0;

  void setupNavigation();
  void animateTransition(int newIndex);
  void updateButtons();

public:
  explicit CarouselForm(QWidget *parent = nullptr);

  void addFormStep(FormField *step);
  void showNext();
  void showPrevious();

public slots:
  void currentStepDataChanged();

signals:
  void formCompleted(const QVariantMap &data);
  void formCancelled();
};

#endif
