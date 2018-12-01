#include "AppClass.h"
using namespace Simplex;
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


	m_pEntityMngr->GetEntity(3)->SetModelMatrix(glm::scale(vector3(50, 1, 50)));

	
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


	m_pEntityMngr->GetEntity(0)->SetModelMatrix(player->getModelBase()); //putting model in entity
	m_pEntityMngr->GetEntity(1)->SetModelMatrix(player->getModelTop()); // creating top part of tank
	m_pEntityMngr->GetEntity(2)->SetModelMatrix(player->getModelHead()); // creating top part of tank

	m_pCameraMngr->SetPositionTargetAndUp(player->getCamPos(), player->getTargetPos(), AXIS_Y); //setting the cordinates for the camera


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
}