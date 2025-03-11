#pragma once

#include "Graphics.h"

class GameObject
{
public:
    virtual ~GameObject() = default;
    virtual void Render(Graphics* graphics) {}
    virtual void Update() {}
};
