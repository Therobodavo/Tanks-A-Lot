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