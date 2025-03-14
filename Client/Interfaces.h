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
    // forces acting on the object
    // as of now they correspond to up, right, down, left, recoil;
    // TODO: dynamic list of forces
    Force2D forces[5] = {Force2D(), Force2D(), Force2D(), Force2D(), Force2D()};
    Vector2D position, velocity, net_force;
    
    virtual ~PhysicalGameObject() = default;
    PhysicalGameObject& UpdateVectors();
};

inline PhysicalGameObject& PhysicalGameObject::UpdateVectors()
{
    net_force.x = net_force.y = 0;
    for (auto& force : forces)
    {
        force.Update();
        net_force += force;
    }
    
    return *this;
}