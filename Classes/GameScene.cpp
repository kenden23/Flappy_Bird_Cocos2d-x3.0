#include "GameScene.h"
#include "Definitions.h"
#include "GameOverScene.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    scene->getPhysicsWorld()->setGravity(Vect(0.f, 0.f));
    
    // 'layer' is an autorelease object
    auto layer = GameScene::create();
    layer->setPhysicsWorld(scene->getPhysicsWorld());

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //set the background image
    auto backgroundSprite = Sprite::create("./ipadhd/Background.png");

    backgroundSprite->setPosition(CENTER_POSITION_OF_GAME_SCREEN);

    this->addChild(backgroundSprite);

    //
    auto edgeBody = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3.f);
    edgeBody->setCollisionBitmask(OBSTACLE_COLLISION_BITMASK);
    edgeBody->setContactTestBitmask(true);

    auto edgeNode = Node::create();
    edgeNode->setPosition(CENTER_POSITION_OF_GAME_SCREEN);
    edgeNode->setPhysicsBody(edgeBody);
    this->addChild(edgeNode);

    //schedule pipe spawning
    this->schedule(schedule_selector(GameScene::spawnPipe), PIPE_SPAWN_FREQUENCY * visibleSize.width);

    //add bird
    std::unique_ptr<Bird> birdTemp(new Bird(this));
    bird = std::move(birdTemp);

    //handle contact physics
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

    //handle touch event
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);
    touchListener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);   

    score = 0;
    __String *tempScore = __String::createWithFormat("%i", score);
    
    scoreLabel = Label::create();
    scoreLabel->setString(tempScore->getCString());
    //scoreLabel->setContentSize(Size(visibleSize.width * SCORE_FONT_SIZE, visibleSize.height * SCORE_FONT_SIZE));
    scoreLabel->setSystemFontSize(visibleSize.height * SCORE_FONT_SIZE);
	    //Label::createWithTTF(tempScore->getCString(), "./fonts/Marker Felt.ttf", visibleSize.height * SCORE_FONT_SIZE);
    scoreLabel->setColor(Color3B::WHITE);
    scoreLabel->setPosition(visibleSize.width * 0.5f + origin.x, visibleSize.height * 0.75f + origin.y);

    this->addChild(scoreLabel, 10000);

    this->scheduleUpdate();

    return true;
}


void GameScene::spawnPipe(float dt)
{
	pipe.SpawnPipe(this);
}

bool GameScene::onContactBegin(cocos2d::PhysicsContact &contact)
{
	PhysicsBody *a = contact.getShapeA()->getBody();
	PhysicsBody *b = contact.getShapeB()->getBody();

	if ( (MyUtils::equ(BIRD_COLLISION_BITMASK, a->getCollisionBitmask()) && MyUtils::equ(OBSTACLE_COLLISION_BITMASK, b->getCollisionBitmask())) || (MyUtils::equ(BIRD_COLLISION_BITMASK, b->getCollisionBitmask()) && MyUtils::equ(OBSTACLE_COLLISION_BITMASK, a->getCollisionBitmask())) )
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Sounds/Hit.mp3");

		CCLOG("SCORE: %i", score);
		auto scene = GameOverScene::createScene(score);
		Director::getInstance()->replaceScene( TransitionFade::create(TRANSITION_TIME, scene));
	}
	else if ( (MyUtils::equ(BIRD_COLLISION_BITMASK, a->getCollisionBitmask()) && MyUtils::equ(POINT_COLLISION_BITMASK, b->getCollisionBitmask())) || (MyUtils::equ(BIRD_COLLISION_BITMASK, b->getCollisionBitmask()) && MyUtils::equ(POINT_COLLISION_BITMASK, a->getCollisionBitmask())) )
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Sounds/Point.mp3");

		score++;
		__String *tempScore = __String::createWithFormat("%i", score);
		scoreLabel->setString(tempScore->getCString());
	}

	return true;
}

bool GameScene::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *eve)
{
	bird->Fly();
	this->scheduleOnce(schedule_selector(GameScene::StopFlying), (float)BIRD_FLY_DURATION);

	return true;
}

void GameScene::StopFlying(float dt)
{
	bird->StopFlying();
}

void GameScene::update(float dt)
{
	bird->Fall();
}