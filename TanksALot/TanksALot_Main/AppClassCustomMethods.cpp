#include "AppClass.h"
using namespace Simplex;

void Application::DeleteBullet(Bullet bullet)
{
//Find Bullet in Tracke
	// Find Bullet in vector and get iterator
	auto iterator = std::find(BulletTracker.begin(), BulletTracker.end(), bullet);
	//Find Bullet index using iterator
	int index = distance(BulletTracker.begin(), iterator);
//Delete Bullet
	//Remove BulletEntity from EntityManager
	m_pEntityMngr->RemoveEntity(bullet.ID);
	//Remove Bullet from Tracker
	BulletTracker.erase(BulletTracker.begin() + index);
}

void Application::FireBulletPlayer()
{
	if (ReloadTimer <= 0)
	{
		//Prep ID
		std::string id = "Bullet" + std::to_string(BulletNextID);
		//Create Bullet at Turret
		Bullet newPBullet = Bullet(player->getModelTop(), id);
		newPBullet.source = "PlayerA";
		newPBullet.bulletTeam = 0;
		//Update IDTracker
		BulletNextID++;
		//Add Bullet to BulletTracker
		BulletTracker.push_back(newPBullet);
		//Add Bullet to EntityManager
		m_pEntityMngr->AddEntity("Minecraft\\Cube.obj", newPBullet.ID);
		//ResetReloadTimer
		ReloadTimer = ReloadTimerMax;
	}
}
void Application::FireBulletEnemy(EnemyTank* Source)
{
	//Prep ID
	std::string id = "Bullet" + std::to_string(BulletNextID);
	//Create Bullet at Turret
	Bullet newBullet = Bullet(Source->getModelTop(), id);
	newBullet.source = Source->id;
	newBullet.bulletTeam = 1;
	//Update IDTracker
	BulletNextID++;
	//Add Bullet to BulletTracker
	BulletTracker.push_back(newBullet);
	//Add Bullet to EntityManager
	m_pEntityMngr->AddEntity("Minecraft\\Cube.obj", newBullet.ID);
}

