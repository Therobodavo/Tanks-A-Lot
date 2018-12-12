#pragma once
#include "Definitions.h"
#include "ControllerConfiguration.h"
#include "imgui\ImGuiObject.h"
#include "Player.h"
namespace Simplex
{
	class EnemyTank
	{//float containing angle of roation of the base
		float rotationBase;
		float rotationBase2;
		//float containing angle of roation of the top
		float rotationTop;
		float rotationTopUp;

		//matrix of the model
		matrix4 model;

		matrix4 top;

		Player* player;
		int type;
	public:
		EnemyTank(Player* play);
		~EnemyTank();

		matrix4 getLeft(void);
		matrix4 getRight(void);
		matrix4 getFront(void);
		matrix4 getBack(void);
		//method returning matrix model of base
		matrix4 getModelBase(void);
		//method returning matrix model of top
		matrix4 getModelTop(void);

		matrix4 getModelHead(void);

		//method for moving foward
		void moveFoward(float move);
		//method for moving back
		void moveBack(float move);
		//method for rotating base left
		void rotateLeft(void);
		//method for rotating base right
		void rotateRight(void);
		//method for roating top right
		void aimRight(void);
		//method for roating top left
		void aimLeft(void);

		//method for roating top right
		void aimUp(void);
		//method for roating top left
		void aimDown(void);

		void aiMovement(void);
		void aiAim(void);

	};
}

