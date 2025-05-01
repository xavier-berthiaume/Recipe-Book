#include "qt_user_wrapper.h"
#include "qt_recipe_wrapper.h"

#include <QCryptographicHash>
#include <QDebug>

QtUserWrapper::QtUserWrapper(QObject *parent) : Storable(parent) {}

QtUserWrapper::QtUserWrapper(QUuid id, QObject *parent)
    : Storable(id, parent) {}

QtUserWrapper::QtUserWrapper(const User &user, QObject *parent)
    : Storable(QUuid::createUuid(), parent), m_user(user) {}

QtUserWrapper::~QtUserWrapper() {
  // Cleanup if needed
}

QString QtUserWrapper::getUsername() const {
  return QString::fromStdString(m_user.getUsername());
}

QString QtUserWrapper::getPasswordHash() const {
  return QString::fromStdString(m_user.getPasswordHash());
}

QList<QtRecipeWrapper *> QtUserWrapper::getSharedRecipes() const {
  return m_sharedRecipes;
}

void QtUserWrapper::setUsername(const QString &username) {
  std::string newUsername = username.toStdString();
  if (m_user.getUsername() != newUsername) {
    m_user.setUsername(newUsername);
    emit usernameChanged();
  }
}

void QtUserWrapper::setPassword(const QString &plainPassword) {
  QByteArray hash = QCryptographicHash::hash(plainPassword.toUtf8(),
                                             QCryptographicHash::Sha256);
  m_user.setPasswordHash(hash.toHex().toStdString());
  emit passwordHashChanged();
}

void QtUserWrapper::addSharedRecipe(const QtRecipeWrapper *recipe) {
  Recipe r = recipe->getRecipe();
  m_user.addSharedRecipe(r);
  // updateSharedRecipesCache();
  emit sharedRecipesChanged();
}

void QtUserWrapper::removeSharedRecipe(const QtRecipeWrapper *recipe) {
  // Assuming recipe can be converted to your Recipe type
  Recipe r = recipe->getRecipe();
  m_user.removeSharedRecipe(r);
  // updateSharedRecipesCache();
  emit sharedRecipesChanged();
}

bool QtUserWrapper::authenticate(const QString &password) const {
  return m_user.authenticate(password.toStdString());
}

QtRecipeWrapper *QtUserWrapper::createWrapperForRecipe(const Recipe &recipe) {
  return new QtRecipeWrapper(recipe, this);
}
