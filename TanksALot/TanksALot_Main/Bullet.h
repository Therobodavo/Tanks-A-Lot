#pragma once
#include "Definitions.h"
#include "ControllerConfiguration.h"
#include "imgui\ImGuiObject.h"
#include "Player.h"
namespace Simplex
{
	class Bullet
	{
		
	public:
		Bullet(matrix4 Source);
		~Bullet();
		//matrix of the model
		matrix4 model;
		//Bullet ID
		std::string ID;
		//Bullet Life
		float BulletLife;

		//method for moving foward
		matrix4 Move(float speed);
		
	};
}
