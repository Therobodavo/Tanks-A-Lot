#include "Player.h"

using namespace Simplex;


Player::Player()
{

	rotation = 0;
	model = glm::translate(vector3(0, 1, 0));

}


Player::~Player()
{
}

vector3 Simplex::Player::getCamPos(void)
{
	glm::vec4 Position = glm::vec4(glm::vec3(0.0f), 1.0f);

	matrix4 mPos = glm::translate(model, vector3(-8, 7.5, 1.f));
	glm::vec4 Transformed = mPos * Position;

	camPos = Transformed;
	return camPos;
}

vector3 Simplex::Player::getPlayerPos(void)
{
	glm::vec4 Position = glm::vec4(glm::vec3(0.0f), 1.0f);
	matrix4 mPos = glm::translate(model, vector3(0, 5, 1.f));

	glm::vec4 Transformed = mPos * Position;

	playerPos = Transformed;
	

	quaternion rot = glm::angleAxis(glm::radians(rotation), vector3(0.0f, 1.0f, 0.0f));
	vector3 distance = (playerPos - camPos);
	playerPos = camPos + (distance * rot);


	return playerPos;
}

matrix4 Simplex::Player::getModel(void)
{	
	return 	glm::scale(model,vector3(5.5f, 1.f, 2.5f));
}

void Simplex::Player::moveFoward(float move)
{
	model = glm::translate(model,vector3(move, 0, 0));

}

void Simplex::Player::moveBack(float move)
{
	model = glm::translate(model, vector3(move, 0, 0));

}

void Simplex::Player::rotateLeft(void)
{
	model = glm::rotate(model, glm::radians(1.f), vector3(0.0f, 1.0f, 0.0f));

	rotation += -0.01f;
	
}

void Simplex::Player::rotateRight(void)
{
	model = glm::rotate(model, glm::radians(-1.f), vector3(0.0f, 1.0f, 0.0f));

	rotation+= 0.01f;

}
