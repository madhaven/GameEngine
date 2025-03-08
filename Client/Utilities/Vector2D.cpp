#include "Vector2D.h"
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

float Vector2D::magnitude() const
{
    if (this->x == 0 && this->y == 0)
        return 0;
    return std::sqrt(x * x + y * y);
}

Vector2D Vector2D::operator+(const Vector2D& rhs) const
{
    return {this->x + rhs.x, this->y + rhs.y};
}

Vector2D Vector2D::operator+(const float rhs) const
{
    return {this->x + rhs, this->y + rhs};
}

Vector2D Vector2D::operator+=(const Vector2D& rhs)
{
    this->x += rhs.x;
    this->y += rhs.y;
    return *this;
}

Vector2D Vector2D::operator+=(const float rhs)
{
    this->x += rhs;
    this->y += rhs;
    return *this;
}

Vector2D Vector2D::operator-(const Vector2D& rhs) const
{
    return {this->x - rhs.x, this->y - rhs.y};
}

Vector2D Vector2D::operator-(const float rhs) const
{
    return {this->x + rhs, this->y + rhs};
}

Vector2D Vector2D::operator-=(const Vector2D& rhs)
{
    this->x -= rhs.x;
    this->y -= rhs.y;
    return *this;
}

Vector2D Vector2D::operator-=(const float rhs)
{
    this->x -= rhs;
    this->y -= rhs;
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