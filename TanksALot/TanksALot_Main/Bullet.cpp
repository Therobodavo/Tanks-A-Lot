#include "Bullet.h"
#include <iostream>
using namespace Simplex;
using namespace std;



Bullet::Bullet(matrix4 Source, std::string id)
{
	//Set Model (+Minor Adjustments for Turret)
	model = Source;
	model *= glm::scale(vector3(0.3f, 0.3f, 0.3f));
	model *= glm::translate(IDENTITY_M4, vector3(0.f, 5.0f, -0.5f));

	//SetBulletLifeSpawn
	//15
	BulletLife = 5;

	//SetBulletID
	ID = id;

	glm::vec4 Position = glm::vec4(glm::vec3(0.0f), 1.0f);
	float yPos = (Position * model).y;
	accl = 0.5f + (yPos * 0.1f); //Old: yPos * 0.1f
	accl2 = accl;
	spd = (0.5f - (yPos * 0.1f)); //Old: yPos * 0.1f
}


Bullet::~Bullet()
{
}

matrix4 Simplex::Bullet::Move(float speed = 0.5f)
{
	//bullets move slightly when tank moves, will change this method to make that stop
	model = glm::translate(model, vector3(spd, 0, 0));
	spd += 0.025f; //Old 0.01f (Goes further before hitting ground)
	
	glm::vec4 Position = glm::vec4(glm::vec3(0.0f), 1.0f);
	vector3 height = glm::translate(model, vector3(0, 0, 0)) * Position;

	if(accl < (accl2 + 1))
		accl += 0.05f;
	if (height.y < 0)
		return model;
	else {
		return 	model = glm::rotate(model, glm::radians(accl), vector3(0.0f, 0.0f, -1.0f));
	}

}

bool Simplex::Bullet::operator==(Bullet const & other) const
{
	return ID == other.ID;
}

