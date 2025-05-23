#include "recipe_display_box.h"
#include <qlogging.h>
#include <qnamespace.h>

RecipeDisplayBox::RecipeDisplayBox(QWidget *parent)
    : GenericObjectDisplayBox(parent), m_name_label(new QLabel(this)),
      m_details_label(new QLabel(this)), m_stats_label(new QLabel(this)),
      m_colorAnimation(new QPropertyAnimation(this, "backgroundColor")) {

  // Color animation setup
  m_colorAnimation->setDuration(150);
  m_colorAnimation->setEasingCurve(QEasingCurve::OutQuad);

  // Initial style
  setFixedSize(300, 200);
  setBackgroundColor(m_normalColor);
  setStyleSheet(R"(
    RecipeDisplayBox {
        border-radius: 8px;
        border: 1px solid #ba68c8;
        padding: 10px;
        transition: all 0.2s ease;
    }

    RecipeDisplayBox QLabel {
        color: #4a148c;
        border: 2px solid #0099ff;
    }

    RecipeDisplayBox QLabel#nameLabel {
        font-weight: bold;
        font-size: 14pt;
    }
  )");

  // Configure layout
  m_layout->addWidget(m_name_label);
  m_layout->addWidget(m_details_label);
  m_layout->addWidget(m_stats_label);

  // Configure labels
  m_name_label->setStyleSheet("font-weight: bold; color: #6a1b9a;");
  m_name_label->setAlignment(Qt::AlignCenter);
  m_details_label->setAlignment(Qt::AlignCenter);
  m_stats_label->setAlignment(Qt::AlignCenter);

  // Connect wrapper signals
  connect(this, &RecipeDisplayBox::wrapperChanged, [this]() {
    if (m_wrapper) {
      connect(m_wrapper, &QtRecipeWrapper::nameChanged, this,
              &RecipeDisplayBox::updateDisplay);
      connect(m_wrapper, &QtRecipeWrapper::instructionsChanged, this,
              &RecipeDisplayBox::updateDisplay);
      connect(m_wrapper, &QtRecipeWrapper::equipmentChanged, this,
              &RecipeDisplayBox::updateDisplay);
      connect(m_wrapper, &QtRecipeWrapper::prepTimeChanged, this,
              &RecipeDisplayBox::updateDisplay);
      connect(m_wrapper, &QtRecipeWrapper::likeCountChanged, this,
              &RecipeDisplayBox::updateDisplay);
    }
  });
}

void RecipeDisplayBox::updateDisplay() {
  if (!m_wrapper) {
    m_name_label->clear();
    m_details_label->clear();
    m_stats_label->clear();
    return;
  }

  m_name_label->setText(m_wrapper->getName());
  m_details_label->setText(QString("%1 instructions • %2 equipment items")
                               .arg(m_wrapper->getInstructions().count())
                               .arg(m_wrapper->getEquipment().count()));

  m_stats_label->setText(QString("Prep time: %1 mins • Likes: %2")
                             .arg(m_wrapper->getPrepTime())
                             .arg(m_wrapper->getLikeCount()));
}

void RecipeDisplayBox::enterEvent(QEnterEvent *event) {
  GenericObjectDisplayBox::enterEvent(event);

  m_colorAnimation->stop();
  m_colorAnimation->setStartValue(backgroundColor());
  m_colorAnimation->setEndValue(m_hoverColor);
  m_colorAnimation->start();

  // Enhance shadow on hover
  graphicsEffect()->setEnabled(true);
  static_cast<QGraphicsDropShadowEffect *>(graphicsEffect())->setBlurRadius(20);
  static_cast<QGraphicsDropShadowEffect *>(graphicsEffect())
      ->setColor(QColor(0, 0, 0, 100));
}

void RecipeDisplayBox::leaveEvent(QEvent *event) {
  GenericObjectDisplayBox::leaveEvent(event);

  m_colorAnimation->stop();
  m_colorAnimation->setStartValue(backgroundColor());
  m_colorAnimation->setEndValue(m_normalColor);
  m_colorAnimation->start();

  // Restore shadow
  static_cast<QGraphicsDropShadowEffect *>(graphicsEffect())->setBlurRadius(10);
  static_cast<QGraphicsDropShadowEffect *>(graphicsEffect())
      ->setColor(QColor(0, 0, 0, 60));
}

void RecipeDisplayBox::mousePressEvent(QMouseEvent *event) {
  if (event->button() == Qt::LeftButton) {
    m_pressed = true;
    // Visual feedback for press
    setBackgroundColor(backgroundColor().darker(110));
  }
  QWidget::mousePressEvent(event);
}

void RecipeDisplayBox::mouseReleaseEvent(QMouseEvent *event) {
  if (m_pressed && event->button() == Qt::LeftButton) {
    m_pressed = false;
    setBackgroundColor(backgroundColor());

    if (rect().contains(event->pos())) {
      qDebug() << "Recipe " << m_wrapper->getId().toString() << " clicked";
      emit clicked(); // Only emit if released inside box
    }
  }
  QWidget::mouseReleaseEvent(event);
}

QColor RecipeDisplayBox::hoverColor() const { return m_hoverColor; }

void RecipeDisplayBox::setHoverColor(const QColor &color) {
  m_hoverColor = color;
}

void RecipeDisplayBox::setWrapper(QtRecipeWrapper *wrapper) {
  m_wrapper = wrapper;

  if (m_wrapper) {
    connect(wrapper, &QtRecipeWrapper::destroyed, this,
            [this]() { m_wrapper = nullptr; });
    updateDisplay();
    emit wrapperChanged();
  }
}
