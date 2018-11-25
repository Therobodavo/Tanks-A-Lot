//DSA2
//Programmed by David Knolls
//Header for OcTree Class
//Creates an OcTree for spatia Optimization

#pragma once
#include<iostream>
#include<vector>
#include "MyEntity.h"
#include "MyEntityManager.h"
using namespace Simplex;

class OcTree
{
public:
	OcTree(int maxBranches); //Root OcTree Creation
	OcTree(int index, int size, OcTree * parent, int branch, int maxBranches, vector3 center); //Main OcTree nodes
	void Display(); //Used to display octree
	~OcTree(); //used to remove octree
	int size = 100; //Initial size, changed in the root method
	int index = 0; //initial index, used for root index value
	OcTree* parent = nullptr; //pointer to parent node, not used in root
	MyEntityManager* manager = nullptr; //instance of Entity Manager
	std::vector<OcTree*> subParts; //list of all sections of the current branch based off this node
	std::vector<int> indexObjs; //index of all objects in this nodes area
	MyRigidBody* rb = nullptr; //RigidBody used for checking collision
private:

};

