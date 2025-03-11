#include "Bullet.h"
#include <math.h>

Bullet::Bullet()
{
    this->speed = 100.0f;
    this->drag = .05f;
    this->isAlive = false;
    this->velocity = {0, 0};
    this->firePosition = {0, 0};
    this->position = {0, 0};
    this->color = D2D1::ColorF(1.0f, 0.3f, 0.0f);
    this->playableArea = {};
}

Bullet::Bullet(RECT playableArea, Vector2D firedPosition, Vector2D target) : Bullet()
{
    this->playableArea = playableArea;
    this->isAlive = true;
    this->firePosition = firedPosition;
    this->position = firedPosition;
    this->color = D2D1::ColorF(1.0f, 1.0f, 0.0f);

    auto angle_vec = target - firePosition;
    auto angle_rad = atan2f(angle_vec.y, angle_vec.x);
    this->velocity = Vector2D(speed * cos(angle_rad), speed * sin(angle_rad));
}

void Bullet::Render(Graphics* graphics)
{
    if (!isAlive) { return; }
    graphics->DrawEllipse(position.x, position.y, 5, color);
}

void Bullet::Update()
{
    if (!isAlive) { return; }

    velocity *= 1 - drag;
    position += velocity;
    
    if (position.x > playableArea.right
        || position.y > playableArea.bottom
        || position.x < 0
        || position.y < 0)
        { isAlive = FALSE; }
}

void Bullet::EnforceBoundingBox()
{
    if (position.x < playableArea.left || position.x > playableArea.right) { velocity.x *= -1; }
    if (position.y < playableArea.top || position.y > playableArea.bottom) { velocity.y *= -1; }
}