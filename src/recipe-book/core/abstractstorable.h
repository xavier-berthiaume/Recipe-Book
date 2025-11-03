/**
 * @file abstractstorable.h
 * @brief Abstract class that extends and defines member variables for the
 * Storable interface.
 */
#ifndef ABSTRACTSTORABLE_H
#define ABSTRACTSTORABLE_H

#include "storable.h"

#include <QDateTime>
#include <QUuid>

/**
 * @brief Abstract class that outlines the member variables used by objects that
 * implement the Storable interface.
 *
 * The following fields are added:
 * - m_id : The unique identifier of the storable object. Marked const since it
 * shouldn't be changed once set.
 * - m_created_by_id : The unique identifier to the profile that created the
 * object. Marked const since it shouldn't be changed once set.
 * - m_creation_date : A timestamp of the creation date in the database. This
 * field should be empty on creating a new object. Marked as const.
 * - m_update_date : A timestamp of the last time the object was updated. This
 * field should be empty on creating a new object.
 *
 * There is no field to track soft deletion because there is no soft deletion of
 * data in the software. Since a user is expected to be responsible and manage
 * their recipes according to their real-world experience, deleting any content,
 * be it an ingredient, recipe or a whole profile is a hard deletion.
 *
 * @note This class is movable and copyable.
 * @see Storable
 * @see Profile
 */
class AbstractStorable : public Storable {
  Q_OBJECT

  const QUuid m_id;
  const QUuid m_created_by_id;
  const QDateTime m_creation_date;
  QDateTime m_update_date;

protected:
  explicit AbstractStorable(QObject *parent = nullptr);

  /**
   * @brief Parametrized constructor.
   *
   * Creates the object based on all the fields passed. std::move is used for
   * the QDateTime parameters due to the fact that copying is non-trivial. The
   * QUuid parameters are passed by value.
   */
  explicit AbstractStorable(
      QUuid identifier, QUuid created_by_id,
      QDateTime creation_date = QDateTime::currentDateTime(),
      QDateTime update_date = QDateTime::currentDateTime(),
      QObject *parent = nullptr)
      : Storable(parent), m_id(identifier), m_created_by_id(created_by_id),
        m_creation_date(std::move(creation_date)),
        m_update_date(std::move(update_date)) {}

public:
  ~AbstractStorable() override = default;

  /** @brief Copy constructor */
  AbstractStorable(const AbstractStorable &other) noexcept
      : AbstractStorable(other.getId(), getCreatedByID(),
                         other.getCreationDate(), other.getUpdateDate(),
                         other.parent()) {}

  /** @brief Move constructor */
  AbstractStorable(AbstractStorable &&other) noexcept
      : AbstractStorable(other.getId(), getCreatedByID(),
                         other.getCreationDate(), other.getUpdateDate(),
                         other.parent()) {}

  /** @brief Deleted copy assignment operator */
  auto operator=(const AbstractStorable &) -> AbstractStorable = delete;

  /** @brief Move assignment operator */
  auto operator=(AbstractStorable &&other) noexcept
      -> AbstractStorable & = delete;

  /** @brief Getter for object id. */
  [[nodiscard]] auto getId() const -> QUuid { return m_id; }

  /** @brief Getter for the id of the profile responsible for object creation.
   */
  [[nodiscard]] auto getCreatedByID() const -> QUuid { return m_created_by_id; }

  /** @brief Getter for the objects creation date and time in the database. */
  [[nodiscard]] auto getCreationDate() const -> QDateTime {
    return m_creation_date;
  }

  /** @brief Getter for the objects update date and time in the database. */
  [[nodiscard]] auto getUpdateDate() const -> QDateTime {
    return m_update_date;
  }

  /** @brief Setter for the objects update date and time. */
  void setUpdateDate(const QDateTime &date) { m_update_date = date; }
};

#endif
