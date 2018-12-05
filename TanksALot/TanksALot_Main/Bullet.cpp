#include "Bullet.h"
#include <iostream>
using namespace std;

using namespace Simplex;


Bullet::Bullet(matrix4 Source)
{
	model = Source;
}


Bullet::~Bullet()
{
}

matrix4 Simplex::Bullet::Move(float speed = 0.5f)
{
	return model = glm::translate(model, vector3(speed, 0, 0));
}
