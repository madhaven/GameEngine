#include "Force2D.h"
#include "Vector2D.h"

#include <algorithm>

Force2D::Force2D()
{
    direction.x = direction.y = 0;
    force.x = force.y = 0;
    life = 0;
    attack = magnitude = gain = release = 0;
    is_active = false;
}

Force2D::Force2D(
    Vector2D direction_vector,
    const float magnitude,
    const float attack,
    const float gain,
    const float release,
    const int max_life) : Force2D()
{
    this->direction = direction_vector.normalize();
    this->magnitude = std::max(.0f, magnitude);
    force.x = force.y = 0;

    this->attack = attack;
    this->gain = gain;
    this->release = release;
    this->is_active = false;
    this->max_life = max_life;
}

Force2D& Force2D::Update()
{
    if (max_life > 0 && life > max_life)
    {
        force = {0, 0};
        is_active = false;
        return *this;
    }
    
    float actual_magnitude = force.magnitude();

    if (is_active)
    {
        // attack/gain phase
        float effectiveAttack = attack > .0f ? attack : magnitude;
        force += direction * (actual_magnitude < magnitude ? effectiveAttack : gain);
    }
    else
    {
        if (actual_magnitude == .0f)
        {
            // proclaim death
            life = 0;
            return *this;
        }
        
        // release phase
        float effectiveRelease = release > .0f ? release : magnitude;
        force -= direction * effectiveRelease;
        if (force.normalize() == direction * -1) { force.x = force.y = 0; }
    }

    life += 1;
    return *this;
}

void Force2D::activate()
{
    is_active = true;
}

void Force2D::deactivate()
{
    is_active = false;
}

bool Force2D::operator==(const Force2D& rhs) const
{
    return this->force == rhs.force;
}

bool Force2D::operator!=(const Force2D& rhs) const
{
    return this->force != rhs.force;
}

Vector2D Force2D::operator+(const Force2D& force) const
{
    return direction + force.direction;
}

void Force2D::operator+=(const Force2D& force)
{
    this->direction += force.direction;
}

Vector2D Force2D::operator-(const Force2D& force) const
{
    return direction - force.direction;
}

void Force2D::operator-=(const Force2D& force)
{
    this->direction -= force.direction;
}
