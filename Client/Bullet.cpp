#include "Bullet.h"
#include <math.h>

void Bullet::Render(Graphics* graphics)
{
	if (!isAlive) { return; }
	graphics->DrawEllipse(position.x, position.y, 5, color);
}

void Bullet::Update()
{
	if (!isAlive) { return; }
	
	if (position.x > playableArea.right) { isAlive = FALSE; }
	if (position.y > playableArea.bottom) { isAlive = FALSE; }
	if (position.x < 0) { isAlive = FALSE; }
	if (position.y < 0) { isAlive = FALSE; }

	position.x += cos(angle) * speed;
	position.y += sin(angle) * speed;
}
