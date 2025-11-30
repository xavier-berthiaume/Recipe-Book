/**
 * @file abstractingredient.h
 * @brief Defines the AbstractIngredient class, which is an interface that
 * defines ingredient behaviour.
 */
#ifndef ABSTRACTINGREDIENT_H
#define ABSTRACTINGREDIENT_H

#include "abstractstorable.h"

#include <memory>
#include <vector>

/**
 * @brief Interface that defines the various behaviours of ingredients.
 *
 * An object that needs to act as an ingredient must provide the following
 * functionality:
 * - A name
 * - A description
 * - Some flavor text (an origin, some history)
 */
class AbstractIngredient : public AbstractStorable {

protected:
  /**
   * @brief Default constructor
   */
  explicit AbstractIngredient() = default;

  /**
   * @brief Constructor for creating new objects
   *
   * @param identifier The unique ID for this object
   * @param created_by_id The profile ID that created this object
   */
  explicit AbstractIngredient(std::string identifier, std::string created_by_id)
      : AbstractStorable(std::move(identifier), std::move(created_by_id)) {}

  /**
   * @brief Parametrized constructor for loading existing objects.
   *
   * Creates the object based on all the fields passed from storage.
   *
   * @param identifier The unique ID for this object
   * @param created_by_id The profile ID that created this object
   * @param creation_date When the object was created in the database
   * @param update_date When the object was last updated
   * @param was_modified Whether the object has been modified since loading
   */
  explicit AbstractIngredient(std::string identifier, std::string created_by_id,
                              time_t creation_date, time_t update_date,
                              bool was_modified)
      : AbstractStorable(std::move(identifier), std::move(created_by_id),
                         creation_date, update_date, was_modified) {}

  AbstractIngredient(const AbstractIngredient &other) = default;
  auto operator=(const AbstractIngredient &other)
      -> AbstractIngredient & = default;
  AbstractIngredient(AbstractIngredient &&) noexcept = default;
  auto operator=(AbstractIngredient &&) noexcept
      -> AbstractIngredient & = default;

public:
  ~AbstractIngredient() override = default;

  virtual void setName(std::string) = 0;
  [[nodiscard]] virtual auto getName() const -> std::string = 0;

  virtual void setDescription(std::string) = 0;
  [[nodiscard]] virtual auto getDescription() const -> std::string = 0;

  virtual void setFlavor(std::string) = 0;
  [[nodiscard]] virtual auto getFlavor() const -> std::string = 0;

  /**
   * @brief Checks what recipes feature this ingredient
   *
   * @return A vector containing the Uuids of all recipes that contain this
   * ingredient
   */
  [[nodiscard]] virtual auto getInRecipeList() const
      -> std::vector<std::string> = 0;
};

#endif
