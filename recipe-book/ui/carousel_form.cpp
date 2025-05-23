#include "carousel_form.h"

#include <QHBoxLayout>
#include <QPropertyAnimation>
#include <QVBoxLayout>

CarouselForm::CarouselForm(QWidget *parent)
    : QWidget(parent), m_stack(new QStackedWidget(this)),
      m_prevBtn(new QPushButton("←", this)),
      m_nextBtn(new QPushButton("→", this)) {
  QHBoxLayout *mainLayout = new QHBoxLayout(this);
  QVBoxLayout *contentLayout = new QVBoxLayout;

  // Setup navigation buttons
  setupNavigation();

  // Layout structure
  mainLayout->addWidget(m_prevBtn, 0, Qt::AlignLeft | Qt::AlignVCenter);
  mainLayout->addLayout(contentLayout, 1);
  mainLayout->addWidget(m_nextBtn, 0, Qt::AlignRight | Qt::AlignVCenter);

  contentLayout->addWidget(m_stack, 0, Qt::AlignHCenter | Qt::AlignVCenter);
  m_stack->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

  setFixedSize(600, 400);
}

void CarouselForm::setupNavigation() {
  // Style navigation buttons
  m_prevBtn->setFixedSize(40, 40);
  m_nextBtn->setFixedSize(40, 40);

  m_prevBtn->setStyleSheet(R"(
    QPushButton {
        border-radius: 20px;
        font-size: 18px;
        background: #4CAF50;
        color: white;
    }
    QPushButton:disabled {
        background: #81C784;
    }
  )");

  m_nextBtn->setStyleSheet(m_prevBtn->styleSheet());

  // Style form container
  setStyleSheet(R"(
    CarouselForm {
        background: #F5F5F5;
        border-radius: 10px;
        border: 2px solid #BDBDBD;
    }
  )");

  connect(m_prevBtn, &QPushButton::pressed, this, &CarouselForm::showPrevious);
  connect(m_nextBtn, &QPushButton::pressed, this, &CarouselForm::showNext);
}

void CarouselForm::animateTransition(int newIndex) {
  const int direction = newIndex > m_currentIndex ? 1 : -1;
  const int offset = width();

  // Animate current widget out
  QWidget *currentWidget = m_stack->currentWidget();
  QPropertyAnimation *outAnim = new QPropertyAnimation(currentWidget, "pos");
  outAnim->setDuration(300);
  outAnim->setStartValue(currentWidget->pos());
  outAnim->setEndValue(QPoint(-direction * offset, 0));

  // Animate new widget in
  QWidget *newWidget = m_stack->widget(newIndex);
  newWidget->setGeometry(direction * offset, 0, width(), height());
  QPropertyAnimation *inAnim = new QPropertyAnimation(newWidget, "pos");
  inAnim->setDuration(300);
  inAnim->setStartValue(QPoint(direction * offset, 0));
  inAnim->setEndValue(QPoint(0, 0));

  // Update index when animation completes
  connect(inAnim, &QPropertyAnimation::finished, [this, newIndex]() {
    m_stack->setCurrentIndex(newIndex);
    m_currentIndex = newIndex;
    updateButtons();
  });

  outAnim->start();
  inAnim->start();
}

void CarouselForm::updateButtons() {
  bool hasSteps = !m_steps.isEmpty();
  bool isFirst = m_currentIndex == 0;
  bool isLast = m_currentIndex == m_steps.count() - 1;

  m_prevBtn->setEnabled(hasSteps && !isFirst);

  if (hasSteps) {
    bool currentStepValid = true;
    if (auto currentStep =
            qobject_cast<FormField *>(m_stack->currentWidget())) {
      currentStepValid = currentStep->validate();
    }
    m_nextBtn->setEnabled(currentStepValid);
    m_nextBtn->setText(isLast ? "✓" : "→");
  } else {
    m_nextBtn->setEnabled(false);
  }
}

void CarouselForm::addFormStep(FormField *step) {
  if (!step) {
    qWarning() << "Attempted to add null form step";
    return;
  }

  m_steps.append(step);
  m_stack->addWidget(step);

  connect(step, &FormField::validChanged, this, [this, step](bool valid) {
    // Enable/disable next button based on validation
    if (m_stack->currentWidget() == step) {
      m_nextBtn->setEnabled(valid && (m_currentIndex < m_steps.count() - 1));
    }
  });

  step->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

  if (m_steps.count() == 1) {
    m_stack->setCurrentIndex(0);
  }

  updateButtons();

  qDebug() << "Added form step successfully";
  qDebug() << QString("There are currently %1 steps").arg(m_steps.size());
}

void CarouselForm::showNext() {
  if (m_currentIndex >= m_steps.count() - 1) {
    // On last step - collect all data and emit completion
    QVariantMap formData;
    for (auto step : m_steps) {
      formData.insert(step->getData());
    }
    qDebug() << "Form successfully submitted with data " << formData;
    emit formCompleted(formData);
    return;
  }

  // Validate current step before proceeding
  if (auto currentStep = qobject_cast<FormField *>(m_stack->currentWidget())) {
    if (!currentStep->validate()) {
      return;
    }
  }

  animateTransition(m_currentIndex + 1);
}

void CarouselForm::showPrevious() {
  if (m_currentIndex <= 0)
    return;
  animateTransition(m_currentIndex - 1);
}

void CarouselForm::currentStepDataChanged() { updateButtons(); }
