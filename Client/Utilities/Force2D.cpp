#include "Force2D.h"
#include "Vector2D.h"

#include <algorithm>

Force2D::Force2D()
{
    unit_vector.x = unit_vector.y = 0;
    force_vec.x = force_vec.y = 0;
    life = 0;
    attack = magnitude = gain = release = 0;
    is_active = false;
}

Force2D::Force2D(
    Vector2D vector,
    float attack = 0,
    float gain = 0,
    float release = 0) : Force2D()
{
    this->magnitude = vector.magnitude();
    Vector2D unitVector = vector.normalize();
    this->unit_vector.x = unitVector.x * magnitude;
    this->unit_vector.y = unitVector.y * magnitude;
    force_vec.x = force_vec.x = 0;
    
    this->attack = attack;
    this->gain = gain;
    this->release = release;
    this->is_active = false;
}

Force2D::Force2D(
    Vector2D unitVector,
    float magnitude,
    float attack = 0,
    float gain = 0,
    float release = 0) : Force2D()
{
    unitVector = unitVector.normalize();
    this->unit_vector = {unitVector.x, unitVector.y};
    this->magnitude = std::max(0.0f, magnitude);
    force_vec.x = force_vec.y = 0;

    this->attack = attack;
    this->gain = gain;
    this->release = release;
    this->is_active = false;
}

Force2D& Force2D::Update()
{
    float actual_magnitude = force_vec.magnitude();

    if (!is_active)
    {
        if (actual_magnitude == .0f) { return *this; } // proclaim death

        // release phase
        float effectiveRelease = release > .0f ? release : magnitude;
        force_vec -= unit_vector * effectiveRelease;
        if (force_vec.normalize() == unit_vector * -1) { force_vec.x = force_vec.y = 0; }
        
        return *this;
    }

    float effectiveAttack = attack > .0f ? attack : magnitude;
    force_vec += unit_vector * (actual_magnitude < magnitude ? effectiveAttack : gain);
    return *this;
}

bool Force2D::operator==(const Force2D& rhs) const
{
    return this->force_vec == rhs.force_vec;
}

bool Force2D::operator!=(const Force2D& rhs) const
{
    return this->force_vec != rhs.force_vec;
}

Vector2D Force2D::operator+(const Force2D& force) const
{
    return unit_vector + force.unit_vector;
}

void Force2D::operator+=(const Force2D& force)
{
    this->unit_vector += force.unit_vector;
}

Vector2D Force2D::operator-(const Force2D& force) const
{
    return unit_vector - force.unit_vector;
}

void Force2D::operator-=(const Force2D& force)
{
    this->unit_vector -= force.unit_vector;
}
