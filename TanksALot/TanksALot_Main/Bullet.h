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
		Bullet(matrix4 Source, std::string id = "None");
		~Bullet();
		//matrix of the model
		matrix4 model;
		//Bullet ID
		std::string ID;
		//Bullet Source

		//Bullet Life
		float BulletLife;


		float accl;
		float accl2;
		float spd;
	private:


	//Methods

		//Move Model forward by 'Speed'.
		matrix4 Move(float speed);

		/*
		Usage: Copy Assignment Operator
		Arguments: class object to copy
		Output: bool
		*/
		bool operator==(Bullet const& other) const;
		
	};
}
