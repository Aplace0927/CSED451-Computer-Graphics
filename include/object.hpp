#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "shape.hpp"
#include "boundingbox.hpp"
#include "graphicsmanager.hpp"
#include "physicsmanager.hpp"

namespace Object {
    template <typename T, typename C>
    class Object {
    public:
        Object(
            const T  &_position,
            const Shape::Shape<T, C> &_shape,
            std::function<void()> releaseFunc = nullptr
        ): shape(_shape), releaseFunc(releaseFunc) {
            // Update to actual position (also initializes bounding box) 
            active = true;
            boundingBox = shape.move(_position);
            update_ptr = GraphicsManager::GraphicsManager::getInstance().registerHandler([this](time_t time) {this->update(time);});
            fixedUpdate_ptr = PhysicsManager::PhysicsManager::getInstance().registerHandler([this]() {this->fixedUpdate();});
        }
        ~Object() {
            GraphicsManager::GraphicsManager::getInstance().unregisterHandler(update_ptr);
            PhysicsManager::PhysicsManager::getInstance().unregisterHandler(fixedUpdate_ptr);
		}

        void setPosition(const T& position) {
            // Move by the difference between current center and new position
            boundingBox = shape.move(position - shape.getCenter());
        }

        void move(const T& displacement) {
            boundingBox = shape.move(displacement);
        }

        void rotate(const T& angles, const T& pivot) {
            boundingBox = shape.rotate(angles, pivot);
        }

        T getCenter() const {
            return shape.getCenter();
        }
        
        void draw() {
            shape.draw();
            #ifdef BOUNDING_BOX_DEBUG
            boundingBox.draw();
            #endif
        }

        bool getStatus() const { return active; }
        void setStatus(bool state) { active = state; }


        std::function<bool(const BoundingBox::BoundingBox<T>&)> getBoundingBoxCollisionFunction() {
            return [this](const BoundingBox::BoundingBox<T>& other) {
                return this->boundingBox & other;
            };
        }

        void setReleaseFunction(std::function<void()> func) {
            releaseFunc = func;
        }

        void callReleaseFunction() {
            if (releaseFunc != nullptr) {
                releaseFunc();
            }
        }

        Shape::Shape<T, C> getShape() const {
            return shape;
        }

        BoundingBox::BoundingBox<T> getBoundingBox() const {
            return boundingBox;
        }

        virtual void update(time_t time);
        virtual void fixedUpdate();
    private:
        bool active;
        Shape::Shape<T, C> shape;
        BoundingBox::BoundingBox<T> boundingBox;
        std::shared_ptr<std::function<void(time_t)>> update_ptr;
        std::shared_ptr<std::function<void()>> fixedUpdate_ptr;
        std::function<void()> releaseFunc;
    };

    template <typename T, typename C>
    void Object<T, C>::update(time_t time) {
        // Default implementation does nothing
    }

    template <typename T, typename C>
    void Object<T, C>::fixedUpdate() {
        // Default implementation does nothing
    }
}

#endif // OBJECT_HPP