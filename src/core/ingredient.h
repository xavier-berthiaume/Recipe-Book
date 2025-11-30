/**
 * @file ingredient.h
 * @brief The main object type used in Recipe-Book. To add recipe functionality,
 * use the Recipe decorator class.
 * @see Recipe
 */
#ifndef INGREDIENT_H
#define INGREDIENT_H

#include "abstractingredient.h"

/**
 * @brief Core class that contains the most important information about every
 * stored piece of data in Recipe-Book.
 *
 * To extend functionality, create decorators that hold a pointer to an
 * Ingredient object and extend the AbstractIngredient class.
 */
class Ingredient : public AbstractIngredient {
  std::string m_name;

  std::string m_description;

  std::string m_flavor;

  std::vector<std::string> m_in_recipe_list;

public:
  /**
   * @brief Constructor for creating new objects
   *
   * @param identifier The unique ID for this object
   * @param created_by_id The profile ID that created this object
   * @param name The user created name of the ingredient
   * @param description The user created description of the ingredient
   * @param flavor The llm created flavor text for the ingredient
   */
  explicit Ingredient(std::string identifier, std::string created_by_id,
                      std::string name, std::string description,
                      std::string flavor);

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
   * @param name The user created name of the ingredient
   * @param description The user created description of the ingredient
   * @param flavor The llm created flavor text for the ingredient
   * @param in_recipe_list A list of the id's which feature this ingredient
   */
  explicit Ingredient(std::string identifier, std::string created_by_id,
                      time_t creation_date, time_t update_date,
                      bool was_modified, std::string name,
                      std::string description, std::string flavor,
                      std::vector<std::string> in_recipe_list);

  Ingredient(const Ingredient &other) = default;
  auto operator=(const Ingredient &other) -> Ingredient & = default;
  Ingredient(Ingredient &&) noexcept = default;
  auto operator=(Ingredient &&) noexcept -> Ingredient & = default;

  ~Ingredient() override = default;

  void setName(std::string name) override;
  [[nodiscard]] auto getName() const -> std::string override;

  void setDescription(std::string description) override;
  [[nodiscard]] auto getDescription() const -> std::string override;

  void setFlavor(std::string flavor) override;
  [[nodiscard]] auto getFlavor() const -> std::string override;

  [[nodiscard]] auto getInRecipeList() const
      -> std::vector<std::string> override;

  [[nodiscard]] auto clone() const -> std::unique_ptr<Ingredient>;

  void accept(DatabaseVisitor *visitor) override;
};

#endif
