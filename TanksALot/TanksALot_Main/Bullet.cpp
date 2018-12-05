#include "Bullet.h"
#include <iostream>
using namespace std;

using namespace Simplex;


Bullet::Bullet(Simplex::Player Vehicle)
{
	model = Vehicle.getModelTop();
}


Bullet::~Bullet()
{
}

void Simplex::Bullet::Move(float speed = 0.5f)
{
	model = glm::translate(model, vector3(speed, 0, 0));
}
