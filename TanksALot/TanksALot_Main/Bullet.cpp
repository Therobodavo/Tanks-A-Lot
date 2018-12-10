#include "Bullet.h"
#include <iostream>
using namespace std;

using namespace Simplex;


Bullet::Bullet(matrix4 Source, std::string id)
{
	//Set Model (+Minor Adjustments for Turret)
	model = Source;
	model *= glm::scale(vector3(0.3f, 0.3f, 0.3f));
	model *= glm::translate(IDENTITY_M4, vector3(0.f, 5.0f, -0.5f));

	//SetBulletLifeSpawn
	BulletLife = 15;

	//SetBulletID
	ID = id;
}


Bullet::~Bullet()
{
}

matrix4 Simplex::Bullet::Move(float speed = 0.5f)
{
	return model = glm::translate(model, vector3(speed, 0, 0));
}

bool Simplex::Bullet::operator==(Bullet const & other) const
{
	return ID == other.ID;
}

