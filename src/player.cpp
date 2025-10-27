#include "player.hpp"

namespace BBong {
//void Player::update() {
//  if (gamestate == gamestate::lose) {
//    this->setstatus(false);
//    //healthbar.setstatus(false);
//    return;
//  }
//
//  shootingcooldown += utility::deltatime;
//  revivecooldown += utility::deltatime;
//
//  if (!getstatus() && revivecooldown >= gameconfig::revive_cooldown_time_sec) {
//    this->setstatus(true);
//  }
//
//  if (isshooting &&
//      shootingcooldown >= gameconfig::shooting_cooldown_time_sec) {
//    playerbullet *newbullet = bullets.acquire();
//    newbullet->activate(
//        transform->position + glm::vec3(0.0f, 17.3f, 0.0f),
//        bulletpattern::straight(glm::vec3(0, 1.0f, 0), 400.0f),
//        bullet::bullettype::player,
//        [this, newbullet]() { this->bullets.release(newbullet); },
//        bullethitdetectfunction, bullethiteventfunction);
//    shootingcooldown = 0;
//  }
//}
//
//void player::fixedupdate() {
//  if (!getstatus()) {
//    return;
//  }
//
//  transform->setposition(transform->position +
//                         direction * utility::fixeddeltatime);
//
//  glm::vec3 currentpos = getscenegraph()->getcenter();
//  boundingbox::boundingbox<glm::vec3> bdbx = getscenegraph()->getboundingbox(utility::getcurrenttimems());
//
//  setposition(
//      glm::vec3(glm::clamp(currentpos.x, gameconfig::position_left_limit,
//                           gameconfig::position_right_limit),
//                glm::clamp(currentpos.y, gameconfig::position_lower_limit,
//                           gameconfig::position_upper_limit),
//                currentpos.z));
//}
} // namespace Player