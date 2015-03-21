#ifndef __BIRD_H__
#define __BIRD_H__

#include "cocos2d.h"

class Bird
{
public:
	Bird(cocos2d::Layer *layer);

	void Fall();
	void Fly()
	{
		isFalling = false; 
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Sounds/Wing.mp3");
	};
	void StopFlying() { isFalling = true; };	
private:
	bool isFalling;
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;
	cocos2d::Sprite *flappyBird;
};

#endif // __BIRD_H__
