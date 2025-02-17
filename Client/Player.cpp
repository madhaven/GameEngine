#define GET_X_LPARAM(lp)						((int)(short)LOWORD(lp))
#define GET_Y_LPARAM(lp)						((int)(short)HIWORD(lp))

#include "Player.h"

#include <ctime>
#include <iostream>

Player::Player()
{
	pos_aim_.x = pos_aim_.y = 0;
}

void Player::Init(const HWND handle)
{
	GetClientRect(handle, &playable_area_);

	srand(time(nullptr));
	position.x = rand() % playable_area_.right;
	position.y = rand() % playable_area_.bottom;
    prev_position.x = position.x;
    prev_position.y = position.y;
    frame_.x = 0;
    frame_.y = 0;
}

void Player::Render(Graphics* graphics)
{
	graphics->DrawEllipse(position.x, position.y, 10, color_);
	graphics->DrawEllipse(pos_aim_.x, pos_aim_.y, 2, color_);

	for (auto& bullet : bullets)
	{
	    bullet.Render(graphics);
	}
}

void Player::Fire()
{
	trigger_released_ = FALSE;
	Bullet bullet;
	bullet.isAlive = TRUE;
	bullet.aimPostion = pos_aim_;
	bullet.firePosition = position;
	bullet.angle = atan2f(pos_aim_.y - position.y, pos_aim_.x - position.x);
	bullet.position = position;
	bullet.playableArea = playable_area_;
	bullet.color = D2D1::ColorF(1.0f, 1.0f, 0.0f);
	GetNextBullet(bullet);
}

void Player::ResetBullets()
{
	for (auto& bullet : bullets)
	{
	    bullet.isAlive = FALSE;
	}
}

bool Player::GetNextBullet(const Bullet& bullet)
{
	for (auto& index : bullets)
    {
		if (!index.isAlive)
		{
            index = bullet;
			return TRUE;
		}
	}
	return FALSE;
}

void Player::OnWinEvent(const UINT msg, const WPARAM w_param, const LPARAM l_param)
{
	if (msg == WM_MOUSEMOVE)
	{
		pos_aim_.x = GET_X_LPARAM(l_param);
		pos_aim_.y = GET_Y_LPARAM(l_param);
	}
	else if (msg == WM_KEYDOWN && w_param == VK_SPACE && trigger_released_)
	{
		Fire();
	}
	else if (msg == WM_LBUTTONDOWN)
	{
		Fire();
		trigger_released_ = TRUE;
	}
	else if (msg == WM_KEYDOWN && w_param == 0x52)	// R => 0x52
	{
		ResetBullets();
	}
	else if (msg == WM_KEYUP)
	{
		if (w_param == VK_SPACE) { trigger_released_ = TRUE; }
		if (w_param == VK_UP || w_param == 0x57) { key_direction_.y = 0; }
		if (w_param == VK_DOWN || w_param == 0x53) { key_direction_.y = 0; }
		if (w_param == VK_RIGHT || w_param == 0x44) { key_direction_.x = 0; }
		if (w_param == VK_LEFT || w_param == 0x41) { key_direction_.x = 0; }

	    // Exit game if 'Q' or 'ESC' is pressed
		if (w_param == 0x51 || w_param == 0x1B)
		{
		    PostQuitMessage(0);
		}
	}
    else if (msg == WM_KEYDOWN)
    {
        if (w_param == VK_UP || w_param == 0x57) { key_direction_.y = -1; }
        if (w_param == VK_DOWN || w_param == 0x53) { key_direction_.y = 1; }
        if (w_param == VK_RIGHT || w_param == 0x44) { key_direction_.x = 1; }
        if (w_param == VK_LEFT || w_param == 0x41) { key_direction_.x = -1; }
    }
}

void Player::Update()
{
    if (frame_.x > 0 && key_direction_.x == 0)
    {
        frame_.x--;
    }
    else if (frame_.x <= 50)
    {
        frame_.x++;
    }

    if (frame_.y > 0 && key_direction_.y == 0)
    {
        frame_.y--;
    }
    else if (frame_.y <= 50)
    {
        frame_.y++;
    }

    CalculateAcceleration();
    CalculateDeceleration();
    CalculateVelocity();
    CalculatePosition();

	for (auto& bullet : bullets)
	{
	    bullet.Update();
	}
}

void Player::CalculateAcceleration()
{
    if (key_direction_.x == 0)
    {
        deceleration_.x = -acceleration_.x;
    }

    if (key_direction_.y == 0)
    {
        deceleration_.y = -acceleration_.y;
    }

    const auto angle = atan2f(key_direction_.y, key_direction_.x);
    acceleration_.x = cosf(angle) * acceleration_magnitude * key_direction_.x;
    acceleration_.y = sinf(angle) * acceleration_magnitude * key_direction_.y;
}

void Player::CalculateDeceleration()
{
    if (key_direction_.x == 0)
    {
        acceleration_.x = -deceleration_.x;
    }

    if (key_direction_.y == 0)
    {
        acceleration_.y = -deceleration_.y;
    }
}

void Player::CalculateVelocity()
{
    const auto v_x = acceleration_.x * 1 + velocity_.x;
    const auto v_y = acceleration_.y * 1 + velocity_.y;
    const auto mag = sqrtf(powf(v_x, 2) + powf(v_y, 2));
    if (mag <= max_velocity_)
    {
        velocity_.x = v_x;
        velocity_.y = v_y;
    }
}

void Player::CalculatePosition()
{
    position.x = velocity_.x * frame_.x + position.x;
    position.y = velocity_.y * frame_.y + position.y;
}

