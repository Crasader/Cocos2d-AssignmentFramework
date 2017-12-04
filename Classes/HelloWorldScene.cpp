#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "SceneManager.h"
USING_NS_CC;

// Because cocos2d-x requres createScene() to be static, we need to make other non-pointer members static
std::map<cocos2d::EventKeyboard::KeyCode,
	std::chrono::high_resolution_clock::time_point> HelloWorld::Key_map;

Scene* HelloWorld::createScene()
{
	auto scene = Scene::createWithPhysics();
	auto layer = HelloWorld::create();
	scene->addChild(layer);
	return scene;
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    

	//Creating a node container to store non-movable variables
	auto nodeItems = Node::create();
	nodeItems->setName("nodeItems");

	//Creating a sprite object to load the image
	//auto sprite = Sprite::create("ZigzagGrass_Mud_Round.png");
	int sX = 0;
	int sY = playingSize.height / 2;

	//int count = visibleSize.width - (sprite->getContentSize().height);
	//int count = std::ceil(visibleSize.width / sprite->getContentSize().width);



	bgNode = Node::create();
	bgNode->setName("bg Node Main");

	auto bgFirst = Sprite::create("bg5.jpg");
	//bgNode->setAnchorPoint(Vec2::ZERO);
	bgFirst->setAnchorPoint(Vec2::ZERO);
	bgSize.setPoint(bgFirst->getContentSize().width, bgFirst->getContentSize().height);
	bgX = 0;
	bgY = 0;
	bgFirst->setPosition(Vec2(bgX, bgY));
	//bgX += bgFirst->getContentSize().width;
	bgFirst->setName("FirstBackground");
	bgNode->addChild(bgFirst);

	auto bgSecd = Sprite::create("bg5.jpg");
	bgSecd->setAnchorPoint(Vec2::ZERO);
	bg2X = 0;
	bg2Y = bgSecd->getContentSize().height;
	bgSecd->setPosition(Vec2(bg2X, bg2Y));
	//bg2X += bgSecd->getContentSize().width;
	bgSecd->setName("SecdBackground");
	bgNode->addChild(bgSecd);

	this->addChild(bgNode, 0);

	auto hpbar_frame = Sprite::create("fullbar.jpg");
	hpbar_frame->setAnchorPoint(Vec2::ZERO);
	float hppos_x = getContentSize().width * 0.01f;
	float hppos_y = getContentSize().height * 0.01f;
	hpbar_frame->setPosition(Vec2(hppos_x, hppos_y));
	hpbar_frame->setName("hpFrame");

	this->addChild(hpbar_frame, 2);


	auto powerup_frame = Sprite::create("powerupEmpty.jpg");
	powerup_frame->setAnchorPoint(Vec2::ZERO);
	float PUpos_x = getContentSize().width * 0.85f;
	float PUpos_y = getContentSize().height * 0.005f;
	powerup_frame->setPosition(Vec2(PUpos_x, PUpos_y));
	powerup_frame->setName("pwrupFrame");

	this->addChild(powerup_frame, 2);

	//int count = visibleSize.width - (sprite->getContentSize().height);
	//int bgcount = std::ceil(visibleSize.width / bg->getContentSize().width);

	//for (int i = 0; i < bgcount; i++)
	//{
	
	//}

	//Setting anchor point and position of your object (Bottom Left)
	//sprite->setAnchorPoint(Vec2::ZERO);
	//sprite->setPosition(0, visibleSize.height / 2);
	
	//Add object into the node container
	//nodeItems->addChild(sprite, 0);
	//Add the note container into the scene graph
	this->addChild(nodeItems, 1);

	//Create node container for Sprites
	auto spriteNode = Node::create();
	spriteNode->setName("spriteNode");
	//Load Sprite
	auto mainSprite = Sprite::create("Blue_Front1.png");
	//mainSprite->setAnchorPoint(Vec2(0, 0));
	mainSprite->setPosition(300, (visibleSize.height - playingSize.height * 0.5f));
	mainSprite->setName("mainSprite");
	{
		auto physicsbody = PhysicsBody::createBox(Size(mainSprite->getContentSize().width, mainSprite->getContentSize().height), PhysicsMaterial(0.01f, 1.0f, 0.0f));
		//physicsbody->setDynamic(false);
		mainSprite->addComponent(physicsbody);
	}
	//Add the sprite into the scene
	spriteNode->addChild(mainSprite, 1);
	this->addChild(spriteNode, 1);

	{
		
		//auto testbox = Sprite::create("ZigzagForest_Square.png");
		//testbox->setName("testbox");
		//testbox->setPosition(Vec2(mainSprite->getPosition().x,mainSprite->getPosition().y - testbox->getContentSize().height * 1.5f));

		//auto physicsbody = PhysicsBody::createBox(Size(testbox->getContentSize().width, testbox->getContentSize().height), PhysicsMaterial(0.1f, 1.0f, 0.0f));
		//physicsbody->setDynamic(false);
		//testbox->addComponent(physicsbody);

		//this->addChild(testbox, 1);

		//for (int i = 0; i < visibleSize.width / testbox->getContentSize().width; ++i)
		//{
		//	auto platformbox = Sprite::create("ZigzagForest_Square.png");
		//	platformbox->setName("platformbox_no" + i );
		//	platformbox->setPosition(Vec2(i * testbox->getContentSize().width, testbox->getPosition().y));
		//	auto m_physicsbody = PhysicsBody::createBox(Size(platformbox->getContentSize().width, platformbox->getContentSize().height), PhysicsMaterial(0.1f, 1.0f, 0.0f));
		//	m_physicsbody->setDynamic(false);
		//	platformbox->addComponent(m_physicsbody);

		//	this->addChild(platformbox, 1);
		//}
	}
	

	//Movement
	//auto moveEvent = MoveBy::create(5, Vec2(200, 0));
	////mainSprite->runAction(moveEvent);
	//auto delay = DelayTime::create(5.0f);
	//auto delaySequence = Sequence::create(delay, delay->clone(), nullptr);
	//auto sequence = Sequence::create(moveEvent, moveEvent->reverse(), delaySequence, nullptr);
	//mainSprite->runAction(sequence);


#ifndef KEYBOARD_EVENT_INIT
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(HelloWorld::onKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(HelloWorld::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
#endif

#ifndef MOUSE_EVENT_INIT
	auto m_listener = EventListenerMouse::create();
	m_listener->onMouseMove = CC_CALLBACK_1(HelloWorld::onMouseMove, this);
	m_listener->onMouseUp = CC_CALLBACK_1(HelloWorld::onMouseUp, this);
	m_listener->onMouseDown = CC_CALLBACK_1(HelloWorld::onMouseDown, this);
	m_listener->onMouseScroll = CC_CALLBACK_1(HelloWorld::onMouseScroll, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(m_listener, this);
#endif
	
#ifndef TOUCH_EVENT_INIT
	auto t_listener = EventListenerTouchOneByOne::create();
	t_listener->onTouchBegan = [](Touch* touch, Event* event) {
		//type your code for the callback function here
		return true;
	};
	t_listener->onTouchMoved = [](Touch* touch, Event* event) {
		//type your code for the callback function here
		return true;
	};
	//t_listener->onTouchEnabled = [](Touch* touch, Event* event) {
	//	//type your code for the callback function here
	//	return true;
	//};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(t_listener, this);
#endif
	
#ifndef ANIMATION_INIT
	//Loading one by one
	Animate* animIdle;
	{
		//Loading each frames
		Vector<SpriteFrame*> animFrames;
		animFrames.reserve(4);
		animFrames.pushBack(SpriteFrame::create("Blue_Front2.png", Rect(0, 0, 65, 81)));
		animFrames.pushBack(SpriteFrame::create("Blue_Front1.png", Rect(0, 0, 65, 81)));
		animFrames.pushBack(SpriteFrame::create("Blue_Front3.png", Rect(0, 0, 65, 81)));
		animFrames.pushBack(SpriteFrame::create("Blue_Front1.png", Rect(0, 0, 65, 81)));
		//Creating animations of frames
		Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.5f);
		animIdle = Animate::create(animation);
	}
	

	//Optimized ver [Loading sprites from sprite sheet]
	Vector<SpriteFrame*> animFrames(3);
	{
		SpriteBatchNode* spritebatch = SpriteBatchNode::create("sprite.png");
		SpriteFrameCache* cache = SpriteFrameCache::getInstance();
		cache->addSpriteFramesWithFile("sprite.plist");
		auto Sprite1 = Sprite::createWithSpriteFrameName("Blue_Back1.png");
		spritebatch->addChild(Sprite1);
		this->addChild(spritebatch);
		char str[100] = { 0 };
		for (int i = 1; i < 3; i++)
		{
			sprintf(str, "Blue_Back%d.png", i);
			SpriteFrame* frame = cache->getSpriteFrameByName(str);
			animFrames.pushBack(frame);
		}
	}
	

	//Loading the spritesheet animation
	Animate* animate;
	{
		// "caches" are always singletons in cocos2d
		auto cache = AnimationCache::getInstance();
		cache->addAnimationsWithFile("sprite_ani.plist");

		// should be getAnimationByName(..) in future versions
		auto animation = cache->animationByName("walk_right");

		// Don't confused between Animation and Animate
		animate = Animate::create(animation);
	}
	

#endif

#ifdef SHADER_INIT
	{
		Vec2 mLoc;
		mLoc.set(0.5f, 0.5f);
		Vec2 mLocInc;
		mLocInc.set(0.005f, 0.01f);

		auto shaderCharEffect = new GLProgram();
		shaderCharEffect->initWithFilenames("Basic.vsh", "CharEffect.fsh");
		shaderCharEffect->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
		shaderCharEffect->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_COLOR, GLProgram::VERTEX_ATTRIB_COLOR);
		shaderCharEffect->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORDS);
		
		shaderCharEffect->link();
		shaderCharEffect->updateUniforms();

		GLProgramState* state = GLProgramState::getOrCreateWithGLProgram(shaderCharEffect);
		mainSprite->setGLProgram(shaderCharEffect);
		mainSprite->setGLProgramState(state);
		state->setUniformVec2("loc", mLoc);

		/*proPostProcess = GLProgram::createWithFilenames("Basic.vsh", "GreyScale.fsh");
		proPostProcess->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_COLOR, GLProgram::VERTEX_ATTRIB_POSITION);
		proPostProcess->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_COLOR);
		proPostProcess->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORD);
		proPostProcess->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD1, GLProgram::VERTEX_ATTRIB_TEX_COORD1);
		proPostProcess->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD2, GLProgram::VERTEX_ATTRIB_TEX_COORD2);
		proPostProcess->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD3, GLProgram::VERTEX_ATTRIB_TEX_COORD3);
		proPostProcess->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_NORMAL, GLProgram::VERTEX_ATTRIB_NORMAL);
		proPostProcess->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_BLEND_WEIGHT, GLProgram::VERTEX_ATTRIB_BLEND_WEIGHT);
		proPostProcess->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_BLEND_INDEX, GLProgram::VERTEX_ATTRIB_BLEND_INDEX);

		proPostProcess->link();
		proPostProcess->updateUniforms();*/
	}
#endif 

#ifndef RENDER_TEXTURE_INIT
	/*rendtex = RenderTexture::create(visibleSize.width, visibleSize.height);
	rendtex->retain();

	rendtexSprite = Sprite::createWithTexture(rendtex->getSprite()->getTexture());
	rendtexSprite->setTextureRect(Rect(0, 0, rendtexSprite->getTexture()->getContentSize().width, rendtexSprite->getTexture()->getContentSize().height));
	rendtexSprite->setAnchorPoint(Point::ZERO);
	rendtexSprite->setPosition(Point::ZERO);
	rendtexSprite->setFlippedY(true);
	rendtexSprite->setGLProgram(proPostProcess);
	this->addChild(rendtexSprite, 2);*/
#endif 

#ifndef SOUND_INIT
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("Sound/bgm.wav", false);
	CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.1f);
#endif

#ifndef PLAYER_INIT
	player1 = Player::create("Player1");
	player1->Init("Plane_Idle.png");
	this->addChild(player1->get_Node(),1);
	player1->set_Position(playingSize.width * 0.5f, playingSize.height * 0.5f);
#endif 

	//mainSprite->runAction(RepeatForever::create(animIdle));
	mainSprite->runAction(animate);
	//this->removeChild(spriteNode);
#ifdef COMMENTS
	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object
	/*auto closeItem = MenuItemImage::create(
	"CloseNormal.png",
	"CloseSelected.png",
	CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

	if (closeItem == nullptr ||
	closeItem->getContentSize().width <= 0 ||
	closeItem->getContentSize().height <= 0)
	{
	problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
	}
	else
	{
	float x = origin.x + visibleSize.width - closeItem->getContentSize().width/2;
	float y = origin.y + closeItem->getContentSize().height/2;
	closeItem->setPosition(Vec2(x,y));
	}
	*/
	// create menu, it's an autorelease object
	/* auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);*/

	/////////////////////////////
	// 3. add your codes below...

	// add a label shows "Hello World"
	// create and initialize a label

	//auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
	//if (label == nullptr)
	//{
	//    problemLoading("'fonts/Marker Felt.ttf'");
	//}
	//else
	//{
	//    // position the label on the center of the screen
	//    label->setPosition(Vec2(origin.x + visibleSize.width/2,
	//                            origin.y + visibleSize.height - label->getContentSize().height));

	//    // add the label as a child to this layer
	//    this->addChild(label, 1);
	//}

	//// add "HelloWorld" splash screen"
	//auto sprite = Sprite::create("HelloWorld.png");
	//if (sprite == nullptr)
	//{
	//    problemLoading("'HelloWorld.png'");
	//}
	//else
	//{
	//    // position the sprite on the center of the screen
	//    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

	//    // add the sprite as a child to this layer
	//    this->addChild(sprite, 0);
	//}
#endif 

	auto cam = this->getDefaultCamera();//Camera::getDefaultCamera();
	//cam->setPosition(mainSprite->getPosition());

	//activate update feature per frame
	this->scheduleUpdate();



    return true;
}

void HelloWorld::update(float delta) 
{
	/*rendtex->beginWithClear(0.f, 0.f, 0.f, 0.f);
	this->visit();
	rendtex->end();
	rendtexSprite->setTexture(rendtex->getSprite()->getTexture());
	rendtexSprite->setGLProgram(proPostProcess);*/
	player1->Update(delta);
	if (isKeyPressed(EventKeyboard::KeyCode::KEY_RIGHT_ARROW))
		player1->Move(Player::Movement_Direction::Right);
	if (isKeyPressed(EventKeyboard::KeyCode::KEY_LEFT_ARROW))
		player1->Move(Player::Movement_Direction::Left);

	if (isKeyPressed(EventKeyboard::KeyCode::KEY_UP_ARROW))
		player1->Move(Player::Movement_Direction::Up);
	if (isKeyPressed(EventKeyboard::KeyCode::KEY_DOWN_ARROW))
		player1->Move(Player::Movement_Direction::Down);


	auto bgScrolling1 = MoveBy::create(0.f, Vec2(0.f, -50.f*delta));
	auto bgScrolling2 = MoveBy::create(0.f, Vec2(0.f, -50.f*delta));
	//auto bgResetHigher = MoveBy::create(0.f, Vec2(0.f, playingSize.height *2.5));
	auto tempbg = this->getChildByName("bg Node Main")->getChildByName("FirstBackground");
	tempbg->runAction(bgScrolling1);
	this->getChildByName("bg Node Main")->getChildByName("SecdBackground")->runAction(bgScrolling2);

	if (this->getChildByName("bg Node Main")->getChildByName("FirstBackground")->getPositionY() <= -bgSize.y)
	{
		this->getChildByName("bg Node Main")->getChildByName("FirstBackground")->setPosition(0, bgSize.y);
	}
	if (this->getChildByName("bg Node Main")->getChildByName("SecdBackground")->getPositionY() <= -bgSize.y)
	{
		this->getChildByName("bg Node Main")->getChildByName("SecdBackground")->setPosition(0, bgSize.y);
	}

}

void HelloWorld::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (Key_map.find(keyCode) == Key_map.end()) {
		Key_map[keyCode] = std::chrono::high_resolution_clock::now();
	}

	/*if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
	{
		player1->Move(Player::Movement_Direction::Right);
	}
	if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
	{
		player1->Move(Player::Movement_Direction::Left);
	}
	if (keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW)
	{
		player1->Move(Player::Movement_Direction::Up);
	}
	if (keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW)
	{
		player1->Move(Player::Movement_Direction::Down);
	}*/
	if (keyCode == EventKeyboard::KeyCode::KEY_SPACE)
	{
		//CCDirector::getInstance()->replaceScene(TransitionFade::create(0.5f, HelloWorld::createScene(),Color3B(0,255,255)));
		player1->Shoot();
	}

	if (keyCode == EventKeyboard::KeyCode::KEY_1)
	{
		SceneManager::getInstance().runSceneWithType(SceneType::SCENE2);
	}

}

void HelloWorld::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	Key_map.erase(keyCode);
	if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
	{
		player1->Set_moving_state(Player::Moving_State::Idle);
	}
	if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
	{
		player1->Set_moving_state(Player::Moving_State::Idle);
	}
}

bool HelloWorld::isKeyPressed(EventKeyboard::KeyCode code) 
{
	// Check if the key is currently pressed by seeing it it's in the std::map Key_map
	if (Key_map.find(code) != Key_map.end())
		return true;
	return false;
}

double HelloWorld::keyPressedDuration(EventKeyboard::KeyCode code, bool seconds)
{
	
	if (!isKeyPressed(code))
		return 0;  // Not pressed, so no duration 

	// Return the amount of time that has elapsed between now and when the user
   // first started holding down the key in milliseconds
   // Obviously the start time is the value we hold in our std::map Key_map
	if (seconds)
		return (std::chrono::duration_cast<std::chrono::milliseconds>
		(std::chrono::high_resolution_clock::now() - Key_map[code]).count()) * 0.001f;
	return std::chrono::duration_cast<std::chrono::milliseconds>
		(std::chrono::high_resolution_clock::now() - Key_map[code]).count();
}



void HelloWorld::onMouseMove(Event* event)
{
	EventMouse* e = (EventMouse*)event;
	e->getCursorX();
}
void HelloWorld::onMouseDown(Event* event)
{
	EventMouse* e = (EventMouse*)event;
}
void HelloWorld::onMouseUp(Event* event)
{
	EventMouse* e = (EventMouse*)event;
}
void HelloWorld::onMouseScroll(Event* event)
{
	EventMouse* e = (EventMouse*)event;
}

bool HelloWorld::checkBoxCollision(Sprite* box1, Sprite* box2)
{
	Rect box1Rect = box1->boundingBox();
	Rect box2Rect = box2->boundingBox();

	if (box1Rect.intersectsRect(box2Rect))
	{
		return true;
	}
	else
	{
		return false;
	}
}
void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}


