#include "Player.h"

using namespace Simplex;


Player::Player()
{
	//setting variables
	rotationTop = 0;
	rotationBase = 0;
	model = glm::translate(vector3(0, 1, 0));
}


Player::~Player()
{
}

///methods that return values
#pragma region getMethods
vector3 Simplex::Player::getCamPos(void)
{
	//create a vec4 position
	glm::vec4 Position = glm::vec4(glm::vec3(0.0f), 1.0f);

	//get the matrix position of model
	matrix4 mPos = glm::translate(model, vector3(-8, 7.5, 1.f));

	//convert matrix to vec4
	glm::vec4 Transformed = mPos * Position;
	camPos = Transformed;

	return camPos;
}

vector3 Simplex::Player::getTargetPos(void)
{
	//create a vec4 position
	glm::vec4 Position = glm::vec4(glm::vec3(0.0f), 1.0f);
	//get the matrix position of model
	matrix4 mPos = glm::translate(model, vector3(0, 5, 1.f));
	//convert matrix to vec4
	glm::vec4 Transformed = mPos * Position;
	targetPos = Transformed;

	//create rotation quaternion based off of baseRotation
	quaternion rot = glm::angleAxis(glm::radians(rotationBase), vector3(0.0f, 1.0f, 0.0f));
	//calculate distance
	vector3 distance = (targetPos - camPos);
	//add camera position by the distance rotated
	targetPos = camPos + (distance * rot);


	return targetPos;
}

matrix4 Simplex::Player::getModelBase(void)
{
	return 	glm::scale(model, vector3(5.5f, 1.f, 2.5f));
}

matrix4 Simplex::Player::getModelTop(void)
{
	//move the top above the base
	matrix4 top = glm::translate(model, vector3(2, 1.f, 1));
	//rotate the top based off of the rotationTop float
	top = glm::rotate(top, glm::radians(rotationTop), vector3(0.0f, 1.0f, 0.0f));


	return glm::scale(top, vector3(5.5f, 0.5f, 0.5f));
}

#pragma endregion

///methods that rotate/move the tank
#pragma region Controls
void Simplex::Player::moveFoward(float move)
{
	model = glm::translate(model, vector3(move, 0, 0));

}

void Simplex::Player::moveBack(float move)
{
	model = glm::translate(model, vector3(move, 0, 0));

}

void Simplex::Player::rotateLeft(void)
{
	model = glm::rotate(model, glm::radians(1.f), vector3(0.0f, 1.0f, 0.0f));

	rotationBase += -0.01f;

}

void Simplex::Player::rotateRight(void)
{
	model = glm::rotate(model, glm::radians(-1.f), vector3(0.0f, 1.0f, 0.0f));

	rotationBase += 0.01f;

}

void Simplex::Player::aimRight(void)
{
	if (rotationTop > -20)
		rotationTop -= 0.5f;
}

void Simplex::Player::aimLeft(void)
{
	if (rotationTop < 20)
		rotationTop += 0.5f;
}
#pragma endregion


