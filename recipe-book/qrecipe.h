#ifndef QRECIPE_H
#define QRECIPE_H

#include "qingredient.h"
#include "recipe.h"

class QRecipe : public QIngredient
{
    Q_OBJECT

    Q_PROPERTY(QStringList instructions READ getInstructions WRITE setInstructions NOTIFY instructionsChanged)
    Q_PROPERTY(QStringList equipment READ getEquipment WRITE setEquipment NOTIFY equipmentChanged)
    Q_PROPERTY(QString notes READ getNotes WRITE setNotes NOTIFY notesChanged)
    Q_PROPERTY(quint32 prepTime READ getPrepTime WRITE setPrepTime NOTIFY prepTimeChanged)
    // Q_PROPERTY(QList<QIngredient *> m_ingredients READ getIngredients WRITE setIngredients NOTIFY ingredientsChanged)

    Recipe m_recipe;
    QList<QIngredient *> m_ingredients;

public:
    explicit QRecipe(QObject *parent = nullptr);
    explicit QRecipe(QUuid id, QObject *parent = nullptr);
    explicit QRecipe(const QString &name,
                     const QString &description,
                     const QStringList &instructions,
                     const QStringList &equipment,
                     const QString &notes,
                     quint32 prepTime,
                     QObject *parent = nullptr);
    explicit QRecipe(const Recipe &recipe, QObject *parent = nullptr);

    ~QRecipe();

    QList<QIngredient *> getIngredients() const;
    QStringList getInstructions() const;
    QStringList getEquipment() const;
    QString getNotes() const;
    quint32 getPrepTime() const;

    void setIngredients(const QList<QIngredient *> &ingredients);
    void setInstructions(const QStringList &instructions);
    void setEquipment(const QStringList &equipment);
    void setNotes(const QString &notes);
    void setPrepTime(quint32 prepTime);

    // Q_INVOKABLE void addIngredient(QIngredient *ingredient);
    // Q_INVOKABLE void removeIngredient(QIngredient *ingredient);
    Q_INVOKABLE void addInstruction(const QString &instruction);
    Q_INVOKABLE void removeInstruction(const QString &instruction);
    Q_INVOKABLE void removeInstructionAt(int index);
    Q_INVOKABLE void addEquipment(const QString &equipment);
    Q_INVOKABLE void removeEquipment(const QString &equipment);
    Q_INVOKABLE void removeEquipmentAt(int index);

signals:
    void instructionsChanged();
    void equipmentChanged();
    void notesChanged();
    void prepTimeChanged();
    void ingredientsChanged();
};

#endif // QRECIPE_H
