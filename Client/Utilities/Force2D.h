#pragma once
#include "Vector2D.h"

class Force2D
{
    int life;
    bool is_active;
public:
    Vector2D unit_vector;
    Vector2D force_vec;
    
    // the amount of increase in force until full power is achieved
    float attack;
    
    // the full force exerted
    float magnitude;
    
    // the cumulative increase in force over prolonged application
    float gain;
    
    // the amount of decrease in force after release of force
    float release;

    Force2D();
    Force2D(Vector2D vector, float attack, float gain, float release);
    Force2D(Vector2D directionVector, float magnitude, float attack, float gain, float release);
    Force2D& Update();
    void activate();
    void deactivate();

    // operators
    bool operator!=(const Force2D& rhs) const;
    bool operator==(const Force2D& rhs) const;
    Vector2D operator+(const Force2D& force) const;
    void operator+=(const Force2D& force);
    Vector2D operator-(const Force2D& force) const;   
    void operator-=(const Force2D& force);
};
