#include "qt_user_wrapper.h"

#include <QCryptographicHash>
#include <QDebug>

QtUserWrapper::QtUserWrapper(QObject *parent) : Storable(parent) {}

QtUserWrapper::QtUserWrapper(QUuid id, QObject *parent)
    : Storable(id, parent) {}

QtUserWrapper::~QtUserWrapper() {
  // Cleanup if needed
}

QString QtUserWrapper::username() const {
  return QString::fromStdString(m_user.getUsername());
}

QString QtUserWrapper::passwordHash() const {
  return QString::fromStdString(m_user.getPasswordHash());
}

QVariantList QtUserWrapper::sharedRecipes() const {
  return m_sharedRecipesCache;
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

void QtUserWrapper::addSharedRecipe(const QVariant &recipe) {
  // Assuming recipe can be converted to your Recipe type
  // You'll need to implement this conversion
  Recipe r = recipe.value<Recipe>();
  m_user.addSharedRecipe(r);
  updateSharedRecipesCache();
  emit sharedRecipesChanged();
}

void QtUserWrapper::removeSharedRecipe(const QVariant &recipe) {
  // Assuming recipe can be converted to your Recipe type
  Recipe r = recipe.value<Recipe>();
  m_user.removeSharedRecipe(r);
  updateSharedRecipesCache();
  emit sharedRecipesChanged();
}

bool QtUserWrapper::authenticate(const QString &password) const {
  return m_user.authenticate(password.toStdString());
}

void QtUserWrapper::updateSharedRecipesCache() {
  m_sharedRecipesCache.clear();
  const auto &recipes = m_user.getSharedRecipes();
  for (const auto &recipe : recipes) {
    // Convert each Recipe to QVariant
    // You'll need to implement this conversion
    m_sharedRecipesCache.append(QVariant::fromValue(recipe));
  }
}
