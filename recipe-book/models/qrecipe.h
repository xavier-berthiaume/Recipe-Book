#ifndef QRECIPE_H
#define QRECIPE_H

#include "qingredient.h"

class QRecipe : public QIngredient {
  Q_OBJECT

  Q_PROPERTY(QString notes READ getNotes WRITE setNotes NOTIFY notesChanged)
  Q_PROPERTY(QList<QUuid> ingredientIds READ getIngredientIds WRITE
                 setIngredientIds NOTIFY ingredientIdsChanged)
  Q_PROPERTY(QStringList instructions READ getInstructions WRITE setInstructions
                 NOTIFY instructionsChanged)
  Q_PROPERTY(QStringList equipment READ getEquipment WRITE setEquipment NOTIFY
                 equipmentChanged)
  Q_PROPERTY(quint32 prepTime READ getPrepTime WRITE setPrepTime NOTIFY
                 prepTimeChanged)

public:
  // For creating objects
  QRecipe(const QString &name, const QString &description, const QString &notes,
          const QList<QUuid> &ingredientIds, const QStringList &instructions,
          const QStringList &equipment, quint32 prepTime,
          QObject *parent = nullptr);

  // For loading objects
  QRecipe(const QUuid &creatorId, const QString &name,
          const QString &description, const QString &notes,
          const QList<QUuid> &ingredientIds, const QStringList &instructions,
          const QStringList &equipment, quint32 prepTime,
          QObject *parent = nullptr);

  QString getNotes() const;
  QList<QUuid> getIngredientIds() const;
  QStringList getInstructions() const;
  QStringList getEquipment() const;
  quint32 getPrepTime() const;

signals:
  void notesChanged();
  void ingredientIdsChanged();
  void instructionsChanged();
  void equipmentChanged();
  void prepTimeChanged();
};

#endif
