#include "recipe_form.h"

RecipeForm::RecipeForm(QWidget *parent)
    : QWidget(parent), m_recipeWrapper(nullptr) {
  setupUi();
  connectSignals();
}

RecipeForm::~RecipeForm() {
  // Cleanup if needed
}

void RecipeForm::setupUi() {
  m_mainLayout = new QFormLayout(this);

  // Basic information
  m_nameEdit = new QLineEdit(this);
  m_descriptionEdit = new QTextEdit(this);
  m_notesEdit = new QTextEdit(this);
  m_prepTimeSpin = new QSpinBox(this);
  m_prepTimeSpin->setSuffix(" mins");
  m_isSharedCheck = new QCheckBox("Shared", this);
  m_likeCountSpin = new QSpinBox(this);

  m_mainLayout->addRow("Name:", m_nameEdit);
  m_mainLayout->addRow("Description:", m_descriptionEdit);
  m_mainLayout->addRow("Preparation Time:", m_prepTimeSpin);
  m_mainLayout->addRow("Notes:", m_notesEdit);
  m_mainLayout->addRow(m_isSharedCheck);
  m_mainLayout->addRow("Likes:", m_likeCountSpin);

  // Instructions
  m_instructionsList = new QListWidget(this);
  m_newInstructionEdit = new QLineEdit(this);
  QPushButton *addInstructionBtn = new QPushButton("Add Instruction", this);
  QPushButton *removeInstructionBtn = new QPushButton("Remove Selected", this);

  QHBoxLayout *instructionBtnLayout = new QHBoxLayout();
  instructionBtnLayout->addWidget(addInstructionBtn);
  instructionBtnLayout->addWidget(removeInstructionBtn);

  m_mainLayout->addRow("Instructions:", m_instructionsList);
  m_mainLayout->addRow("New Instruction:", m_newInstructionEdit);
  m_mainLayout->addRow(instructionBtnLayout);

  // Equipment
  m_equipmentList = new QListWidget(this);
  m_newEquipmentEdit = new QLineEdit(this);
  QPushButton *addEquipmentBtn = new QPushButton("Add Equipment", this);
  QPushButton *removeEquipmentBtn = new QPushButton("Remove Selected", this);

  QHBoxLayout *equipmentBtnLayout = new QHBoxLayout();
  equipmentBtnLayout->addWidget(addEquipmentBtn);
  equipmentBtnLayout->addWidget(removeEquipmentBtn);

  m_mainLayout->addRow("Equipment:", m_equipmentList);
  m_mainLayout->addRow("New Equipment:", m_newEquipmentEdit);
  m_mainLayout->addRow(equipmentBtnLayout);

  // Submit button
  m_submitButton = new QPushButton("Create Recipe", this);
  m_mainLayout->addRow(m_submitButton);
}

void RecipeForm::connectSignals() {
  connect(m_submitButton, &QPushButton::clicked, this,
          &RecipeForm::handleSubmit);
  // Connect other buttons to their respective slots
}

void RecipeForm::handleSubmit() {
  // Create a new Recipe object
  Recipe recipe;

  // Create the wrapper
  m_recipeWrapper = new QtRecipeWrapper(recipe, this);

  // Set properties from form
  m_recipeWrapper->setName(m_nameEdit->text());
  m_recipeWrapper->setDescription(m_descriptionEdit->toPlainText());
  m_recipeWrapper->setNote(m_notesEdit->toPlainText());
  m_recipeWrapper->setPrepTime(m_prepTimeSpin->value());
  m_recipeWrapper->setIsShared(m_isSharedCheck->isChecked());
  m_recipeWrapper->setLikeCount(m_likeCountSpin->value());

  // Add instructions
  for (int i = 0; i < m_instructionsList->count(); ++i) {
    m_recipeWrapper->addInstruction(m_instructionsList->item(i)->text());
  }

  // Add equipment
  for (int i = 0; i < m_equipmentList->count(); ++i) {
    m_recipeWrapper->addEquipment(m_equipmentList->item(i)->text());
  }

  qDebug() << "Created Recipe with wrapper: " << m_recipeWrapper->getId();
  emit recipeCreated(m_recipeWrapper);
}

QtRecipeWrapper *RecipeForm::getRecipeWrapper() const {
  return m_recipeWrapper;
}

void RecipeForm::addInstruction() {}

void RecipeForm::removeInstruction() {}

void RecipeForm::addEquipment() {}

void RecipeForm::removeEquipment() {}
