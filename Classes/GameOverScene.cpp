#include "GameOverScene.h"
#include "GameScene.h"
#include "MainMenuScene.h"
#include "Definitions.h"

USING_NS_CC;

unsigned int score;

Scene* GameOverScene::createScene(unsigned int tempScore)
{
	score = tempScore;

    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameOverScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

//return length
int iToStr(char *ch, int num)
{
	if (!num)
	{
		ch[0] = '0';
		ch[1] = '\0';
		return 1;
	}

	int i = 0, tempNum = num;
	while (tempNum)
	{
		ch[i++] = tempNum % 10 + '0';
		tempNum /= 10;
	}
	std::reverse(ch, ch+i);
	ch[i] = '\0';
	return i;
}

// on "init" you need to initialize your instance
bool GameOverScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto backgroundSprite = Sprite::create("./ipadhd/Background.png");
    backgroundSprite->setPosition(visibleSize.width / 2.f + origin.x, visibleSize.height / 2.f + origin.y);

    this->addChild(backgroundSprite);

    //add menus
    auto retryItem = MenuItemImage::create("./ipadhd/Retry Button.png", "./ipadhd/Retry Button Clicked.png", CC_CALLBACK_1(GameOverScene::GoToGameScene, this));
    retryItem->setPosition(visibleSize.width / 2.f + origin.x, visibleSize.height * 3.f / 4.f + origin.y);

    auto mainMenuItem = MenuItemImage::create("./ipadhd/Menu Button.png", "./ipadhd/Menu Button Clicked.png", CC_CALLBACK_1(GameOverScene::GoToMainMenuScene, this));
    mainMenuItem->setPosition(visibleSize.width / 2.f + origin.x, visibleSize.height / 4.f + origin.y);

    auto menu = Menu::create(retryItem, mainMenuItem, NULL);
    menu->setPosition(Point::ZERO);

    this->addChild(menu);

    //save the scores, but not working
    UserDefault *def = UserDefault::getInstance();  
    auto highScore = def->getIntegerForKey("FLAPPYHIGHTSCORE");
    if (score > highScore)
    {
	    highScore = score;
	    def->setIntegerForKey("FLAPPYHIGHTSCORE", highScore);	    
    }

    //save the scores, too.
    char strHighRecord[38];
    int iHightRecord = 0, len;
    auto cfp = FileUtils::getInstance();
    std::string fileName = cfp->getWritablePath() + HIGHEST_SCORE_FILE;
    FILE *fp;
    if ( MyUtils::equ((fp = fopen(fileName.c_str(), "r")), NULL))
    {
	    fp = fopen(fileName.c_str(), "w+");
	    len = iToStr(strHighRecord, score);
	    iHightRecord = score;
	    fputs(strHighRecord, fp);
    }
    else
    {
	    len = fread(strHighRecord, 1, 50, fp);
	    strHighRecord[len] = '\0';
	    iHightRecord = atoi(strHighRecord);
    }
    
    if (iHightRecord < score)
    {
	    fclose(fp);
	    fopen(fileName.c_str(), "w");//clear the old file

	    iHightRecord = score;
	    len = iToStr(strHighRecord, iHightRecord);
	    strHighRecord[len] = '\0';
	    fputs(strHighRecord, fp);	    
    }

    fclose(fp);

    __String *tempScore = __String::createWithFormat("YOU SCORE: %i", score);
    auto finalScoe = Label::create();
    finalScoe->setString(tempScore->getCString());
    finalScoe->setSystemFontSize(visibleSize.height * SCORE_FONT_SIZE);
    finalScoe->setColor(Color3B::WHITE);
    finalScoe->setPosition(visibleSize.width * 0.5f + origin.x, visibleSize.height * 0.5f + origin.y + visibleSize.height * SCORE_FONT_SIZE * 0.6f);
    finalScoe->setAlignment(cocos2d::TextHAlignment::CENTER);

    //show the highest score
    __String *tempHighScore = __String::createWithFormat("HIGHEST: %i", iHightRecord);
    auto highScoreLabel = Label::create();
    highScoreLabel->setString(tempHighScore->getCString());
    highScoreLabel->setSystemFontSize(visibleSize.height * SCORE_FONT_SIZE);
    highScoreLabel->setColor(Color3B::RED);
    highScoreLabel->setPosition(visibleSize.width * 0.5f + origin.x, visibleSize.height * 0.5f + origin.y - visibleSize.height * SCORE_FONT_SIZE * 0.6f);
    highScoreLabel->setAlignment(cocos2d::TextHAlignment::CENTER);

    /*
    __String *tempScore = __String::createWithFormat("%i", score);
    auto currentScore = Label::createWithTTF(tempScore->getCString(), "./fonts/Marker Felt.ttf", visibleSize.height * SCORE_FONT_SIZE);
    currentScore->setPosition(visibleSize.width * 0.25 + origin.x, visibleSize.height * 0.5 + origin.y);
    */

    this->addChild(finalScoe);
    this->addChild(highScoreLabel);

    return true;
}

void GameOverScene::GoToMainMenuScene(cocos2d::Ref *sender)
{
	auto scene = MainMenuScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}

void GameOverScene::GoToGameScene(cocos2d::Ref *sender)
{
	auto scene = GameScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}