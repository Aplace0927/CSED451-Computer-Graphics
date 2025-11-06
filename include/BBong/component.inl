#ifndef BBONG_COMPONENT_INL
#define BBONG_COMPONENT_INL

#include "BBong/gameobject.hpp"

template <typename T> T *BBong::Component::addComponent() {
  static_assert(std::is_base_of_v<BBong::Component, T>,
                "T must be a class derived from Component");
  return gameObject->addComponent<T>();
}

template <typename T> T *BBong::Component::getComponent() {
  static_assert(std::is_base_of_v<BBong::Component, T>,
                "T must be a class derived from Component");
  return gameObject->getComponent<T>();
}

template <typename T>
std::unique_ptr<BBong::Component>
BBong::ClonableComponent<T>::clone(GameObject *newOwner) const {
  const T *derived_this = static_cast<const T *>(this);

  auto newComponent = std::make_unique<T>(*derived_this);

  newComponent->gameObject = newOwner;
  newComponent->transform = (newOwner) ? newOwner->transform : nullptr;

  return newComponent;
}

#endif // BBONG_COMPONENT_INL