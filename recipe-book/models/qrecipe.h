#ifndef QRECIPE_H
#define QRECIPE_H

#include "qingredient.h"
#include "recipe.h"

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

  Recipe m_recipe;

  // These are just helper functions to help with managing the list attributes
  // being different between the Qt framework and pure C++. Eventually they
  // should be moved into their own class grouping static helper functions.
  template <typename T>
  static std::list<std::string> toStdList(const QList<T> &list);
  template <typename T>
  static QList<T> fromStdList(const std::list<std::string> &list);
  template <typename T>
  static bool compareListsWithoutDuplicates(const std::list<T> &list1,
                                            const std::list<T> &list2);

public:
  // For creating objects
  explicit QRecipe(const QUuid &creatorId, const QString &name,
                   const QString &description, const QString &notes,
                   const QList<QUuid> &ingredientIds,
                   const QStringList &instructions,
                   const QStringList &equipment, quint32 prepTime,
                   QObject *parent = nullptr);

  // For loading objects
  explicit QRecipe(const QUuid &id, const QUuid &creatorId, const QString &name,
                   const QString &description, const QString &notes,
                   const QList<QUuid> &ingredientIds,
                   const QStringList &instructions,
                   const QStringList &equipment, quint32 prepTime,
                   QObject *parent = nullptr);

  QUuid getCreatorId() const override;
  QString getName() const override;
  QString getDescription() const override;
  QString getNotes() const;
  QList<QUuid> getIngredientIds() const;
  QStringList getInstructions() const;
  QStringList getEquipment() const;
  quint32 getPrepTime() const;

  void setName(const QString &name) override;
  void setDescription(const QString &description) override;
  void setNotes(const QString &notes);
  void setIngredientIds(const QList<QUuid> &ingredientIds);
  void setInstructions(const QStringList &instructions);
  void setEquipment(const QStringList &equipment);
  void setPrepTime(quint32 prepTime);

  void addIngredientId(const QUuid &id);
  void removeIngredientId(const QUuid &id);

  void addInstruction(const QString &instruction);
  void removeInstruction(const QString &instruction);

  void addEquipment(const QString &equipment);
  void removeEquipment(const QString &equipment);

signals:
  void notesChanged();
  void ingredientIdsChanged();
  void instructionsChanged();
  void equipmentChanged();
  void prepTimeChanged();
};

#endif
