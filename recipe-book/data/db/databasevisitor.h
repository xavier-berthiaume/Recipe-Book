#ifndef DATABASEVISITOR_H
#define DATABASEVISITOR_H

#include "../../database_visitor_fwd.h"

#include <QObject>

class QProfile;
class QIngredient;
class QRecipeIngredient;
class QRecipe;

class DatabaseVisitor : public QObject {
  Q_OBJECT

public:
  explicit DatabaseVisitor(QObject *parent = nullptr) : QObject(parent) {}
  virtual ~DatabaseVisitor() = default;

  virtual void visit(QProfile *) = 0;
  virtual void visit(QIngredient *) = 0;
  virtual void visit(QRecipeIngredient *) = 0;
  virtual void visit(QRecipe *) = 0;
};

#endif
