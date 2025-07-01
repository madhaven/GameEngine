#define GET_X_LPARAM(lp)						((int)(short)LOWORD(lp))
#define GET_Y_LPARAM(lp)						((int)(short)HIWORD(lp))

#include "Player.h"

#include <ctime>
#include <iostream>

#include "Utilities/Force2D.h"

constexpr int DIR_UP = 0;
constexpr int DIR_RIGHT = 1;
constexpr int DIR_DOWN = 2;
constexpr int DIR_LEFT = 3;
constexpr int FIRE_RECOIL = 4;

Player::Player()
{
    friction_coef = 0.1f;
    terminal_velocity = 0.5;
    rotation_deg = 0;
    trigger_released_ = true;

    color_ = D2D1::ColorF(0.0f, 1.0f, 1.0f);
    playable_area_ = {};
    
    float mag = 1.f, att = .0f, gai = .05f, rel = .0f;
    forces[DIR_UP] = Force2D{{0, -1}, mag, att, gai, rel};
    forces[DIR_RIGHT] = Force2D({1, 0}, mag, att, gai, rel);
    forces[DIR_DOWN] = Force2D({0, 1}, mag, att, gai, rel);
    forces[DIR_LEFT] = Force2D({-1, 0}, mag, att, gai, rel);
}

void Player::Init(const HWND handle)
{
    GetClientRect(handle, &playable_area_);
    srand(time(nullptr));

    // position_vec = {rand() % playable_area_.right, rand() % playable_area_.bottom};
    position = Vector2D(playable_area_.right / 2, playable_area_.bottom / 2);
    velocity = Vector2D();
    net_force = Vector2D();
    aim_pos_vec = Vector2D();
    rotation_deg = 0;
}

void Player::Render(Graphics* graphics)
{
    graphics->DrawEllipse(position.x, position.y, 10, color_);
    graphics->DrawEllipse(aim_pos_vec.x, aim_pos_vec.y, 2, color_);

    for (auto& bullet : bullets)
    {
        bullet.Render(graphics);
    }
}

void Player::Fire()
{
    auto recoil_direction = (position - aim_pos_vec).normalize();
    forces[FIRE_RECOIL] = Force2D(recoil_direction, .1f, .0f, .0f, .0f, 4);
    forces[FIRE_RECOIL].activate();
    trigger_released_ = FALSE;
    Bullet bullet = Bullet(playable_area_, position, aim_pos_vec);
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
    switch (msg) // is if cases better to improve multiple events ?
    {
    case WM_MOUSEMOVE:
        aim_pos_vec = Vector2D(GET_X_LPARAM(l_param), GET_Y_LPARAM(l_param));
        break;
    case WM_LBUTTONDOWN:
        if (trigger_released_) { Fire(); }
        break;
    case WM_LBUTTONUP:
        trigger_released_ = true;
        forces[FIRE_RECOIL].deactivate();
        break;
    case WM_KEYDOWN:
        if (w_param == VK_SPACE && trigger_released_) { Fire(); }
        else if (w_param == 0x52) { ResetBullets(); } // R => 0x52
        else
        {
            if (w_param == VK_UP || w_param == 0x57) { forces[DIR_UP].activate(); }
            if (w_param == VK_DOWN || w_param == 0x53) { forces[DIR_DOWN].activate(); }
            if (w_param == VK_RIGHT || w_param == 0x44) { forces[DIR_RIGHT].activate(); }
            if (w_param == VK_LEFT || w_param == 0x41) { forces[DIR_LEFT].activate(); }
        }
        break;
    case WM_KEYUP:
        if (w_param == VK_SPACE)
        {
            trigger_released_ = TRUE;
            forces[FIRE_RECOIL].deactivate();
        }
        if (w_param == VK_UP || w_param == 0x57) { forces[DIR_UP].deactivate(); }
        if (w_param == VK_DOWN || w_param == 0x53) { forces[DIR_DOWN].deactivate(); }
        if (w_param == VK_RIGHT || w_param == 0x44) { forces[DIR_RIGHT].deactivate(); }
        if (w_param == VK_LEFT || w_param == 0x41) { forces[DIR_LEFT].deactivate(); }
        // keyups trigger a complete reset of THAT component of the vector: this is not realistic
        // consider adding a force_decay that decreases power if still in motion instead of stopping.

        // Exit game if 'Q' or 'ESC' is pressed
        if (w_param == 0x51 || w_param == 0x1B) { PostQuitMessage(0); }
        break;
    default:;
    }
}

void Player::EnforceBoundaries()
{
    if (position.x < playable_area_.left)
    {
        position.x += 2 * (playable_area_.left - position.x);
        velocity.x *= -1;
    }
    else if (position.x > playable_area_.right)
    {
        position.x -= 2 * (position.x - playable_area_.right);
        velocity.x *= -1;
    }
    if (position.y < playable_area_.top)
    {
        position.y += 2 * (playable_area_.top - position.y);
        velocity.y *= -1;
    }
    else if (position.y > playable_area_.bottom)
    {
        position.y -= 2 * (position.y - playable_area_.bottom);
        velocity.y *= -1;
    }
}

void Player::Update()
{
    UpdateVectors();
    velocity *= 1 - friction_coef;
    velocity += net_force;
    position += velocity;
    EnforceBoundaries();

    for (auto& bullet : bullets) { bullet.Update(); }
}

void Player::WriteStats(Graphics* graphics) const
{
    D2D1_RECT_F rect = { 10, 100, 200, 50 };
    graphics->WriteText(L"pos.x:" + std::to_wstring(position.x), rect);
    rect = { 10, 150, 200, 50 };
    graphics->WriteText(L"pos.y:" + std::to_wstring(position.y), rect);
    rect = { 10, 200, 200, 50 };
    graphics->WriteText(L"vel.x:" + std::to_wstring(velocity.x), rect);
    rect = { 10, 250, 200, 50 };
    graphics->WriteText(L"vel.y:" + std::to_wstring(velocity.y), rect);
    rect = { 10, 300, 200, 50 };
    graphics->WriteText(L"acc.x:" + std::to_wstring(net_force.x), rect);
    rect = { 10, 350, 200, 50 };
    graphics->WriteText(L"acc.y:" + std::to_wstring(net_force.y), rect);
}

