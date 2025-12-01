/**
 * @file abstractstorable.h
 * @brief Abstract class that extends and defines member variables for the
 * Storable interface.
 */
#ifndef ABSTRACTSTORABLE_H
#define ABSTRACTSTORABLE_H

#include "storable.h"

#include <chrono>
#include <string>

/**
 * @brief Abstract class that outlines the member variables used by objects that
 * implement the Storable interface.
 *
 * There is no field to track soft deletion because there is no soft deletion of
 * data in the software. Since a user is expected to be responsible and manage
 * their recipes according to their real-world experience, deleting any content,
 * be it an ingredient, recipe or a whole profile is a hard deletion.
 *
 * @note This class is movable and copyable but cannot be assigned.
 * @see Storable
 */
class AbstractStorable : public Storable
{

  /**
   * @brief The unique identifier of the storable object.
   */
  std::string m_id;

  /**
   * @brief The unique identifier to the profile that created the
   * object.
   */
  std::string m_created_by_id;

  /**
   * @brief A timestamp of the creation date in the database..
   *
   * @note Using time_t to store unix time
   */
  time_t m_creation_date;

  /**
   * @brief A timestamp of the last time the object was updated.
   *
   * @note Using time_t to store unix time
   */
  time_t m_update_date;

  bool m_was_modified;

protected:
  /**
   * @brief Default constructor
   *
   * Use this constructor to construct decorators that wrap the Ingredient
   * class. The idea is that if you want to access any data members within the
   * Ingredient class, you should have the decorator class override this classes
   * getters/setters.
   */
  explicit AbstractStorable() = default;

  /**
   * @brief Constructor for creating new objects.
   *
   * @param identifier The unique ID for this object
   * @param created_by_id The profile ID that created this object
   */
  explicit AbstractStorable(std::string identifier, std::string created_by_id)
      : AbstractStorable(std::move(identifier), std::move(created_by_id),
                         std::chrono::system_clock::to_time_t(
                             std::chrono::system_clock::now()),
                         std::chrono::system_clock::to_time_t(
                             std::chrono::system_clock::now()),
                         false)
  {
  }

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
  explicit AbstractStorable(std::string identifier, std::string created_by_id,
                            time_t creation_date, time_t update_date,
                            bool was_modified = false)
      : m_id(std::move(identifier)), m_created_by_id(std::move(created_by_id)),
        m_creation_date(creation_date), m_update_date(update_date),
        m_was_modified(was_modified)
  {
  }

  AbstractStorable(const AbstractStorable &other) = default;
  auto operator=(const AbstractStorable &other) -> AbstractStorable & = default;
  AbstractStorable(AbstractStorable &&other) noexcept = default;
  auto operator=(AbstractStorable &&other) noexcept
      -> AbstractStorable & = default;

public:
  ~AbstractStorable() override
  {
    if (m_was_modified)
    {
      // Save this object to the database by force
    }
  }

  /**
   * @brief Getter for object id.
   *
   * If you're implementing a decorator class that wraps around the Ingredient
   * class, you should override these getters and setters to return the data
   * within the wrapped Ingredient object.
   */
  [[nodiscard]] virtual auto getId() const -> std::string { return m_id; }

  /**
   * @brief Getter for the id of the profile responsible for object creation.
   *
   * If you're implementing a decorator class that wraps around the Ingredient
   * class, you should override these getters and setters to return the data
   * within the wrapped Ingredient object.
   */
  [[nodiscard]] virtual auto getCreatedById() const -> std::string
  {
    return m_created_by_id;
  }

  /**
   * @brief Getter for the objects creation date and time in the database.
   *
   * If you're implementing a decorator class that wraps around the Ingredient
   * class, you should override these getters and setters to return the data
   * within the wrapped Ingredient object.
   */
  [[nodiscard]] virtual auto getCreationDate() const -> time_t
  {
    return m_creation_date;
  }

  /** @brief Getter for the objects update date and time in the database.
   *
   * If you're implementing a decorator class that wraps around the Ingredient
   * class, you should override these getters and setters to return the data
   * within the wrapped Ingredient object.
   */
  [[nodiscard]] virtual auto getUpdateDate() const -> time_t
  {
    return m_update_date;
  }

  /** @brief Getter to know if the object's data has been modified or not.
   *
   * If you're implementing a decorator class that wraps around the Ingredient
   * class, you should override these getters and setters to return the data
   * within the wrapped Ingredient object.
   */
  [[nodiscard]] virtual auto getWasModified() const -> bool
  {
    return m_was_modified;
  }

  /** @brief Setter for the objects update date and time. */
  virtual void setUpdateDate(time_t date)
  {
    m_update_date = date;
    modified();
  }

  /**
   * @brief Sets the was_modified field to true no matter the current state.
   *
   * Anytime a field is modified using a setter, the modified() function
   * should be called to let the object remember that it must save itself to the
   * database before desctruction.
   *
   * Marked as virtual so that any classes that eventually inherit from
   * AbstractStorable can act as decorators and change the modified status of
   * the object they decorate instead of themselves.
   */
  virtual void modified() { m_was_modified = true; }
};

#endif
