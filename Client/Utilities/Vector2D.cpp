#include "Vector2D.h"
#include "Force2D.h"
#include "cmath"

Vector2D::Vector2D()
{
    this->x = 0;
    this->y = 0;
}

Vector2D::Vector2D(float x, float y)
{
    this->x = x;
    this->y = y;
}

Vector2D::Vector2D(const Vector2D& vector)
{
    this->x = vector.x;
    this->y = vector.y;
}

Vector2D Vector2D::normalize() const
{
    if (x == .0f && y == .0f) { return *this; }
    float magnitude = sqrt(x * x + y * y);
    return {x / magnitude, y / magnitude};
}

float Vector2D::magnitude() const
{
    if (this->x == 0 && this->y == 0)
        return 0;
    return sqrt(x * x + y * y);
}

bool Vector2D::operator==(const Vector2D& rhs) const
{
    return this->x == rhs.x && this->y == rhs.y;
}

bool Vector2D::operator!=(const Vector2D& rhs) const
{
    return this->x != rhs.x || this->y != rhs.y;
}

Vector2D Vector2D::operator+(const float rhs) const
{
    return {this->x + rhs, this->y + rhs};
}

Vector2D Vector2D::operator+(const Vector2D& rhs) const
{
    return {this->x + rhs.x, this->y + rhs.y};
}

Vector2D Vector2D::operator+(Force2D& force) const
{
    return { x + force.force.x, y + force.force.y };
}

Vector2D Vector2D::operator+=(const float rhs)
{
    this->x += rhs;
    this->y += rhs;
    return *this;
}

Vector2D Vector2D::operator+=(const Vector2D& rhs)
{
    this->x += rhs.x;
    this->y += rhs.y;
    return *this;
}

Vector2D Vector2D::operator+=(const Force2D& force)
{
    x += force.force.x;
    y += force.force.y;
    return *this;
}

Vector2D Vector2D::operator-(const float rhs) const
{
    return {this->x + rhs, this->y + rhs};
}

Vector2D Vector2D::operator-(const Vector2D& rhs) const
{
    return {this->x - rhs.x, this->y - rhs.y};
}

Vector2D Vector2D::operator-(Force2D& force) const
{
    return { x - force.force.x, y - force.force.y };
}

Vector2D Vector2D::operator-=(const float rhs)
{
    this->x -= rhs;
    this->y -= rhs;
    return *this;
}

Vector2D Vector2D::operator-=(const Vector2D& rhs)
{
    this->x -= rhs.x;
    this->y -= rhs.y;
    return *this;
}

Vector2D Vector2D::operator-=(const Force2D& force)
{
    x += force.force.x;
    y += force.force.y;
    return *this;
}

Vector2D Vector2D::operator*(const float rhs) const
{
    return {this->x * rhs, this->y * rhs};
}

Vector2D Vector2D::operator*=(const float rhs)
{
    this->x *= rhs;
    this->y *= rhs;
    return *this;
}

Vector2D Vector2D::operator/(const float rhs) const
{
    return {this->x / rhs, this->y / rhs};
}

Vector2D Vector2D::operator/=(const float rhs)
{
    this->x /= rhs;
    this->y /= rhs;
    return *this;
}