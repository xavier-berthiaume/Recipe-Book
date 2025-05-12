#ifndef GENERIC_OBJECT_DISPLAY_BOX_H
#define GENERIC_OBJECT_DISPLAY_BOX_H

#include "display_box.h"

#include <QVBoxLayout>

template <typename T> class GenericObjectDisplayBox : public DisplayBox {

protected:
  T *m_wrapper; // The wrapped model object to display
  QVBoxLayout *m_layout;

  virtual void updateDisplay() = 0;

public:
  explicit GenericObjectDisplayBox(QWidget *parent = nullptr);

  virtual void setWrapper(T *wrapper) = 0;

  T *wrapper() const;
};

template <typename T>
GenericObjectDisplayBox<T>::GenericObjectDisplayBox(QWidget *parent)
    : DisplayBox(parent), m_layout(new QVBoxLayout(this)) {}

template <typename T> void GenericObjectDisplayBox<T>::setWrapper(T *wrapper) {
    if (m_wrapper)
        m_wrapper->disconnect(this);
    m_wrapper = wrapper;

    if (m_wrapper) {
        connect(wrapper, &T::destroyed, this, [this]() { m_wrapper = nullptr; });
        updateDisplay();
    }
}

template <typename T> T *GenericObjectDisplayBox<T>::wrapper() const {
    return m_wrapper;
}

#endif
