#include "BBong/component.hpp"
#include "BBong/gameobject.hpp"
#include "BBong/transform.hpp"

namespace BBong {
Component::Component(GameObject *owner) : gameObject(owner), transform(owner ? owner->transform : nullptr) {}

bool Component::getActive() const { return gameObject->getActive(); }
void Component::setActive(bool state) { gameObject->setActive(state); }

void Component::doFixedUpdate() { fixedUpdate(); }
void Component::doCollision3D(Collider3D *collider) { collision3D(collider); }
void Component::doUpdate() { update(); }
void Component::doLateUpdate() { lateUpdate(); }
void Component::doRenderUpdate() { renderUpdate(); }
} // namespace BBong
