#include "shared_recipe.h"

QUuid SharedRecipe::getOriginalRecipeId() const { return original_recipe_id; }

QUuid SharedRecipe::getAuthorId() const { return author_id; }

quint32 SharedRecipe::getLikeCount() const { return like_count; }

// Add the recipe to a users likes, save that to the database, then increment
// the like count by 1 only if the user hadn't already liked the recipe
void SharedRecipe::addLike(QUuid user) { like_count++; }

// Remove the recipe from a users likes, remove the entry from the database,
// then decrement the like count by 1 if the user had liked the recipe
// previously
void SharedRecipe::removeLike(QUuid user) { like_count--; }
