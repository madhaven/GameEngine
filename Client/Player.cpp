#define GET_X_LPARAM(lp)						((int)(short)LOWORD(lp))
#define GET_Y_LPARAM(lp)						((int)(short)HIWORD(lp))

#include "Player.h"

#include <ctime>
#include <iostream>

Player::Player() {}

void Player::Init(const HWND handle)
{
	GetClientRect(handle, &playable_area_);
	srand(time(nullptr));

	// position_vec = {rand() % playable_area_.right, rand() % playable_area_.bottom};
	position_vec = Vector2D(playable_area_.right / 2, playable_area_.bottom / 2);
	velocity_vec = Vector2D();
	aim_pos_vec = Vector2D();
	force_vec = Vector2D();
	rotation_deg = 0;
}

void Player::Render(Graphics* graphics)
{
	graphics->DrawEllipse(position_vec.x, position_vec.y, 10, color_);
	graphics->DrawEllipse(aim_pos_vec.x, aim_pos_vec.y, 2, color_);

	for (auto& bullet : bullets)
	{
	    bullet.Render(graphics);
	}
}

void Player::Fire()
{
	trigger_released_ = FALSE;
	Bullet bullet = Bullet(playable_area_, position_vec, aim_pos_vec);
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
	switch (msg)
	{
	case WM_MOUSEMOVE:
		aim_pos_vec = Vector2D(GET_X_LPARAM(l_param), GET_Y_LPARAM(l_param));
		break;
	case WM_LBUTTONDOWN:
		Fire();
		trigger_released_ = TRUE;
		break;
	case WM_KEYDOWN:
		if (w_param == VK_SPACE && trigger_released_) { Fire(); }
		else if (w_param == 0x52) { ResetBullets(); } // R => 0x52
		else
		{
			if (force_vec.y == 0.0f)
			{
				if (w_param == VK_UP || w_param == 0x57) { force_vec.y = -1; }
				if (w_param == VK_DOWN || w_param == 0x53) { force_vec.y = 1; }
			}
			if (force_vec.x == 0.0f)
			{
				if (w_param == VK_RIGHT || w_param == 0x44) { force_vec.x = 1; }
				if (w_param == VK_LEFT || w_param == 0x41) { force_vec.x = -1; }
			}
		}
		break;
	case WM_KEYUP:
		if (w_param == VK_SPACE) { trigger_released_ = TRUE; }
		if (w_param == VK_UP || w_param == 0x57) { force_vec.y = 0; }
		if (w_param == VK_DOWN || w_param == 0x53) { force_vec.y = 0; }
		if (w_param == VK_RIGHT || w_param == 0x44) { force_vec.x = 0; }
		if (w_param == VK_LEFT || w_param == 0x41) { force_vec.x = 0; }
		// keyups trigger a complete reset of THAT component of the vector: this is not realistic
		// consider adding a force_decay that decreases power if still in motion instead of stopping.

		// Exit game if 'Q' or 'ESC' is pressed
		if (w_param == 0x51 || w_param == 0x1B) { PostQuitMessage(0); }
		break;
	default:;
	}
}

void Player::Update()
{
	force_vec *= force_gain;
	velocity_vec += force_vec;
	velocity_vec *= 1 - friction_coef;
	position_vec += velocity_vec;

	for (auto& bullet : bullets)
	{
	    bullet.Update();
	}
}

void Player::WriteStats(Graphics* graphics)
{
    D2D1_RECT_F rect = { 10, 100, 200, 50 };
    graphics->WriteText(L"pos.x:" + std::to_wstring(position_vec.x), rect);
    rect = { 10, 150, 200, 50 };
    graphics->WriteText(L"pos.y:" + std::to_wstring(position_vec.y), rect);
    rect = { 10, 200, 200, 50 };
    graphics->WriteText(L"acc.x:" + std::to_wstring(force_vec.x), rect);
    rect = { 10, 250, 200, 50 };
    graphics->WriteText(L"acc.y:" + std::to_wstring(force_vec.y), rect);
    rect = { 10, 300, 200, 50 };
    graphics->WriteText(L"vel.x:" + std::to_wstring(velocity_vec.x), rect);
    rect = { 10, 350, 200, 50 };
    graphics->WriteText(L"vel.y:" + std::to_wstring(velocity_vec.y), rect);
}

