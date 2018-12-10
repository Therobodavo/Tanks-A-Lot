#include "Bullet.h"
#include <iostream>
using namespace std;

using namespace Simplex;


Bullet::Bullet(matrix4 Source)
{
	model = Source;
	model *= glm::scale(vector3(0.3f, 0.3f, 0.3f));
	model *= glm::translate(IDENTITY_M4, vector3(0.f, 5.0f, -0.5f));
}


Bullet::~Bullet()
{
}

matrix4 Simplex::Bullet::Move(float speed = 0.5f)
{
	return model = glm::translate(model, vector3(speed, 0, 0));
}
