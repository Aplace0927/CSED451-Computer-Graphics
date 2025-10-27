#pragma once

#include "BBong/component.hpp"

template <typename T> T *BBong::Component::addComponent() {
  static_assert(std::is_base_of_v<BBong::Component, T>,
                "T must be a class derived from ComponentRoot");
  return gameObject->addComponent<T>();
}

template <typename T> T *BBong::Component::getComponent() {
  static_assert(std::is_base_of_v<BBong::Component, T>,
                "T must be a class derived from ComponentRoot");
  return gameObject->getComponent<T>();
}

template <typename T>
std::unique_ptr<BBong::Component>
BBong::ClonableComponent<T>::clone(GameObject *newOwner) const {
  const T *derived_this = dynamic_cast<const T *>(this);
  if (!derived_this) {
    return nullptr;
  }
  auto newComponent = std::make_unique<T>(*derived_this);

  newComponent->gameObject = newOwner;
  newComponent->transform = newOwner->transform;

  return newComponent;
}