#pragma once
#include "Vector2D.h"

class Force2D
{
    /*
     * The force is an object that represents A FORCE.
     * The force object in its core is a vector that represents the effect the object has.
     * The other parameters specify the update behavior.
     * The reason for these controls is to shift the game physics from an On-Off mechanism to something that feels alive.
     * 
     * Force object has an activate and deactivate method to set it in action and set it off.
     * It also has a max_life which says how long it will be alive for.
     * Being active means the force has an effect. Even if it is inactive, there could be a residual "release" effect.
     * Being dead means no behavior is applicable anyhow.
     *
     * active          magnitude          inactive             dead
     *   |-----------------|------------------|------------------|
     *         +attack           +gain              -release
     */
    
    int life;
    bool is_active;
public:
    Vector2D direction;
    Vector2D force;
    
    // the amount of increase in force until full power is achieved
    float attack;
    
    // the full force exerted
    float magnitude;
    
    // the cumulative increase in force over prolonged application
    float gain;
    
    // the amount of decrease in force after release of force
    float release;

    // kill the force after max_life
    int max_life;

    Force2D();
    Force2D(Vector2D direction_vector, float magnitude, float attack=.0f, float gain=.0f, float release=.0f, int max_life=0);
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
