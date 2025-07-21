#include "qrecipe.h"
#include "qingredient.h"

#include <QSet>
#include <qtmetamacros.h>

template <typename T>
std::list<std::string> QRecipe::toStdList(const QList<T> &list) {
  std::list<std::string> convList;
  for (const T &item : list) {
    convList.push_back(item.toString().toStdString());
  }

  return convList;
}

template <>
std::list<std::string> QRecipe::toStdList<QString>(const QList<QString> &list) {
  std::list<std::string> convList;
  for (const QString &item : list) {
    convList.push_back(item.toStdString());
  }
  return convList;
}

template <>
QList<QString>
QRecipe::fromStdList<QString>(const std::list<std::string> &list) {
  QStringList convList;
  for (const std::string &item : list) {
    convList.push_back(QString::fromStdString(item));
  }

  return convList;
}

template <>
QList<QUuid> QRecipe::fromStdList<QUuid>(const std::list<std::string> &list) {
  QList<QUuid> convList;
  for (const std::string &item : list) {
    convList.push_back(QUuid::fromString(item));
  }

  return convList;
}

template <typename T>
bool QRecipe::compareListsWithoutDuplicates(const std::list<T> &list1,
                                            const std::list<T> &list2) {
  QSet<T> convSet(list1.begin(), list1.end());
  QSet<T> existingSet(list2.begin(), list2.end());

  if (convSet != existingSet)
    return false;

  return true;
}

QRecipe::QRecipe(const QUuid &creatorId, const QString &name,
                 const QString &description, const QString &notes,
                 const QList<QUuid> &ingredientIds,
                 const QStringList &instructions, const QStringList &equipment,
                 quint32 prepTime, QObject *parent)
    : QIngredient(creatorId, name, description, parent),
      m_recipe(creatorId.toString().toStdString(), name.toStdString(),
               description.toStdString(), notes.toStdString(),
               toStdList(ingredientIds), toStdList(instructions),
               toStdList(equipment), prepTime) {}

QRecipe::QRecipe(const QUuid &id, const QUuid &creatorId, const QString &name,
                 const QString &description, const QString &notes,
                 const QList<QUuid> &ingredientIds,
                 const QStringList &instructions, const QStringList &equipment,
                 quint32 prepTime, QObject *parent)
    : QIngredient(creatorId, name, description),
      m_recipe(creatorId.toString().toStdString(), name.toStdString(),
               description.toStdString(), notes.toStdString(),
               toStdList(ingredientIds), toStdList(instructions),
               toStdList(equipment), prepTime) {}

QUuid QRecipe::getCreatorId() const {
  return QUuid::fromString(QString::fromStdString(m_recipe.getCreatorId()));
}

QString QRecipe::getName() const {
  return QString::fromStdString(m_recipe.getName());
}

QString QRecipe::getDescription() const {
  return QString::fromStdString(m_recipe.getDescription());
}

QString QRecipe::getNotes() const {
  return QString::fromStdString(m_recipe.getNotes());
}

QList<QUuid> QRecipe::getIngredientIds() const {
  return fromStdList<QUuid>(m_recipe.getIngredientIds());
}

QStringList QRecipe::getInstructions() const {
  return fromStdList<QString>(m_recipe.getInstructions());
}

QStringList QRecipe::getEquipment() const {
  return fromStdList<QString>(m_recipe.getEquipment());
}

quint32 QRecipe::getPrepTime() const { return m_recipe.getPrepTime(); }

void QRecipe::setName(const QString &name) {
  if (name.toStdString() == m_recipe.getName())
    return;

  m_recipe.setName(name.toStdString());
  emit nameChanged();
}

void QRecipe::setDescription(const QString &description) {
  if (description.toStdString() == m_recipe.getDescription())
    return;

  m_recipe.setDescription(description.toStdString());
  emit descriptionChanged();
}

void QRecipe::setNotes(const QString &notes) {
  if (notes == QString::fromStdString(m_recipe.getNotes()))
    return;

  m_recipe.setNotes(notes.toStdString());
  emit notesChanged();
}

void QRecipe::setIngredientIds(const QList<QUuid> &ingredientIds) {
  std::list<std::string> convIds = toStdList(ingredientIds);

  if (compareListsWithoutDuplicates(convIds, m_recipe.getIngredientIds())) {
    m_recipe.setIngredientIds(convIds);
    emit ingredientIdsChanged();
  }
}

void QRecipe::setInstructions(const QStringList &instructions) {
  std::list<std::string> convInstructions = toStdList(instructions);

  if (compareListsWithoutDuplicates(convInstructions,
                                    m_recipe.getInstructions())) {
    m_recipe.setInstructions(convInstructions);
    emit instructionsChanged();
  }
}

void QRecipe::setEquipment(const QStringList &equipment) {
  std::list<std::string> convEquip = toStdList(equipment);

  if (compareListsWithoutDuplicates(convEquip, m_recipe.getEquipment())) {
    m_recipe.setEquipment(convEquip);
    emit equipmentChanged();
  }
}

void QRecipe::setPrepTime(quint32 prepTime) {
  if (m_recipe.getPrepTime() == prepTime)
    return;

  m_recipe.setPrepTime(prepTime);
  emit prepTimeChanged();
}

void QRecipe::addIngredientId(const QUuid &ingredientId) {
  if (ingredientId.isNull())
    return;

  m_recipe.addIngredientId(ingredientId.toString().toStdString());
  emit ingredientIdsChanged();
}

void QRecipe::removeIngredientId(const QUuid &ingredientId) {
  if (ingredientId.isNull())
    return;

  m_recipe.removeIngredientId(ingredientId.toString().toStdString());
  emit ingredientIdsChanged();
}

void QRecipe::addInstruction(const QString &instruction) {
  if (instruction.isEmpty())
    return;

  m_recipe.addInstruction(instruction.toStdString());
  emit instructionsChanged();
}

void QRecipe::removeInstruction(const QString &instruction) {
  if (instruction.isEmpty())
    return;

  m_recipe.removeInstruction(instruction.toStdString());
  emit instructionsChanged();
}

void QRecipe::addEquipment(const QString &equipment) {
  if (equipment.isEmpty())
    return;

  m_recipe.addEquipment(equipment.toStdString());
  emit equipmentChanged();
}

void QRecipe::removeEquipment(const QString &equipment) {
  if (equipment.isEmpty())
    return;

  m_recipe.removeEquipment(equipment.toStdString());
  emit equipmentChanged();
}
