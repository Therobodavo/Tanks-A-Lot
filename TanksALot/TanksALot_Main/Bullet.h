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
		Bullet(Player Vehicle);
		~Bullet();
	//matrix of the model
		matrix4 model;
		//method for moving foward
		void Move(float speed);
		
	};
}
