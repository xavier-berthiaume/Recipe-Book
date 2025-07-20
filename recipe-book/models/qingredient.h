#ifndef QINGREDIENT_H
#define QINGREDIENT_H

#include "ingredient.h"
#include "storable.h"

class QIngredient : public Storable {
  Q_OBJECT

  Q_PROPERTY(QString name READ getName WRITE setName NOTIFY nameChanged)
  Q_PROPERTY(QString description READ getDescription WRITE setDescription NOTIFY
                 descriptionChanged)

  Ingredient m_ingredient;

public:
  // In this case we're using the factory to create a QIngredient with form data
  explicit QIngredient(const QString &name, const QString &description,
                       QObject *parent = nullptr);
  // In this case we're loading a QIngredient from the database
  explicit QIngredient(const QUuid &id, const QString &name,
                       const QString &description, QObject *parent = nullptr);

  QString getName() const;
  QString getDescription() const;

  void setName(const QString &name);
  void setDescription(const QString &description);

signals:
  void nameChanged();
  void descriptionChanged();
};

#endif
