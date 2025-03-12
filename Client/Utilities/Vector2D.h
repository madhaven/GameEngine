#pragma once
class Force2D;

class Vector2D
{
public:
    float x, y;

    Vector2D();
    Vector2D(float x, float y);
    Vector2D(const Vector2D& vector);

    // methods
    Vector2D normalize() const;
    float magnitude() const;

    // operators
    bool operator==(const Vector2D& rhs) const;
    bool operator!=(const Vector2D& rhs) const;
    Vector2D operator+(float rhs) const;
    Vector2D operator+(const Vector2D& rhs) const;
    Vector2D operator+(Force2D& force) const;
    Vector2D operator+=(float rhs);
    Vector2D operator+=(const Vector2D& rhs);
    Vector2D operator+=(const Force2D& force);
    Vector2D operator-(float rhs) const;
    Vector2D operator-(const Vector2D& rhs) const;
    Vector2D operator-(Force2D& force) const;
    Vector2D operator-=(float rhs);
    Vector2D operator-=(const Vector2D& rhs);
    Vector2D operator-=(const Force2D& force);
    Vector2D operator*(float rhs) const;
    Vector2D operator*=(float rhs);
    Vector2D operator/(float rhs) const;
    Vector2D operator/=(float rhs);
};
