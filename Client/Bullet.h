#pragma once
#include "Interfaces.h"
#include "Utilities/Vector2D.h"

class Bullet : public GameObject
{
    float speed;

public:
    BOOL isAlive;
    Vector2D position;
    Vector2D firePosition;
    Vector2D velocity;
    float drag;
    
    D2D1_COLOR_F color;
    RECT playableArea;

    Bullet();
    Bullet(RECT playableArea, Vector2D firedPosition, Vector2D target);
    void Render(Graphics* graphics);
    void Update();
    void EnforceBoundingBox();
};
