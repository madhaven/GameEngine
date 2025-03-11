#pragma once

#include <windows.h>
#include "Bullet.h"
#include "Utilities/Vector2D.h"

class Player : public GameObject
{
    Vector2D aim_pos_vec;
    Vector2D position_vec;
    Vector2D velocity_vec;
    Vector2D force_vec;
    float friction_coef;
    float force_gain; // the increase in power
    float terminal_velocity;
    float rotation_deg;
    
    D2D1_COLOR_F color_;
    bool trigger_released_;
    RECT playable_area_;

public:
    Bullet bullets[5];

    Player();

    void Init(HWND handle);

    void Update();

    void Render(Graphics* graphics);

    void OnWinEvent(UINT msg, WPARAM w_param, LPARAM l_param);

    bool GetNextBullet(const Bullet& bullet);

    void Fire();

    void ResetBullets();

    void WriteStats(Graphics* graphics);

    void EnforceBoundaries();
};
