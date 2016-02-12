#include "OEntity.h"

std::vector<OEntityCollision*> OEntityCollision::sCollisionList;

OEntityCollision::OEntityCollision()
{
	this->entityA = NULL;
	this->entityB = NULL;
}

void OEntityCollision::onCleanup()
{
	this->entityA = NULL;
	this->entityB = NULL;
}

void OEntityCollision::onRegister(OEntity* a, OEntity* b)
{
	OEntityCollision* temp = new OEntityCollision();

	temp->entityA = a;
	temp->entityB = b;

	sCollisionList.push_back(temp);
}