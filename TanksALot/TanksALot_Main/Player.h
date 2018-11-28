#pragma once
#include "Definitions.h"
#include "ControllerConfiguration.h"
#include "imgui\ImGuiObject.h"

namespace Simplex
{
	class Player
	{
		//float containing angle of roation of the base
		float rotationBase;
		//float containing angle of roation of the top
		float rotationTop;
		//vector position of the camera
		vector3 camPos;
		//vector position of camera target (not the same as the tanks position)
		vector3 targetPos;
		//matrix of the model
		matrix4 model;
	public:
		Player();
		~Player();

		//method returning camPos
		vector3 getCamPos(void);
		//method returning targetPos
		vector3 getTargetPos(void);
		//method returning matrix model of base
		matrix4 getModelBase(void);
		//method returning matrix model of top
		matrix4 getModelTop(void);

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
	};
}

