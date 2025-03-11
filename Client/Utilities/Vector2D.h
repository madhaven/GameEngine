#pragma once

class Vector2D
{
public:
    float x, y;

    Vector2D();
    Vector2D(float x, float y);
    Vector2D(const Vector2D& vector);

    float magnitude() const;

    Vector2D operator+(float rhs) const;
    Vector2D operator+(const Vector2D& rhs) const;
    Vector2D operator+=(const Vector2D& rhs);
    Vector2D operator+=(float rhs);
    Vector2D operator-(const Vector2D& rhs) const;
    Vector2D operator-(float rhs) const;
    Vector2D operator-=(const Vector2D& rhs);
    Vector2D operator-=(float rhs);
    Vector2D operator*(float rhs) const;
    Vector2D operator*=(float rhs);
    Vector2D operator/(float rhs) const;
    Vector2D operator/=(float rhs);
};
