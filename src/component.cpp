#include "BBong/component.hpp"
#include "BBong/gameobject.hpp"
#include "BBong/transform.hpp"

namespace BBong {
Component::Component(GameObject *owner) : gameObject(owner), transform(owner ? owner->transform : nullptr) {}

bool Component::getStatus() const { return gameObject->getActive(); }
void Component::setStatus(bool state) { gameObject->setActive(state); }

void Component::doFixedUpdate() { fixedUpdate(); }
void Component::doCollision() { collision(); }
void Component::doUpdate() { update(); }
void Component::doLateUpdate() { lateUpdate(); }
void Component::doRenderUpdate() { renderUpdate(); }
} // namespace BBong
