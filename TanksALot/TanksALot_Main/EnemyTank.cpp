#include "EnemyTank.h"
#include <iostream>
#include <math.h>
using namespace std;

using namespace Simplex;


EnemyTank::EnemyTank(Player* play)
{
	player = play;
	rotationTop = 0;
	rotationTopUp = 0;
	float x = rand() % 500;
	float z = rand() % 500;
	type = rand() % 10 + 1;
	model = glm::translate(vector3(x, 0.2f, z));

	//Bulletinfo
	//Set reloadtimer to: (airreloadAverage [- variation(since lack of negative random)]) + Random number between 0 and 2*Variation + 1[due to 0];
	aireloadtimer = (aireloadtimeraverage - aireloadtimervariation) + rand() % ((aireloadtimervariation * 2) + 1);
}


EnemyTank::~EnemyTank()
{
	//SafeDelete(player);
}

matrix4 Simplex::EnemyTank::getLeft(void)
{
	return glm::translate(getModelBase(), vector3(-1, 0, -1.5f));
}

matrix4 Simplex::EnemyTank::getRight(void)
{
	return glm::translate(getModelBase(), vector3(-1, 0, 1));
}

matrix4 Simplex::EnemyTank::getFront(void)
{
	return glm::translate(getModelBase(), vector3(1.5f, 0, -0.5f));
}

matrix4 Simplex::EnemyTank::getBack(void)
{
	return glm::translate(getModelBase(), vector3(-3, 0, -0.5f));
}


matrix4 Simplex::EnemyTank::getModelBase(void)
{
	return glm::scale(model, vector3(2.f, 2.f, 2.f));
}

matrix4 Simplex::EnemyTank::getModelTop(void)
{
	//move the top above the base
	top = glm::translate(model, vector3(-1.1f, 0.f, 0));

	//rotate the top based off of the rotationTop float
	top = glm::rotate(top, glm::radians(rotationTop), vector3(0.0f, 0.6f, 0.0f));
	float rot = (rotationTopUp / 5)* 0.2;
	top = glm::translate(top, vector3(rot / 2 + 1, rot, 0));
	top = glm::rotate(top, glm::radians(rotationTopUp), vector3(0.0f, 0.0f, 0.6f));

	//top = glm::rotate(top, glm::radians(rotationBase2), vector3(0.0f, 1.0f, 0.0f));
	return glm::scale(top, vector3(5.0f, 1.5f, 1.5f));
}

matrix4 Simplex::EnemyTank::getModelHead(void)
{
	matrix4 head = glm::scale(model, vector3(2.f, 2.0f, 2.f));
	return head;
}

void Simplex::EnemyTank::moveFoward(float move)
{
	model = glm::translate(model, vector3(move, 0, 0));
}

void Simplex::EnemyTank::moveBack(float move)
{
	model = glm::translate(model, vector3(move, 0, 0));
	glm::translate(model, vector3(move, 0, 0));
}

void Simplex::EnemyTank::rotateLeft(void)
{
	model = glm::rotate(model, glm::radians(0.5f), vector3(0.0f, 1.0f, 0.0f));
}

void Simplex::EnemyTank::rotateRight(void)
{
	model = glm::rotate(model, glm::radians(-0.5f), vector3(0.0f, 1.0f, 0.0f));
}

void Simplex::EnemyTank::aimRight(void)
{

	if (rotationTop > -90) {
		if(type <= 3)
		rotationTop -= 0.1f;
		else if (type <= 5)
			rotationTop -= 0.2f;
		else
			rotationTop -= 0.15f;
	}
}

void Simplex::EnemyTank::aimLeft(void)
{

	if (rotationTop < 90) {
		if (type <= 3)
			rotationTop += 0.1f;
		else if (type <= 5)
			rotationTop += 0.2f;
		else
			rotationTop += 0.15f;
	}
}

void Simplex::EnemyTank::aimUp(void)
{
	if (rotationTopUp < 30) {
		rotationTopUp += 0.1f;
	}
}

void Simplex::EnemyTank::aimDown(void)
{
	if (rotationTopUp > 0) {
		rotationTopUp -= 0.1f;
	}
}

void Simplex::EnemyTank::aiMovement(void)
{
     matrix4 playerPos = player->getModelBase();

	 glm::vec4 Position = glm::vec4(glm::vec3(0.0f), 1.0f);
	 glm::vec4 Transformed = playerPos * Position;
	 glm::vec4 Transformed2 = getModelBase() * Position;
	 vector3 targetPos = Transformed;
	 vector3 currentPos = Transformed2;
	 
	 vector3 left = getLeft() * Position;
	 vector3 right = getRight() * Position;
	 vector3 Front = getFront() * Position;
	 vector3 Back = getBack() * Position;

	 vector3 Front1 = glm::translate(getFront(), vector3(1, 0, 0)) * Position;
	 vector3 Front2 = glm::translate(getFront(), vector3(0.5, 0, 0)) * Position;



	float d1 = glm::distance(targetPos, Front1);
	float d2 = glm::distance(targetPos, Front2);





	float dL = glm::distance(targetPos, left);
	float dR = glm::distance(targetPos, right);

	float speedBoost = 0.f;
	if (d2 <= 120) {
		aiAim();
		speedBoost = 0.05f;
	}
	
	if (type <= 1) {
		///Behavior1
		if (dL < dR)
			rotateLeft();
		if (dL > dR)
			rotateRight();


		if (d1 <= (d2))
		{
			moveFoward(0.2f + speedBoost);
		}
	}
	else if (type <= 4) {
		///Behavior2
		if (d1 >= d2) {
			if (dL < dR)
				rotateLeft();
			if (dL > dR)
				rotateRight();
		}
		if (d1 <= (d2 + 0.5f))
		{
			moveFoward(0.05f + speedBoost);
		}
	}
	else if (type <= 6) {
		///Behavior2
		if (d1 >= d2 + 1.f) {
			if (dL < dR)
				rotateLeft();
			if (dL > dR)
				rotateRight();
		}
		moveFoward(0.08f + speedBoost);
	}
	else if (type <= 8) {
		if (d1 >= d2) {
			if (dL < dR)
				rotateLeft();
			if (dL > dR)
				rotateRight();
		}
		if (d1 <= (d2))
		{
			moveFoward(0.1f + speedBoost);
		}
	}
	else {
		if (d2 <= 120) {
			if (dL < dR)
				rotateLeft();
			if (dL > dR)
				rotateRight();
		}
		else {
			if (d1 >= d2 + 1.f) {
				if (dL < dR)
					rotateLeft();
				if (dL > dR)
					rotateRight();
			}
			moveFoward(0.08f + speedBoost);
		}
	}
	

	
}

void Simplex::EnemyTank::aiAim(void)
{
	glm::vec4 Position = glm::vec4(glm::vec3(0.0f), 1.0f);
	matrix4 cannon = getModelTop();
	vector3 front = glm::translate(cannon, vector3(0.5f, 0, 0)) * Position;
	vector3 back = glm::translate(cannon, vector3(-0.5f, 0, 0)) * Position;
	vector3 left = glm::translate(cannon, vector3(0, 0, 0.5f)) * Position;
	vector3 right = glm::translate(cannon, vector3(0, -0, -0.5f)) * Position;

	vector3 targetPos = player->getModelHead() * Position;
	// --- Locked on reset ---
	horizontalLockedOn = false;
	verticalLockedOn = false;
	// -----------------------


	float dL = glm::distance(targetPos, left);
	float dR = glm::distance(targetPos, right);

	if (dL > dR)
		aimLeft();
	else if (dL < dR)
		aimRight();
	else
		horizontalLockedOn = true;

	float dFoward = glm::distance(targetPos, front);
	dFoward = dFoward / 5;
	dFoward -= 2;

	if (dFoward > rotationTopUp + 1.f) //Old: 2.f
		aimUp();
	else if (dFoward < rotationTopUp - 1.f) //Old: 2.f
		aimDown();
	else //If Vertical Aim is good
		verticalLockedOn = true;

	// --- Locked on check ---
	//Check 1:  Distance Left is smaller than Distance Right (+ margin), AND Check 2: Distance right is smaller than Distance Left (+ margin)
	if(dL < (dR + .1f) && dR < (dL + .1f) )
	horizontalLockedOn = true;

	//verticalLockedOn = false;
	// -----------------------
}

//Bullet Methods
bool Simplex::EnemyTank::aiReloadStatus(float deltatime)
{
	//Update timer
	aireloadtimer -= deltatime;
	//Ready to fire?  Reload timer at 0 AND locked up horizontally and Vertically
	if (aireloadtimer <= 0 && horizontalLockedOn == true && verticalLockedOn == true)
	//If Yes ...
	{
		//Reset timer
		aireloadtimer = (aireloadtimeraverage - aireloadtimervariation) + rand() % ((aireloadtimervariation * 2) + 1);
		//Return true
		return true;
	}
	//Otherwise ...
	//return false
	return false;
}


