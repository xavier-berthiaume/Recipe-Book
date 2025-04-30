#ifndef QT_USER_WRAPPER_H
#define QT_USER_WRAPPER_H

#include "storable.h"
#include "user.h"

#include <QObject>
#include <QString>
#include <QUuid>
#include <QVariantList>

class QtUserWrapper : public Storable {
  Q_OBJECT

  // Declare properties with proper accessors and signals
  Q_PROPERTY(
      QString username READ username WRITE setUsername NOTIFY usernameChanged)
  Q_PROPERTY(QString passwordHash READ passwordHash NOTIFY passwordHashChanged)
  Q_PROPERTY(
      QVariantList sharedRecipes READ sharedRecipes NOTIFY sharedRecipesChanged)

public:
  explicit QtUserWrapper(QObject *parent = nullptr);
  explicit QtUserWrapper(QUuid id, QObject *parent = nullptr);

  ~QtUserWrapper();

  // Property accessors
  QString username() const;
  void setUsername(const QString &username);

  QString passwordHash() const;

  QVariantList sharedRecipes() const;

  // User functionality
  Q_INVOKABLE void setPassword(const QString &plainPassword);
  Q_INVOKABLE bool authenticate(const QString &password) const;
  Q_INVOKABLE void addSharedRecipe(const QVariant &recipe);
  Q_INVOKABLE void removeSharedRecipe(const QVariant &recipe);

signals:
  void usernameChanged();
  void passwordHashChanged();
  void sharedRecipesChanged();

private:
  User m_user; // The actual User instance being wrapped

  // Helper to convert between Recipe and QVariant
  QVariant recipeToVariant(const Recipe &recipe) const;
  Recipe variantToRecipe(const QVariant &variant) const;
};

#endif
