#include "ingredient_display_box.h"

IngredientDisplayBox::IngredientDisplayBox(QWidget *parent)
    : GenericObjectDisplayBox(parent), m_name_label(new QLabel(this)),
      m_description_label(new QLabel(this)) {

  m_layout->addWidget(m_name_label);
  m_layout->addWidget(m_description_label);

  // Initial style
  setFixedSize(300, 150);

  // Configure labels
  // I'm not sure satisfied with the elision for the description label. Will
  // revisit.
  m_name_label->setStyleSheet("font-weight: bold; font-size: 14pt;");
  m_name_label->setAlignment(Qt::AlignCenter);
  m_description_label->setTextFormat(Qt::PlainText);
  m_description_label->setWordWrap(true);
  m_description_label->setSizePolicy(QSizePolicy::Ignored,
                                     QSizePolicy::Preferred);
  m_description_label->setAlignment(Qt::AlignLeft | Qt::AlignTop);

  // Connect wrapper signals
  connect(this, &IngredientDisplayBox::wrapperChanged, [this]() {
    if (m_wrapper) {
      connect(m_wrapper, &QtIngredientWrapper::nameChanged, this,
              &IngredientDisplayBox::updateDisplay);
      connect(m_wrapper, &QtIngredientWrapper::descriptionChanged, this,
              &IngredientDisplayBox::updateDisplay);
    }
  });
}

void IngredientDisplayBox::updateDisplay() {
  if (!m_wrapper)
    return;

  m_name_label->setText(m_wrapper->getName());
  m_description_label->setText(m_wrapper->getDescription());

  // Update visual style based on properties
  if (m_wrapper->getIsRecipe()) {
    setStyleSheet("background: #e8f5e9; border: 2px solid #81c784;");
  } else {
    setStyleSheet("background: #fff3e0; border: 2px solid #ffb74d;");
  }
}

void IngredientDisplayBox::setWrapper(QtIngredientWrapper *wrapper) {
  m_wrapper = wrapper;

  if (m_wrapper) {
    connect(wrapper, &QtIngredientWrapper::destroyed, this,
            [this]() { m_wrapper = nullptr; });
    updateDisplay();
    emit wrapperChanged();
  }
}
