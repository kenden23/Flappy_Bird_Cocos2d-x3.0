#include "Bird.h"
#include "Definitions.h"

USING_NS_CC;

Bird::Bird(Layer *layer):isFalling(true)
{
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	flappyBird = Sprite::create("./ipadhd/Ball.png");
	flappyBird->setPosition(CENTER_POSITION_OF_GAME_SCREEN);

	auto flappyBody = PhysicsBody::createCircle(flappyBird->getContentSize().width / 2.f);

	flappyBody->setCollisionBitmask(BIRD_COLLISION_BITMASK);
	flappyBody->setContactTestBitmask(true);

	flappyBird->setPhysicsBody(flappyBody);

	layer->addChild(flappyBird, 100);
}

void Bird::Fall()
{
	if (isFalling)
	{
		flappyBird->setPositionX(visibleSize.width / 2.f + origin.x);
		flappyBird->setPositionY(flappyBird->getPositionY() - BIRD_FALLING_SPEED * visibleSize.height);
	}
	else
	{
		flappyBird->setPositionX(visibleSize.width / 2.f + origin.x);
		flappyBird->setPositionY(flappyBird->getPositionY() + BIRD_FALLING_SPEED * visibleSize.height);
	}
}