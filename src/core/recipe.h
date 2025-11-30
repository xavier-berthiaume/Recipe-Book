/**
 * @file recipe.h
 * @brief Core class that wraps the Ingredient class as a decorator.
 *
 * The most important data relationship in this software is the notion that
 * everything is an ingredient at its core. If an ingredient requires steps to
 * create it, then this Recipe class wraps the core Ingredient object to define
 * what those steps are, as well as what other ingredients are required to make
 * it. This models the real-world reality of a recipe: it can also be used as a
 * basic ingredient within another recipe.
 */
#ifndef RECIPE_H
#define RECIPE_H

#include "core/abstractingredientdecorator.h"
#include "core/ingredient.h"

#include <vector>

class Recipe : public AbstractIngredientDecorator {
  std::vector<std::string> m_instructions;

public:
  /**
   * @brief Default constructor
   */
  explicit Recipe(std::unique_ptr<Ingredient> ingredient);

  /**
   * @brief Parametrized constructor
   */
  explicit Recipe(std::unique_ptr<Ingredient> ingredient,
                  std::vector<std::string> instructions);

  Recipe(const Recipe &other) = default;
  auto operator=(const Recipe &other) -> Recipe & = default;
  Recipe(Recipe &&other) noexcept = default;
  auto operator=(Recipe &&other) noexcept -> Recipe & = default;

  ~Recipe() override = default;

  [[nodiscard]] auto getInstructionsList() const -> std::vector<std::string>;

  /**
   * @brief Appends an instruction to the current instruction list.
   */
  void addInstruction(std::string instruction_text);

  /**
   * @brief Inserts an instruction in the current instruction list at the
   * specified position.
   */
  void addInstruction(int position, std::string instruction_text);

  /**
   * @brief Removes the instruction at the given position of the list.
   */
  void removeInstruction(int position);

  void accept(DatabaseVisitor *visitor) override;
};

#endif
