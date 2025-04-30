#ifndef QT_RECIPE_WRAPPER_H
#define QT_RECIPE_WRAPPER_H

#include "recipe.h"
#include "storable.h"

#include <QObject>
#include <QString>
#include <QStringList>
#include <QVariant>

class QtRecipeWrapper : public Storable {
  Q_OBJECT
  Q_PROPERTY(QString name READ getName WRITE setName NOTIFY nameChanged)
  Q_PROPERTY(QString description READ getDescription WRITE setDescription NOTIFY
                 descriptionChanged)
  Q_PROPERTY(
      QStringList instructions READ getInstructions NOTIFY instructionsChanged)
  Q_PROPERTY(QStringList equipment READ getEquipment NOTIFY equipmentChanged)
  Q_PROPERTY(QString notes READ getNotes WRITE setNote NOTIFY notesChanged)
  Q_PROPERTY(
      uint prepTime READ getPrepTime WRITE setPrepTime NOTIFY prepTimeChanged)
  Q_PROPERTY(
      bool isShared READ getIsShared WRITE setIsShared NOTIFY isSharedChanged)
  Q_PROPERTY(uint likeCount READ getLikeCount WRITE setLikeCount NOTIFY
                 likeCountChanged)

public:
  explicit QtRecipeWrapper(QObject *parent = nullptr);
  explicit QtRecipeWrapper(QUuid id, QObject *parent = nullptr);
  ~QtRecipeWrapper();

  // Property accessors
  QString getName() const;
  QString getDescription() const;
  QStringList getInstructions() const;
  QStringList getEquipment() const;
  QString getNotes() const;
  uint getPrepTime() const;
  bool getIsShared() const;
  uint getLikeCount() const;

  // Property setters
  void setName(const QString &name);
  void setDescription(const QString &description);
  void setNote(const QString &note);
  void setPrepTime(uint prep_time);
  void setIsShared(bool is_shared);
  void setLikeCount(uint like_count);

  // Wrapped Recipe functionality
  Q_INVOKABLE void addInstruction(const QString &instruction);
  Q_INVOKABLE void removeInstruction(const QString &instruction);
  Q_INVOKABLE void removeInstructionAt(int index);
  Q_INVOKABLE void addEquipment(const QString &equipment);
  Q_INVOKABLE void removeEquipment(const QString &equipment);
  Q_INVOKABLE void removeEquipmentAt(int index);
  Q_INVOKABLE void toggleShared();

signals:
  void nameChanged();
  void descriptionChanged();
  void instructionsChanged();
  void equipmentChanged();
  void notesChanged();
  void prepTimeChanged();
  void isSharedChanged();
  void likeCountChanged();

private:
  Recipe m_recipe; // The actual Recipe instance being wrapped
  QStringList m_instructionsCache;
  QStringList m_equipmentCache;

  void updateCaches();
};

#endif
