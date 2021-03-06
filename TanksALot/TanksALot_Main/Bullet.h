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
		String source;
		//Bullet Life
		float BulletLife;

		int bulletTeam;
		float accl;
		float accl2;
		float spd;

		//Move Model forward by 'Speed'.
		matrix4 Move(float speed);

		/*
		Usage: Copy Assignment Operator
		Arguments: class object to copy
		Output: bool
		*/
		bool operator==(Bullet const& other) const;

	private:


	//Methods


		
	};
}
