#include "qrecipe.h"

QRecipe::QRecipe(QObject *parent)
    : QIngredient(m_recipe, parent)
{}

// Not sure I'll keep this kind of constructor with just the id passed
QRecipe::QRecipe(QUuid id, QObject *parent)
    : QIngredient(parent) {}

QRecipe::QRecipe(const QString &name,
                 const QString &description,
                 const QList<QRecipeIngredient *> &ingredients,
                 const QStringList &instructions,
                 const QStringList &equipment,
                 const QString &notes,
                 quint32 prepTime,
                 QObject *parent)
    : QIngredient(name, description, parent)
{
    std::vector<std::string> stdInstructions;
    std::vector<std::string> stdEquipment;

    for (const QString &it : instructions) {
        stdInstructions.push_back(it.toStdString());
    }

    for (const QString &eq : equipment) {
        stdEquipment.push_back(eq.toStdString());
    }

    m_recipe = Recipe(name.toStdString(),
                      description.toStdString(),
                      stdInstructions,
                      stdEquipment,
                      notes.toStdString(),
                      prepTime);

    m_ingredients = ingredients;
}

QRecipe::QRecipe(const Recipe &recipe,
                 QObject *parent)
    : QIngredient(recipe, parent)
    , m_recipe(recipe)
{}

QRecipe::~QRecipe() {}

QList<QRecipeIngredient *> QRecipe::getIngredients() const {
    return m_ingredients;
}

QStringList QRecipe::getInstructions() const {
    QStringList instructions;

    for (const std::string &it : m_recipe.getInstructions()) {
        instructions.push_back(QString::fromStdString(it));
    }

    return instructions;
}

QStringList QRecipe::getEquipment() const {
    QStringList equipment;

    for (const std::string &eq : m_recipe.getEquipment()) {
        equipment.push_back(QString::fromStdString(eq));
    }

    return equipment;
}

QString QRecipe::getNotes() const {
    return QString::fromStdString(m_recipe.getNotes());
}

quint32 QRecipe::getPrepTime() const {
    return m_recipe.getPrepTime();
}

void QRecipe::setIngredients(const QList<QRecipeIngredient *> &ingredients) {
    m_ingredients = ingredients;
    emit ingredientsChanged();
}

void QRecipe::setInstructions(const QStringList &instructions) {
    std::vector<std::string> stdInstructions;

    for (const QString &instruction : instructions) {
        stdInstructions.push_back(instruction.toStdString());
    }

    m_recipe.setInstructions(stdInstructions);

    emit instructionsChanged();
}

void QRecipe::addIngredient(QRecipeIngredient *ingredient) {
    if (ingredient == nullptr) return;

    m_ingredients.push_back(ingredient);
    emit ingredientsChanged();
}

void QRecipe::removeIngredient(QRecipeIngredient *ingredient) {
    if (ingredient == nullptr) return;

    for (int i = 0; i < m_ingredients.size(); i++) {
        if (m_ingredients[i] == ingredient)
            m_ingredients.removeAt(i);
    }
    emit ingredientsChanged();
}

void QRecipe::addInstruction(const QString &instruction) {
    if (instruction.isEmpty()) return;

    m_recipe.addInstruction(instruction.toStdString());
    emit instructionsChanged();
}

void QRecipe::removeInstruction(const QString &instruction) {
    if (instruction.isEmpty()) return;

    m_recipe.removeInstruction(instruction.toStdString());
    emit instructionsChanged();
}

void QRecipe::removeInstructionAt(int index) {
    if (index < 0 || index >= getInstructions().size()) return;

    m_recipe.removeInstruction(index);
    emit instructionsChanged();
}

void QRecipe::setEquipment(const QStringList &equipment) {
    std::vector<std::string> stdEquipment;

    for (const QString &eq : equipment) {
        stdEquipment.push_back(eq.toStdString());
    }

    m_recipe.setEquipment(stdEquipment);
    emit equipmentChanged();
}

void QRecipe::addEquipment(const QString &equipment) {
    if (equipment.isEmpty()) return;

    m_recipe.addEquipment(equipment.toStdString());
    emit equipmentChanged();
}

void QRecipe::removeEquipment(const QString &equipment) {
    if (equipment.isEmpty()) return;

    m_recipe.removeEquipment(equipment.toStdString());
    emit equipmentChanged();
}

void QRecipe::removeEquipmentAt(int index) {
    if (index < 0 || index >= getEquipment().size()) return;

    m_recipe.removeEquipment(index);
}

void QRecipe::setNotes(const QString &notes) {
    m_recipe.setNotes(notes.toStdString());
}

void QRecipe::setPrepTime(quint32 prepTime) {
    m_recipe.setPrepTime(prepTime);
}
