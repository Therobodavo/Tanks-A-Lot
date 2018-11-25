//DSA2
//Programmed by David Knolls
//CPP for OcTree Class
//Creates an OcTree for spatia Optimization

#include "OcTree.h"


//Use for root
OcTree::OcTree(int maxBranches)
{
	//Set default values
	index = 0;
	size = 40;
	int branch = 0;
	vector3 center = vector3(0, 0, 0);

	//Set instance for manager
	manager = MyEntityManager::GetInstance();


	//Create this square

	std::vector<vector3> points;

	//Bottom points
	points.push_back(vector3(size, -size, size));
	points.push_back(vector3(size, -size, -size));
	points.push_back(vector3(-size, -size, size));
	points.push_back(vector3(-size, -size, -size));

	//Top points
	points.push_back(vector3(size, size, size));
	points.push_back(vector3(size, size, -size));
	points.push_back(vector3(-size, size, size));
	points.push_back(vector3(-size, size, -size));

	//Create RigidBody based off points
	rb = new MyRigidBody(points);

	//If Entity is in this octant
	for (int i = 0; i < manager->GetEntityCount(); i++)
	{
		if (rb->IsColliding(manager->GetEntity(i)->GetRigidBody()))
		{
			indexObjs.push_back(i);
		}
	}
	//if > 1 entity in this octant

	if (indexObjs.size() > 1 && branch < maxBranches)
	{
		//Create all nodes for next branch
		subParts.push_back(new OcTree(index + 1, size / 2, this, branch + 1, maxBranches, vector3(center.x - (size / 2), center.y + (size / 2), center.z - (size / 2))));
		subParts.push_back(new OcTree(index + 2, size / 2, this, branch + 1, maxBranches, vector3(center.x - (size / 2), center.y + (size / 2), center.z + (size / 2))));
		subParts.push_back(new OcTree(index + 3, size / 2, this, branch + 1, maxBranches, vector3(center.x + (size / 2), center.y + (size / 2), center.z - (size / 2))));
		subParts.push_back(new OcTree(index + 4, size / 2, this, branch + 1, maxBranches, vector3(center.x + (size / 2), center.y + (size / 2), center.z + (size / 2))));
		subParts.push_back(new OcTree(index + 5, size / 2, this, branch + 1, maxBranches, vector3(center.x - (size / 2), center.y - (size / 2), center.z - (size / 2))));
		subParts.push_back(new OcTree(index + 6, size / 2, this, branch + 1, maxBranches, vector3(center.x - (size / 2), center.y - (size / 2), center.z + (size / 2))));
		subParts.push_back(new OcTree(index + 7, size / 2, this, branch + 1, maxBranches, vector3(center.x + (size / 2), center.y - (size / 2), center.z - (size / 2))));
		subParts.push_back(new OcTree(index + 8, size / 2, this, branch + 1, maxBranches, vector3(center.x + (size / 2), center.y - (size / 2), center.z + (size / 2))));
	}

}

//For all nodes that aren't the root
OcTree::OcTree(int index, int size, OcTree* parent, int branch, int maxBranches, vector3 center)
{
	//Set variables from parameters
	this->index = index;
	this->size = size;
	this->parent = parent;

	//Get instance of the manager
	manager = MyEntityManager::GetInstance();

	//Create this square
	std::vector<vector3> points;

	//Bottom points
	points.push_back(vector3(size,-size,size) + center);
	points.push_back(vector3(size, -size, -size) + center);
	points.push_back(vector3(-size, -size, size) + center);
	points.push_back(vector3(-size, -size, -size) + center);

	//Top points
	points.push_back(vector3(size, size, size) + center);
	points.push_back(vector3(size, size, -size) + center);
	points.push_back(vector3(-size, size, size) + center);
	points.push_back(vector3(-size, size, -size) + center);

	//Create RigidBody based off points
	rb = new MyRigidBody(points);


	//If Entity is in this octant
	for each(int i in parent->indexObjs)
	{
		if (rb->IsColliding(manager->GetEntity(i)->GetRigidBody()))
		{
			indexObjs.push_back(i);
			if (branch == maxBranches)
			{
				manager->GetEntity(i)->AddDimension(index);
			}
		}
	}
	//if > 1 entity in this octant

	if (indexObjs.size() > 1 && branch < maxBranches)
	{
		//Create all nodes under this branch
		subParts.push_back(new OcTree(index + 1, size / 2, this, branch + 1, maxBranches, vector3(center.x - (size / 2),center.y + (size / 2),center.z - (size / 2))));
		subParts.push_back(new OcTree(index + 1, size / 2, this, branch + 1, maxBranches, vector3(center.x - (size / 2), center.y + (size / 2), center.z + (size / 2))));
		subParts.push_back(new OcTree(index + 1, size / 2, this, branch + 1, maxBranches, vector3(center.x + (size / 2), center.y + (size / 2), center.z - (size / 2))));
		subParts.push_back(new OcTree(index + 1, size / 2, this, branch + 1, maxBranches, vector3(center.x + (size / 2), center.y + (size / 2), center.z + (size / 2))));
		subParts.push_back(new OcTree(index + 1, size / 2, this, branch + 1, maxBranches, vector3(center.x - (size / 2), center.y - (size / 2), center.z - (size / 2))));
		subParts.push_back(new OcTree(index + 1, size / 2, this, branch + 1, maxBranches, vector3(center.x - (size / 2), center.y - (size / 2), center.z + (size / 2))));
		subParts.push_back(new OcTree(index + 1, size / 2, this, branch + 1, maxBranches, vector3(center.x + (size / 2), center.y - (size / 2), center.z - (size / 2))));
		subParts.push_back(new OcTree(index + 1, size / 2, this, branch + 1, maxBranches, vector3(center.x + (size / 2), center.y - (size / 2), center.z + (size / 2))));
	}
	//Make 8 Octants
}

//Display, renders current node and other nodes in the branch
void OcTree::Display()
{
	//If more than 1 object
	if (indexObjs.size() > 1)
	{
		rb->SetColorColliding(C_WHITE);
		rb->AddToRenderList();
	}

	//Call nodes Display in this branch
	for each(OcTree* i in subParts)
	{
		i->Display();
	}
}

//Remove all pointers when program ends
OcTree::~OcTree()
{
	delete(parent);
	delete(rb);
}
