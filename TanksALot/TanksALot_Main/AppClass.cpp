#include "AppClass.h"
#include <iostream>
using namespace Simplex;
using namespace std;
void Application::InitVariables(void)
{
	//Set the position and target of the camera
	m_pCameraMngr->SetPositionTargetAndUp(vector3(-0.0f, 3, 0), vector3(1.0f, 3, 0), AXIS_Y);		//Up


	player = new Player();
	
	
	m_pLightMngr->SetPosition(vector3(0.0f, 3.0f, 13.0f), 1); //set the position of first light (0 is reserved for ambient light)

	m_pEntityMngr->AddEntity("Minecraft\\ModelTB.obj", "PlayerBase");
	m_pEntityMngr->AddEntity("Minecraft\\ModelTT.obj", "PlayerTop");
	m_pEntityMngr->AddEntity("Minecraft\\ModelTH.obj", "PlayerHead");
	m_pEntityMngr->AddEntity("Minecraft\\Cube.obj", "Floor");
	


	m_pEntityMngr->GetEntity(3)->SetModelMatrix(glm::scale(vector3(1000, 1, 1000)));
	
	//need to do this properway
	for (size_t i = 0; i < 20; i++)
	{
		m_pEntityMngr->AddEntity("Minecraft\\ModelTB.obj", "PlayerBase");
		m_pEntityMngr->AddEntity("Minecraft\\ModelTT.obj", "PlayerTop");
		m_pEntityMngr->AddEntity("Minecraft\\ModelTH.obj", "PlayerHead");
		eniTanks.push_back(new EnemyTank(player));
	
	}
	
	//m_pEntityMngr->Update();
}
void Application::Update(void)
{
	//Update the system so it knows how much time has passed since the last call
	m_pSystem->Update();

	//Is the ArcBall active?
	ArcBall();

	//Is the first person camera active?
	CameraRotation();

	// --- Update Timer ---
	//Set Clock (Static)
	static uint uClock = m_pSystem->GenClock(); //generate a new clock for that timer
	//Update Timer
	ftimer = m_pSystem->GetDeltaTime(uClock);
	// --- Update Timer ---


	m_pEntityMngr->GetEntity(0)->SetModelMatrix(player->getModelBase()); //putting model in entity
	m_pEntityMngr->GetEntity(1)->SetModelMatrix(player->getModelTop()); // creating top part of tank
	m_pEntityMngr->GetEntity(2)->SetModelMatrix(player->getModelHead()); // creating top part of tank

	
	int check = 4;
	//testing
	for each (EnemyTank* eni in eniTanks)
	{
		m_pEntityMngr->GetEntity(check)->SetModelMatrix(eni->getModelBase()); //putting model in entity
		m_pEntityMngr->GetEntity(check + 1)->SetModelMatrix(eni->getModelTop()); // creating top part of tank
		m_pEntityMngr->GetEntity(check + 2)->SetModelMatrix(eni->getModelHead()); // creating top part of tank
		eni->aiMovement();
		check += 3;
		//Check reload status, Fire if able.
		if (eni->aiReloadStatus(ftimer) == true)
		{
			FireBulletEnemy(eni);
		}
	}


	m_pCameraMngr->SetPositionTargetAndUp(player->getCamPos(), player->getTargetPos(), AXIS_Y); //setting the cordinates for the camera




	//Bullet Code
	
	//Update ReloadTimer;
	ReloadTimer -= ftimer;
	if (ReloadTimer < 0)ReloadTimer = 0;
	//Update Bullet Models, check LifeTimer
	for (int i = 0; i < BulletTracker.size(); i++)
	{
		BulletTracker[i].Move(0.5f);
		m_pEntityMngr->SetModelMatrix(BulletTracker[i].model, BulletTracker[i].ID);

		//Update Bullet Life
		BulletTracker[i].BulletLife -= ftimer;
		//Delete if expired
		if (BulletTracker[i].BulletLife <= 0)
		{
			DeleteBullet(BulletTracker[i]);
			i--;
		}
	}

	//End Bullet Code


	//Update Entity Manager
	//m_pEntityMngr->Update();

	//Add objects to render list
	m_pEntityMngr->AddEntityToRenderList(-1, true);
}
void Application::Display(void)
{
	// Clear the screen
	ClearScreen();
	
	// draw a skybox
	m_pMeshMngr->AddSkyboxToRenderList();
	
	//render list call
	m_uRenderCallCount = m_pMeshMngr->Render();

	//clear the render list
	m_pMeshMngr->ClearRenderList();
	
	//draw gui,
	DrawGUI();
	
	//end the current frame (internally swaps the front and back buffers)
	m_pWindow->display();
}
void Application::Release(void)
{
	//release GUI
	ShutdownGUI();

	//Deletes each pointer in eniTanks(sets to Null so don't have to worry about index confusion)
	for (int i = 0; i < eniTanks.size(); i++)
	{
		SafeDelete(eniTanks[i]);
	}

	/* - - -Doesn't work, deletes the "eni" made by the for each statement, doesn't change eniTanks at all- - -
	for each (EnemyTank* eni in eniTanks)
	{
		SafeDelete(eni);
	}
	*/

	SafeDelete(player);
}