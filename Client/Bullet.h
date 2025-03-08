#pragma once
#include "Interfaces.h"
#include "Utilities/Vector2D.h"

class Bullet : public GameObject
{
	float speed = 30.0f;

public:
	BOOL isAlive = FALSE;
	Vector2D position;
	Vector2D firePosition;
	Vector2D velocity;
	float drag = .0001f;
	
	D2D1_COLOR_F color = D2D1::ColorF(1.0f, 0.3f, 0.0f);
	RECT playableArea = {};

	Bullet();
	Bullet(RECT playableArea, Vector2D firedPosition, Vector2D target);
	void Render(Graphics* graphics);
	void Update();
};
