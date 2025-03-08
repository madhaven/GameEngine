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
	float friction_coef = 0.1f;
	float force_gain = 1.02f; // the increase in power
	float terminal_velocity = 0.5;
	float rotation_deg;
	
	D2D1_COLOR_F color_ = D2D1::ColorF(0.0f, 1.0f, 1.0f);
	BOOL trigger_released_ = TRUE;
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
};
