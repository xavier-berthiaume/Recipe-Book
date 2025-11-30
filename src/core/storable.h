/**
 * @file storable.h
 * @brief Main interface that defines functionality required to interact with
 * the database layer.
 */
#ifndef STORABLE_H
#define STORABLE_H

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
 * @note This class is movable and copyable and can be assigned.
 * @see DatabaseVisitor
 */
class Storable {

protected:
  explicit Storable() = default;

  Storable(const Storable &) = default;
  auto operator=(const Storable &) -> Storable & = default;
  Storable(Storable &&) noexcept = default;
  auto operator=(Storable &&) noexcept -> Storable & = default;

public:
  virtual ~Storable() = default;

  /**
   * @brief Classes that implement storable will have the acceptor function for
   * the database visitor pattern.
   */
  virtual void accept(DatabaseVisitor *visitor) = 0;
};

#endif
