#include "generic_object_display_box.h"

/*
 * THIS IS A DEPRECATED FILE, THE IMPLEMENTATIONS HERE HAVE BEEN MOVED TO THE HEADER FILE
 * TO SOLVE COMPILATION ISSUES

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

*/
