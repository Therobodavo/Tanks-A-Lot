#include "Player.h"
#include <iostream>
using namespace std;

using namespace Simplex;


Player::Player()
{
	//setting variables
	rotationTop = 0;
	rotationTopUp = 0;
	rotationBase = 0;
	rotationBase2 = 0;
	rotationCam = 0;
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
	matrix4 top2 = glm::rotate(model, glm::radians(rotationCam), vector3(0.0f, 1.0f, 0.0f));
	//top2 = glm::rotate(top2, glm::radians(rotationBase2), vector3(0.0f, 1.0f, 0.0f));
	matrix4 mPos = glm::translate(top2, vector3(-16, 7.5, 0.f));

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
	matrix4 top2 = glm::rotate(model, glm::radians(rotationCam), vector3(0.0f, 1.0f, 0.0f));
	//top2 = glm::rotate(top2, glm::radians(rotationBase2), vector3(0.0f, 1.0f, 0.0f));
	matrix4 mPos = glm::translate(top2, vector3(0, 5, 1.f));

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
	return glm::scale(model, vector3(2.f, 2.f, 2.f));
}

matrix4 Simplex::Player::getModelTop(void)
{
	//move the top above the base
    top = glm::translate(model, vector3(-1.1f, 0.f, 0));
	
	//rotate the top based off of the rotationTop float
	top = glm::rotate(top, glm::radians(rotationTop), vector3(0.0f, 0.6f, 0.0f));
	float rot = (rotationTopUp/5)* 0.2;
	top = glm::translate(top, vector3(rot/2 + 1, rot, 0));
	top = glm::rotate(top, glm::radians(rotationTopUp), vector3(0.0f, 0.0f, 0.6f));

	//top = glm::rotate(top, glm::radians(rotationBase2), vector3(0.0f, 1.0f, 0.0f));
	return glm::scale(top, vector3(5.0f, 1.5f, 1.5f));
}

matrix4 Simplex::Player::getModelHead(void)
{
	matrix4 head = glm::scale(model, vector3(2.f, 2.0f, 2.f));
	//head = glm::rotate(head, glm::radians(rotationBase2), vector3(0.0f, 1.0f, 0.0f));
	//float rot = glm::abs(rotationBase2 * 0.005f);
	//if (rot >= 1) {
	//	rot -= round(rot);
	
//	if (rot > 1.0)
	//	rot = 0;
	//rot = 0;
	//cout << rot << endl;
	//return glm::translate(head, vector3(rot, 0.0f, 0));
	return head;
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
	glm::translate(model, vector3(move, 0, 0));

}

void Simplex::Player::rotateLeft(void)
{
   model = glm::rotate(model, glm::radians(0.5f), vector3(0.0f, 1.0f, 0.0f));
	rotationBase += -0.01f;
	rotationBase2 += -0.5f;
}

void Simplex::Player::rotateRight(void)
{
	model = glm::rotate(model, glm::radians(-0.5f), vector3(0.0f, 1.0f, 0.0f));
	rotationBase += 0.01f;
	rotationBase2 += 0.5f;

}

void Simplex::Player::aimRight(void)
{
	if (rotationTop > -80) {
		rotationTop -= 0.5f;
		rotationCam -= 0.5f;
	}
	
}

void Simplex::Player::aimLeft(void)
{
	if (rotationTop < 80) {
		rotationTop += 0.5f;
		rotationCam += 0.5f;
   }
	
}
void Simplex::Player::aimUp(void)
{
	if (rotationTopUp < 30)
	rotationTopUp += 0.5f;
}
void Simplex::Player::aimDown(void)
{
	if (rotationTopUp > 0)
	rotationTopUp -= 0.5f;
}
void Simplex::Player::camLeft(void)
{
	rotationCam -= 1.0f;
}
void Simplex::Player::camRight(void)
{
	rotationCam += 1.0f;
}
#pragma endregion


