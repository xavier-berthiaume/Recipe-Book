#include "qt_recipe_wrapper.h"

#include <QDebug>

QtRecipeWrapper::QtRecipeWrapper(QObject *parent) : Storable(parent) {
  updateCaches();
}

QtRecipeWrapper::QtRecipeWrapper(QUuid id, QObject *parent)
    : Storable(id, parent) {
  updateCaches();
}

QtRecipeWrapper::~QtRecipeWrapper() {}

// Property accessors
QString QtRecipeWrapper::getName() const {
  return QString::fromStdString(m_recipe.getName());
}

QString QtRecipeWrapper::getDescription() const {
  return QString::fromStdString(m_recipe.getDescription());
}

QStringList QtRecipeWrapper::getInstructions() const {
  return m_instructionsCache;
}

QStringList QtRecipeWrapper::getEquipment() const { return m_equipmentCache; }

QString QtRecipeWrapper::getNotes() const {
  return QString::fromStdString(m_recipe.getNotes());
}

uint QtRecipeWrapper::getPrepTime() const { return m_recipe.getPrepTime(); }

bool QtRecipeWrapper::getIsShared() const { return m_recipe.getIsShared(); }

uint QtRecipeWrapper::getLikeCount() const { return m_recipe.getLikeCount(); }

// Property setters
void QtRecipeWrapper::setName(const QString &name) {
  std::string newName = name.toStdString();
  if (m_recipe.getName() != newName) {
    m_recipe.setName(newName);
    emit nameChanged();
  }
}

void QtRecipeWrapper::setDescription(const QString &description) {
  std::string newDesc = description.toStdString();
  if (m_recipe.getDescription() != newDesc) {
    m_recipe.setDescription(newDesc);
    emit descriptionChanged();
  }
}

void QtRecipeWrapper::setNote(const QString &note) {
  std::string newNote = note.toStdString();
  if (m_recipe.getNotes() != newNote) {
    m_recipe.setNote(newNote);
    emit notesChanged();
  }
}

void QtRecipeWrapper::setPrepTime(uint prep_time) {
  if (m_recipe.getPrepTime() != prep_time) {
    m_recipe.setPrepTime(prep_time);
    emit prepTimeChanged();
  }
}

void QtRecipeWrapper::setIsShared(bool is_shared) {
  if (m_recipe.getIsShared() != is_shared) {
    m_recipe.setIsShared(is_shared);
    emit isSharedChanged();
  }
}

void QtRecipeWrapper::setLikeCount(uint like_count) {
  if (m_recipe.getLikeCount() != like_count) {
    m_recipe.setLikeCount(like_count);
    emit likeCountChanged();
  }
}

// Wrapped Recipe functionality
void QtRecipeWrapper::addInstruction(const QString &instruction) {
  m_recipe.addInstruction(instruction.toStdString());
  updateCaches();
  emit instructionsChanged();
}

void QtRecipeWrapper::removeInstruction(const QString &instruction) {
  m_recipe.removeInstruction(instruction.toStdString());
  updateCaches();
  emit instructionsChanged();
}

void QtRecipeWrapper::removeInstructionAt(int index) {
  m_recipe.removeInstruction(index);
  updateCaches();
  emit instructionsChanged();
}

void QtRecipeWrapper::addEquipment(const QString &equipment) {
  m_recipe.addEquipment(equipment.toStdString());
  updateCaches();
  emit equipmentChanged();
}

void QtRecipeWrapper::removeEquipment(const QString &equipment) {
  m_recipe.removeEquipment(equipment.toStdString());
  updateCaches();
  emit equipmentChanged();
}

void QtRecipeWrapper::removeEquipmentAt(int index) {
  m_recipe.removeEquipment(index);
  updateCaches();
  emit equipmentChanged();
}

void QtRecipeWrapper::toggleShared() {
  m_recipe.toggleShared();
  updateCaches();
  emit isSharedChanged();
}

void QtRecipeWrapper::updateCaches() {
  // Update instructions cache
  m_instructionsCache.clear();
  const auto &instructions = m_recipe.getInstructions();
  for (const auto &instruction : instructions) {
    m_instructionsCache.append(QString::fromStdString(instruction));
  }

  // Update equipment cache
  m_equipmentCache.clear();
  const auto &equipment = m_recipe.getEquipment();
  for (const auto &item : equipment) {
    m_equipmentCache.append(QString::fromStdString(item));
  }
}
