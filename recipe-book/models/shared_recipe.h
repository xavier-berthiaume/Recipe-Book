#ifndef SHARED_RECIPE_H
#define SHARED_RECIPE_H

#include "storable.h"

#include <QString>
#include <QUuid>
#include <QtTypes>

class SharedRecipe : public Storable {

  QUuid original_recipe_id;
  QUuid author_id;
  quint32 like_count;

public:
  QUuid getOriginalRecipeId() const;
  QUuid getAuthorId() const;
  quint32 getLikeCount() const;

  void addLike(QUuid user);
  void removeLike(QUuid user);
};

#endif
