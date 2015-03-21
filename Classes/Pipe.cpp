#include "Pipe.h"
#include "Definitions.h"

USING_NS_CC;

Pipe::Pipe()
{
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
}

void Pipe::SpawnPipe(cocos2d::Layer *layer)
{
	CCLOG("SPAWN PIPE");

	auto topPipe = Sprite::create("./ipadhd/Pipe.png");
	auto bottomPipe = Sprite::create("./ipadhd/Pipe.png");

	auto topPipeBody = PhysicsBody::createBox(topPipe->getContentSize());
	auto bottomPipeBody = PhysicsBody::createBox(bottomPipe->getContentSize());

	auto random = CCRANDOM_0_1();
	random = clampf(random, LOWER_SCREEN_PIPE_THRESHOLD, UPPER_SCREEN_PIPE_THRESHOLD);

	auto topPipePosition = random * visibleSize.height + topPipe->getContentSize().height / 2.f;

	topPipeBody->setDynamic(false);
	bottomPipeBody->setDynamic(false);

	topPipeBody->setCollisionBitmask(OBSTACLE_COLLISION_BITMASK);
	bottomPipeBody->setCollisionBitmask(OBSTACLE_COLLISION_BITMASK);

	topPipeBody->setContactTestBitmask(true);
	bottomPipeBody->setContactTestBitmask(true);

	topPipe->setPhysicsBody(topPipeBody);
	bottomPipe->setPhysicsBody(bottomPipeBody);

	topPipe->setPosition(visibleSize.width + topPipe->getContentSize().width + origin.x, topPipePosition);

	int tempBottom = topPipePosition - Sprite::create("./ipadhd/Ball.png")->getContentSize().height *  PIPE_GAP - topPipe->getContentSize().height;

	bottomPipe->setPosition(topPipe->getPositionX(), topPipePosition - topPipe->getContentSize().height - Sprite::create("./ipadhd/Ball.png")->getContentSize().height * PIPE_GAP);

	layer->addChild(topPipe);
	layer->addChild(bottomPipe);

	auto topPipeAction = MoveBy::create(PIPE_MOVEMENT_SPEED * visibleSize.width, Vec2(-visibleSize.width * 1.5f, 0.f));

	auto bottomPipeAction = MoveBy::create(PIPE_MOVEMENT_SPEED * visibleSize.width, Vec2(-visibleSize.width * 1.5f, 0.f));

	topPipe->runAction(topPipeAction);
	bottomPipe->runAction(bottomPipeAction);

	//add the invisible point node to get points when the bird throught pipe gaps.
	const float tempPointSize = Sprite::create("./ipadhd/Ball.png")->getContentSize().height * PIPE_GAP;
	auto pointNode = Node::create();
	auto pointBody = PhysicsBody::createBox(Size(1, tempPointSize));

	pointBody->setDynamic(false);
	pointBody->setCollisionBitmask(POINT_COLLISION_BITMASK);
	pointBody->setContactTestBitmask(true);

	pointNode->setPhysicsBody(pointBody);
	pointNode->setPosition(topPipe->getPositionX(), topPipe->getPositionY() - topPipe->getContentSize().height / 2.f - tempPointSize / 2.f);

	layer->addChild(pointNode);
	
	auto pointNodeAction = MoveBy::create(PIPE_MOVEMENT_SPEED * visibleSize.width, Vec2(-visibleSize.width * 1.5f, 0.f));
	pointNode->runAction(pointNodeAction);
}