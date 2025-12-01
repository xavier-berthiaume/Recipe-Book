/**
 * @file abstractingredientdecorator.h
 * @brief The abstraction layer that defines the functionality of decorator
 * classes that wrap the Ingredient class.
 */
#ifndef ABSTRACTINGREDIENTDECORATOR_H
#define ABSTRACTINGREDIENTDECORATOR_H

#include "abstractingredient.h"
#include "ingredient.h"

#include <memory>

/**
 * @brief Interface that defines the functionality required of decorator classes
 * to the Ingredient class.
 *
 * To implement a decorator that extends the functionality of the Ingredient
 * class, extend this class and use its accessors and mutators.
 */
class AbstractIngredientDecorator : public AbstractIngredient
{
  std::unique_ptr<Ingredient> m_ingredient;

protected:
  explicit AbstractIngredientDecorator(std::unique_ptr<Ingredient> ingredient)
      : m_ingredient(std::move(ingredient))
  {
  }

  AbstractIngredientDecorator(const AbstractIngredientDecorator &other)
      : AbstractIngredient(other),
        m_ingredient(other.m_ingredient ? other.m_ingredient->clone() : nullptr)
  {
  }

  auto operator=(const AbstractIngredientDecorator &other)
      -> AbstractIngredientDecorator &
  {
    if (this != &other)
    {
      m_ingredient = other.m_ingredient ? other.m_ingredient->clone() : nullptr;
    }
    return *this;
  }

  AbstractIngredientDecorator(AbstractIngredientDecorator &&) noexcept =
      default;
  auto operator=(AbstractIngredientDecorator &&) noexcept
      -> AbstractIngredientDecorator & = default;

public:
  ~AbstractIngredientDecorator() override = default;

  // AbstractStorable Overrides

  /**
   * @brief Override of the getId() method of the AbstractStorable class.
   *
   * @return The Id of the base Ingredient object.
   * @see AbstractStorable
   */
  [[nodiscard]] auto getId() const -> std::string override
  {
    return m_ingredient->getId();
  }

  /**
   * @brief Override of the getCreatedById() method of the AbstractStorable
   * class.
   *
   * @return The Id of the user that created this object of the base Ingredient
   * object.
   * @see AbstractStorable
   */
  [[nodiscard]] auto getCreatedById() const -> std::string override
  {
    return m_ingredient->getCreatedById();
  }

  /**
   * @brief Override of the getCreationDate() method of the AbstractStorable
   * class.
   *
   * @return The creation date of the base Ingredient object.
   * @see AbstractStorable
   * @note The time is stored in unix time.
   */
  [[nodiscard]] auto getCreationDate() const -> time_t override
  {
    return m_ingredient->getCreationDate();
  }

  /**
   * @brief Override of the getUpdateDate() method of the AbstractStorable
   * class.
   *
   * @return The update date of the base Ingredient object.
   * @see AbstractStorable
   * @note The time is stored in unix time.
   */
  [[nodiscard]] auto getUpdateDate() const -> time_t override
  {
    return m_ingredient->getUpdateDate();
  }

  /**
   * @brief Override of the getWasModified() method of the AbstractStorable
   * class.
   *
   * @return The modified status of the base Ingredient object.
   * @see AbstractStorable
   */
  [[nodiscard]] auto getWasModified() const -> bool override
  {
    return m_ingredient->getWasModified();
  }

  void modified() override { m_ingredient->modified(); }

  void setUpdateDate(time_t date) override
  {
    m_ingredient->setUpdateDate(date);
  }

  void setName(std::string name) override { m_ingredient->setName(name); }

  [[nodiscard]] auto getName() const -> std::string override
  {
    return m_ingredient->getName();
  }

  void setDescription(std::string description) override
  {
    m_ingredient->setDescription(description);
  }

  [[nodiscard]] auto getDescription() const -> std::string override
  {
    return m_ingredient->getDescription();
  }

  void setFlavor(std::string flavor) override
  {
    m_ingredient->setFlavor(flavor);
  }

  [[nodiscard]] auto getFlavor() const -> std::string override
  {
    return m_ingredient->getFlavor();
  }

  [[nodiscard]] auto getInRecipeList() const
      -> std::vector<std::string> override
  {
    return m_ingredient->getInRecipeList();
  }
};

#endif
