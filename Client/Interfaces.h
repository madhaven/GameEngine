#pragma once

#include "Graphics.h"
#include "Utilities/Force2D.h"
#include "Utilities/Vector2D.h"

class GameObject
{
public:
    virtual ~GameObject() = default;
    virtual void Render(Graphics* graphics) {}
    virtual void Update() {}
};

class PhysicalGameObject : public GameObject
{
public:
    Vector2D position, velocity, net_force;

    // forces acting on x, y and z(rotational) planes
    Force2D forces[5] = {Force2D(), Force2D(), Force2D()};
    
    virtual ~PhysicalGameObject() = default;
    virtual void UpdateNetForce();
    PhysicalGameObject& UpdateVectors();
};

inline void PhysicalGameObject::UpdateNetForce()
{
}

inline PhysicalGameObject& PhysicalGameObject::UpdateVectors()
{
    UpdateNetForce();
    velocity += net_force;
    position += velocity;
    return *this;
}