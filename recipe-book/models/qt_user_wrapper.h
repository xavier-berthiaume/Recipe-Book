#ifndef QT_USER_WRAPPER_H
#define QT_USER_WRAPPER_H

#include "qt_recipe_wrapper.h"
#include "storable.h"
#include "user.h"

#include <QObject>
#include <QString>
#include <QUuid>
#include <QVariantList>

class QtUserWrapper : public Storable {
  Q_OBJECT

  // Declare properties with proper accessors and signals
  Q_PROPERTY(QString username READ getUsername WRITE setUsername NOTIFY
                 usernameChanged)
  Q_PROPERTY(
      QString passwordHash READ getPasswordHash NOTIFY passwordHashChanged)
  Q_PROPERTY(QList<QtRecipeWrapper *> sharedRecipes READ getSharedRecipes NOTIFY
                 sharedRecipesChanged)

  User m_user; // The actual User instance being wrapped

  QList<QtRecipeWrapper *> m_sharedRecipes;

  // Converts between Recipe and QtRecipeWrapper
  QtRecipeWrapper *createWrapperForRecipe(const Recipe &recipe);

public:
  explicit QtUserWrapper(QObject *parent = nullptr);
  explicit QtUserWrapper(QUuid id, QObject *parent = nullptr);
  // Constructor for new user objects not yet in the database
  explicit QtUserWrapper(const User &user, QObject *parent = nullptr);

  ~QtUserWrapper();

  // Property accessors
  QString getUsername() const;
  void setUsername(const QString &username);

  QString getPasswordHash() const;

  QList<QtRecipeWrapper *> getSharedRecipes() const;

  // User functionality
  Q_INVOKABLE void setPassword(const QString &plainPassword);
  Q_INVOKABLE bool authenticate(const QString &password) const;

  Q_INVOKABLE void addSharedRecipe(const QtRecipeWrapper *recipe);
  Q_INVOKABLE void removeSharedRecipe(const QtRecipeWrapper *recipe);

signals:
  void usernameChanged();
  void passwordHashChanged();
  void sharedRecipesChanged();
};

#endif
