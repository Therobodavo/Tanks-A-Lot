#pragma once
#include "Definitions.h"
#include "ControllerConfiguration.h"
#include "imgui\ImGuiObject.h"

namespace Simplex
{
	class Player
	{
		CameraManager* m_pCameraMngr = nullptr; //Singleton for the camera manager
		float rotation;
		vector3 camPos;
		vector3 playerPos;
		matrix4 model;
	public:
		Player();
		~Player();
		vector3 getCamPos(void);
		vector3 getPlayerPos(void);
		matrix4 getModel(void);
		void moveFoward(float move);
		void moveBack(float move);
		void rotateLeft(void);
		void rotateRight(void);
	};
}

