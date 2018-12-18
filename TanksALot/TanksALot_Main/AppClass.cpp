#include "AppClass.h"
#include <iostream>
using namespace Simplex;
using namespace std;
std::vector<String> destroyList;

//Adds entity to render queue
void Application::AddToDelete(String s)
{
	bool isHere = false;

	//loops to make sure only one of each object is in delete queue
	for (int i = 0; i < destroyList.size(); i++)
	{
		if (destroyList[i] == s)
		{
			isHere = true;
			return;
		}
	}

	//If  it's the only one
	if (!isHere)
	{
		destroyList.push_back(s);
		score += 10;
	}
}

//All collision code here
void Application::UpdateCollision(void)
{
	MyEntityManager* manager = MyEntityManager::GetInstance();

	destroyList.clear();

	//Clear all collisions
	for (uint i = 0; i < manager->GetEntityCount(); i++)
	{
		manager->GetEntity(i)->ClearCollisionList();
	}

	//check collisions
	for (uint i = 0; i < manager->GetEntityCount(); i++)
	{
		for (uint j = 0; j < manager->GetEntityCount(); j++)
		{
			String id = manager->GetEntity(i)->GetUniqueID();
			String id2 = manager->GetEntity(j)->GetUniqueID();

			if (id == "Floor" || id2 == "Floor" || i == j || (id[0] == id2[0] && id.substr(6) == id2.substr(6)) || (id[0] == 'P' && id2[0] == 'P'))
			{
				continue;
			}

			int findcheck = id2.find("Player");
			int findcheck2 = !id2.find("Player");
			if (manager->GetEntity(i)->SharesDimension(manager->GetEntity(j)))
			{
				bool isCol = manager->GetEntity(i)->IsColliding(manager->GetEntity(j));
				if (isCol)
				{


					if (!id.find("Bullet"))
					{
						continue;
						//if ((BulletTracker.size() - 1) == j)
						//{
						//	//if (!BulletTracker[j].source.find("Player"))
						//	//{
						//	//	continue;
						//	//}
						//	////if ( (BulletTracker[j].source != "PlayerA" && !id2.find("Enemy")))
						//	////{
						//	////	continue;
						//	////}
						//	if (!id2.find("Player") && !BulletTracker[j].source.find("Player") )//AND bullet.shooter != Player
						//	{
						//		//Hurt Player
						//		//Destroy Bullet
						//		AddToDelete(id);
						//	}
						//	else if (!id2.find("Enemy"))//AND bullet.shooter != Enemy
						//	{
						//		//Hurt Enemy
						//		//Destroy
						//		AddToDelete(id);
						//	}
						//	else if (!id2.find("Wall"))
						//	{
						//		//Destroy Bullet
						//		AddToDelete(id);
						//	}
						//	else if (!id2.find("Bullet"))
						//	{
						//		//Destroy both bullets
						//		AddToDelete(id);
						//		AddToDelete(id2);
						//	}
						//}

						
					}
					else if (!id.find("Enemy"))
					{
						if (!id2.find("Player"))//AND bullet.shooter != Player
						{

							//Hurt Player
							isAlive = false;
							//Destroy Enemy


							if (id[5] == 'A')
							{
								AddToDelete(id);
								AddToDelete(manager->GetEntity(i + 1)->GetUniqueID());
								AddToDelete(manager->GetEntity(i + 2)->GetUniqueID());
							}
							else if (id[5] == 'B')
							{
								AddToDelete(id);
								AddToDelete(manager->GetEntity(i - 1)->GetUniqueID());
								AddToDelete(manager->GetEntity(i + 1)->GetUniqueID());
							}
							else if (id[5] == 'C')
							{
								AddToDelete(id);
								AddToDelete(manager->GetEntity(i - 1)->GetUniqueID());
								AddToDelete(manager->GetEntity(i - 2)->GetUniqueID());
							}
						}
						else if (!id2.find("Enemy"))//AND bullet.shooter != Enemy
						{
							//Hurt both Enemies

							if (id[5] == 'A')
							{
								AddToDelete(id);
								AddToDelete(manager->GetEntity(i + 1)->GetUniqueID());
								AddToDelete(manager->GetEntity(i + 2)->GetUniqueID());
							}
							else if (id[5] == 'B')
							{
								AddToDelete(id);
								AddToDelete(manager->GetEntity(i - 1)->GetUniqueID());
								AddToDelete(manager->GetEntity(i + 1)->GetUniqueID());
							}
							else if (id[5] == 'C')
							{
								AddToDelete(id);
								AddToDelete(manager->GetEntity(i - 1)->GetUniqueID());
								AddToDelete(manager->GetEntity(i - 2)->GetUniqueID());
							}

							if (id2[5] == 'A')
							{
								AddToDelete(id2);
								AddToDelete(manager->GetEntity(j + 1)->GetUniqueID());
								AddToDelete(manager->GetEntity(j + 2)->GetUniqueID());
							}
							else if (id2[5] == 'B')
							{
								AddToDelete(id2);
								AddToDelete(manager->GetEntity(j - 1)->GetUniqueID());
								AddToDelete(manager->GetEntity(j + 1)->GetUniqueID());
							}
							else if (id2[5] == 'C')
							{
								AddToDelete(id2);
								AddToDelete(manager->GetEntity(j - 1)->GetUniqueID());
								AddToDelete(manager->GetEntity(j - 2)->GetUniqueID());
							}
						}
						else if (!id2.find("Wall"))
						{
							//move back/ obstacle avoidance?
						}
						else if (!id2.find("Bullet") )
						{
							//Destroy enemy

							if (id[5] == 'A')
							{
								AddToDelete(id);
								AddToDelete(manager->GetEntity(i + 1)->GetUniqueID());
								AddToDelete(manager->GetEntity(i + 2)->GetUniqueID());
							}
							else if (id[5] == 'B')
							{
								AddToDelete(id);
								AddToDelete(manager->GetEntity(i - 1)->GetUniqueID());
								AddToDelete(manager->GetEntity(i + 1)->GetUniqueID());
							}
							else if (id[5] == 'C')
							{
								AddToDelete(id);
								AddToDelete(manager->GetEntity(i - 1)->GetUniqueID());
								AddToDelete(manager->GetEntity(i - 2)->GetUniqueID());
							}

							//Destroy bullet
							AddToDelete(id2);
						}
					}
					else if (id.find("Player"))
					{
						if (id2.find("Wall"))
						{
							//move back/out of collision
						}
					}

				}
			}
			

		}
	}

	for (int i = 0; i < destroyList.size(); i++)
	{
		
		if (!destroyList[i].find("EnemyA"))
		{

			for (int j = 0; j < eniTanks.size(); j++)
			{
				if (eniTanks[j]->id == destroyList[i])
				{
					eniTanks.erase(eniTanks.begin() + j);
					manager->RemoveEntity(destroyList[i]);
					j--;
				}
			}

		}
		else if (!destroyList[i].find("Bullet"))
		{
			for (int j = 0; j < BulletTracker.size(); j++)
			{
				if (BulletTracker[j].ID == destroyList[i])
				{
					std::cout << "DELETE BULLET" << std::endl;
					DeleteBullet(BulletTracker[j]);
				}
			}
			
		}
		else 
		{
			manager->RemoveEntity(destroyList[i]);
		}
		

	}

}
void Application::InitVariables(void)
{
	numEnemies = 0;
	showOc = false;
	score = 0;
	//Set the position and target of the camera
	m_pCameraMngr->SetPositionTargetAndUp(vector3(-0.0f, 3, 0), vector3(1.0f, 3, 0), AXIS_Y);		//Up


	player = new Player();
	
	m_pLightMngr->SetPosition(vector3(0.0f, 3.0f, 13.0f), 1); //set the position of first light (0 is reserved for ambient light)

	m_pEntityMngr->AddEntity("Minecraft\\ModelTB.obj", "PlayerA");
	m_pEntityMngr->AddEntity("Minecraft\\ModelTT.obj", "PlayerB");
	m_pEntityMngr->AddEntity("Minecraft\\ModelTH.obj", "PlayerC");
	m_pEntityMngr->AddEntity("Minecraft\\Cube.obj", "Floor");


	m_pEntityMngr->GetEntity(3)->SetModelMatrix(glm::scale(vector3(1000, 1, 1000)));
	
	//need to do this properway
	for (size_t i = 0; i < 20; i++)
	{
		m_pEntityMngr->AddEntity("Minecraft\\ModelTB.obj", "EnemyA" + std::to_string(numEnemies));
		m_pEntityMngr->AddEntity("Minecraft\\ModelTH.obj", "EnemyB" + std::to_string(numEnemies));
		m_pEntityMngr->AddEntity("Minecraft\\ModelTT.obj", "EnemyC" + std::to_string(numEnemies));
		numEnemies += 1;
		EnemyTank* e = new EnemyTank(player);
		e->id = "EnemyA" + std::to_string(numEnemies);
		eniTanks.push_back(e);
	
	}
	
	
	//m_pEntityMngr->Update();
	//UpdateCollision();
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

	if (isAlive)
	{
		m_pEntityMngr->GetEntity(0)->SetModelMatrix(player->getModelBase()); //putting model in entity
		m_pEntityMngr->GetEntity(1)->SetModelMatrix(player->getModelTop()); // creating top part of tank
		m_pEntityMngr->GetEntity(2)->SetModelMatrix(player->getModelHead()); // creating top part of tank
	}


	
	int check = 4;
	//testing
	for each (EnemyTank* eni in eniTanks)
	{
		m_pEntityMngr->SetModelMatrix(eni->getModelBase(), ("EnemyA" +  eni->id.substr(6) ));
		m_pEntityMngr->SetModelMatrix(eni->getModelHead(), ("EnemyB" + eni->id.substr(6)));
		m_pEntityMngr->SetModelMatrix(eni->getModelTop(), ("EnemyC" + eni->id.substr(6)));



		eni->aiMovement();
		//check += 3;
		//Check reload status, Fire if able.
		if (eni->aiReloadStatus(0.02f) == true)
		{
			//FireBulletEnemy(eni);
		}
	}


	m_pCameraMngr->SetPositionTargetAndUp(player->getCamPos(), player->getTargetPos(), AXIS_Y); //setting the cordinates for the camera


	if (!isAlive)
	{
		m_pEntityMngr->ReleaseInstance();

	}

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

	//std::cout << "TESTHI" << m_pEntityMngr->GetEntity(4)->GetUniqueID() << std::endl;
	//Update Entity Manager
	//m_pEntityMngr->Update();

	m_pRoot = new OcTree(8);
	UpdateCollision();
	//for (int i = 0; i < m_pEntityMngr->GetEntityCount(); i++)
	//{
	//	std::cout << "TESTHI   " << m_pEntityMngr->GetEntity(i)->GetUniqueID() << std::endl;
	//}
	//std::cout << "TESTBYE" << m_pEntityMngr->GetEntity(4)->GetUniqueID() << std::endl;
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

	if (showOc)
	{
		m_pRoot->Display();
	}
	
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