/**
 * @file storable.h
 * @brief Main interface that defines functionality required to interact with
 * the database layer.
 */
#ifndef STORABLE_H
#define STORABLE_H

#include <QObject>

class DatabaseVisitor;

/**
 * @brief Abstract base class defining the interface for persistent objects.
 *
 * The Storable class works with the DatabaseVisitor class for write operations
 * to the database. Implementing the visitor pattern this way simplifies object
 * storage by letting the object itself tell the DatabaseVisitor class its own
 * class type.
 *
 * The actual database operations are written in the derived DatabaseVisitor
 * class implementations.
 *
 * When copying or moving an object that inherits from Storable, the copy or
 * destination object will have the same parent as the original object.
 *
 * @note This class is movable and copyable.
 * @see DatabaseVisitor
 */
class Storable : public QObject {
  Q_OBJECT

protected:
  explicit Storable(QObject *parent = nullptr);

public:
  ~Storable() override = default;

  /** @brief Copy constructor */
  Storable(const Storable &other) : Storable(other.parent()) {}

  /** @brief Copy assignment operator */
  auto operator=(const Storable &other) noexcept -> Storable & {
    if (this != &other) {
      this->setParent(other.parent());
    }

    return *this;
  }

  /** @brief Move constructor */
  Storable(Storable &&other) noexcept : Storable(other.parent()) {}

  /** @brief Move assignment operator */
  auto operator=(Storable &&other) noexcept -> Storable & {
    if (this != &other) {
      this->setParent(other.parent());
    }

    return *this;
  }

  /**
   * @brief Classes that implement storable will have the acceptor function for
   * the database visitor pattern.
   */
  virtual void accept(DatabaseVisitor *visitor) = 0;
};

#endif
