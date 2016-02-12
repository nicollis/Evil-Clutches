#include "OEntity.h"

std::vector<OEntity*> OEntity::sEntityList;

OEntity::OEntity()
{
	mEntityTexture = NULL;

	mEntityDimensions = new SDL_Rect({ 0,0,0,0 });

	mAnimationState = 0;

	mType = ENTITY_TYPE_GENERIC;
	isDeadFlag = false;
	mFlags = ENTITY_FLAG_GRAVITY;

	mSpeedX = 0;
	mSpeedY = 0;

	mCurrentFrameCol = 0;
	mCurrentFrameRow = 0;

	mColX = 0;
	mColY = 0;
	mColWidth = 0;
	mColHeight = 0;

	sEntityList.push_back(this);
}

OEntity::~OEntity()
{
	//do nothing; pure virtual
}

void OEntity::setDimensions(SDL_Rect* rect)
{
	mEntityDimensions = rect;
}

SDL_Rect* OEntity::getDimensions()
{
	return mEntityDimensions;
}

EntityTypes OEntity::getType()
{
	return mType;
}

int OEntity::getTypeId()
{
	return typeId;
}

void OEntity::setAnimationState(int state)
{
	mAnimationState = state;
}

int OEntity::getAnimationState()
{
	return mAnimationState;
}

bool OEntity::isDead()
{
	return this->isDeadFlag;
}

bool OEntity::onLoad(int id, int maxFrames)
{
	mEntityTexture = OTexture::sTextureMap.at(id);

	if (!mEntityTexture) return false;

	mEntityDimensions->w = mEntityTexture->getSpriteWidth();
	mEntityDimensions->h = mEntityTexture->getSpriteHeight();

	mAnimationController.setMaxFrames(maxFrames);

	return true;
}//end onLoad

void OEntity::onReset()
{
	//pure virtual method
}

void OEntity::onLoop()
{
	//pure virtual method
}

void OEntity::onRender()
{
	if (mEntityTexture == NULL) { return; }

	SDL_Rect clip =
	{
		mCurrentFrameCol * mEntityDimensions->w,
		(mCurrentFrameRow * mAnimationController.getCurrentFrame()) * mEntityDimensions->h ,
		mEntityDimensions->w,
		mEntityDimensions->h
	};

	mEntityTexture->render(
		mEntityDimensions->x - OCamera::sCameraControl.getX(),
		mEntityDimensions->y - OCamera::sCameraControl.getY(), 
		&clip);
}

void OEntity::onDistroy()
{
	for (int i = 0; i < sEntityList.size(); ++i)
	{
		if (sEntityList[i] == this)
		{
			sEntityList.erase(sEntityList.begin() + i);
			delete this;
		}
	}
}

void OEntity::onCleanup()
{
	mEntityTexture = NULL;
}

void OEntity::onAnimate()
{
	//pure virtual function
}

bool OEntity::onCollision(OEntity* entity)
{
	return true;
}

void OEntity::onMove(float moveX, float moveY)
{
	//pure virtual method
}//end onMove method

bool OEntity::checkForCollisions()
{
	bool results = false;
	for (int i = 0; i < sEntityList.size(); ++i)
	{
		if (this == sEntityList.at(i)) continue;

		if (checkCollision(*this->getDimensions(), *sEntityList.at(i)->getDimensions()))
		{
			OEntityCollision::onRegister(this, sEntityList.at(i));
			results = true;
		}
	}
	return results;
}