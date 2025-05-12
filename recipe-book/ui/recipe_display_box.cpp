#include "recipe_display_box.h"

RecipeDisplayBox::RecipeDisplayBox(QWidget *parent)
    : GenericObjectDisplayBox(parent), m_name_label(new QLabel(this)),
      m_details_label(new QLabel(this)), m_stats_label(new QLabel(this)) {

  // Configure layout
  m_layout->addWidget(m_name_label);
  m_layout->addWidget(m_details_label);
  m_layout->addWidget(m_stats_label);

  // Style setup
  setStyleSheet("background: #f3e5f5; border: 2px solid #ba68c8;");
  m_name_label->setStyleSheet("font-weight: bold; color: #6a1b9a;");

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
  if (!m_wrapper)
    return;

  m_name_label->setText(m_wrapper->getName());
  m_details_label->setText(QString("%1 instructions • %2 equipment items")
                               .arg(m_wrapper->getInstructions().count())
                               .arg(m_wrapper->getEquipment().count()));

  m_stats_label->setText(QString("Prep time: %1 mins • Likes: %2")
                             .arg(m_wrapper->getPrepTime())
                             .arg(m_wrapper->getLikeCount()));
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
