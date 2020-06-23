#include "scripted_enemy.h"

#include "pugixml.hpp"
#include <iostream>
#include <string>

//lua c ibrary files
extern "C" {
    #include "lua.h"
    #include "lauxlib.h"
    #include "lualib.h"
}

#include <cstdio>


//constructor
ScriptedEnemy::ScriptedEnemy(int x,int y,int width,int height) : Enemy(x,y,width,height)
{
    //std::int16_t initialHealth = 50;
    Enemy::setHealth(cockroachHealth);
    Enemy::setEnemyState(Enemy::EnemyState::MOVING_NO_PLAYER);
    ScriptedEnemy::pushState(ScriptedEnemy::ScriptedEnemyState::DETERMINE_DIRECTION);
    
    //initialize speed
    float speed = 10;
    Enemy::setSpeed(speed);
    
    probabilitiesDirection = {0.2, 0.2,0.2,0.2,0.3};
    
    //setup collision object for cockroach
    ScriptedEnemy::setupScriptedEnemyCollisionObject();
    
    //set view of cockroach
    Enemy::setEnemyView(Enemy::EnemyViewOption::LINE_OF_SIGHT);
    
    std::int16_t lineWidth = width; std::int16_t lineHeight = height * 2.5;
    Enemy::setLineOfSightDimensions(lineWidth,lineHeight);
    Enemy::setLineOfSightToEnemyBox();
    
    Enemy::resetPushBackVariables();
    
    //std::cout << "\n ScriptedEnemy constructor called! \n";
}

ScriptedEnemy::~ScriptedEnemy()
{
    //std::cout << "\n ScriptedEnemy destructor called! \n";
    probabilitiesDirection = {0.3, 0.4,0.2,0.4};
}

void ScriptedEnemy::setupScriptedEnemyCollisionObject()
{
    CollisionBoxOwnerType type = CollisionBoxOwnerType::GREEDY_ZOMBIE;
    Enemy::setOwnerTypeOfCollisionObject(type);
}

bool loadScriptedEnemyVisualMedia(std::string xml_file_path,std::string xml_file_dir,
						LTexture* cTexture,
                        std::vector <SDL_Rect> &walk_clips,
                        SDL_Renderer* gRenderer )
{
    
    // Create empty XML document within memory
	pugi::xml_document doc;

	// Load XML file into memory
	// Remark: to fully read declaration entries you have to specify
	// "pugi::parse_declaration"
	pugi::xml_parse_result result = doc.load_file(xml_file_path.c_str(),
											pugi::parse_default);
	if (!result)
	{
		std::cout << "Parse error: " << result.description() << ", character pos= " << result.offset;
		return false;
	}
    
    pugi::xml_node root = doc.child("EnemyRoot");
    
    std::string cTexFilePath = xml_file_dir + root.child("Texture").attribute("path").value();
    
    //initialize texture
    if(!cTexture->loadFromFile(cTexFilePath.c_str(),gRenderer) )
    {
        std::cout << "scripted enemy image loading failed! \n";
        std::cout << "filepath:" << cTexFilePath << std::endl;
        return false;
    }
    else
    {
		
		std::string valString;
		
		//set size of walk clips vector
		valString = root.child("WalkClips").child("clip_num").attribute("number").value();
		size_t clipsNum = atoi(valString.c_str());;
        walk_clips.resize(clipsNum);
		
		//set width and height of each uniform clips
		valString = root.child("WalkClips").child("clip_width").attribute("width").value();
        std::int8_t width = atoi(valString.c_str());
        valString = root.child("WalkClips").child("clip_height").attribute("height").value();
        std::int8_t height = atoi(valString.c_str());
        
        SDL_Rect clip;
        clip.w = width;
        clip.h = height;
        
        valString = root.child("WalkClips").child("UP_1").attribute("x").value();
        clip.x = atoi(valString.c_str());;
        valString = root.child("WalkClips").child("UP_1").attribute("y").value();
        clip.y = atoi(valString.c_str());;
        walk_clips[Sprite::UP_1] = clip;
        
        valString = root.child("WalkClips").child("UP_2").attribute("x").value();
        clip.x = atoi(valString.c_str());;
        valString = root.child("WalkClips").child("UP_2").attribute("y").value();
        clip.y = atoi(valString.c_str());;
        walk_clips[Sprite::UP_2] = clip; 
        
        valString = root.child("WalkClips").child("UP_3").attribute("x").value();
        clip.x = atoi(valString.c_str());;
        valString = root.child("WalkClips").child("UP_3").attribute("y").value();
        clip.y = atoi(valString.c_str());;
        walk_clips[Sprite::UP_3] = clip; 
        
        valString = root.child("WalkClips").child("UP_4").attribute("x").value();
        clip.x = atoi(valString.c_str());;
        valString = root.child("WalkClips").child("UP_4").attribute("y").value();
        clip.y = atoi(valString.c_str());;
        walk_clips[Sprite::UP_4] = clip;
        
        valString = root.child("WalkClips").child("UP_LEFT_1").attribute("x").value();
        clip.x = atoi(valString.c_str());;
        valString = root.child("WalkClips").child("UP_LEFT_1").attribute("y").value();
        clip.y = atoi(valString.c_str());;
        walk_clips[Sprite::UP_LEFT_1] = clip;
        
        valString = root.child("WalkClips").child("UP_LEFT_2").attribute("x").value();
        clip.x = atoi(valString.c_str());;
        valString = root.child("WalkClips").child("UP_LEFT_2").attribute("y").value();
        clip.y = atoi(valString.c_str());;
        walk_clips[Sprite::UP_LEFT_2] = clip;
        
        valString = root.child("WalkClips").child("UP_LEFT_3").attribute("x").value();
        clip.x = atoi(valString.c_str());;
        valString = root.child("WalkClips").child("UP_LEFT_3").attribute("y").value();
        clip.y = atoi(valString.c_str());;
        walk_clips[Sprite::UP_LEFT_3] = clip;
        
        valString = root.child("WalkClips").child("UP_LEFT_4").attribute("x").value();
        clip.x = atoi(valString.c_str());;
        valString = root.child("WalkClips").child("UP_LEFT_4").attribute("y").value();
        clip.y = atoi(valString.c_str());;
        walk_clips[Sprite::UP_LEFT_4] = clip;
        
        valString = root.child("WalkClips").child("LEFT_1").attribute("x").value();
        clip.x = atoi(valString.c_str());;
        valString = root.child("WalkClips").child("LEFT_1").attribute("y").value();
        clip.y = atoi(valString.c_str());;
        walk_clips[Sprite::LEFT_1] = clip;
        
        valString = root.child("WalkClips").child("LEFT_2").attribute("x").value();
        clip.x = atoi(valString.c_str());;
        valString = root.child("WalkClips").child("LEFT_2").attribute("y").value();
        clip.y = atoi(valString.c_str());;
        walk_clips[Sprite::LEFT_2] = clip;
        
        valString = root.child("WalkClips").child("LEFT_3").attribute("x").value();
        clip.x = atoi(valString.c_str());;
        valString = root.child("WalkClips").child("LEFT_3").attribute("y").value();
        clip.y = atoi(valString.c_str());;
        walk_clips[Sprite::LEFT_3] = clip;
        
        valString = root.child("WalkClips").child("LEFT_4").attribute("x").value();
        clip.x = atoi(valString.c_str());;
        valString = root.child("WalkClips").child("LEFT_4").attribute("y").value();
        clip.y = atoi(valString.c_str());;
        walk_clips[Sprite::LEFT_4] = clip;
        
        valString = root.child("WalkClips").child("DOWN_LEFT_1").attribute("x").value();
        clip.x = atoi(valString.c_str());;
        valString = root.child("WalkClips").child("DOWN_LEFT_1").attribute("y").value();
        clip.y = atoi(valString.c_str());;
        walk_clips[Sprite::DOWN_LEFT_1] = clip;
        
        valString = root.child("WalkClips").child("DOWN_LEFT_2").attribute("x").value();
        clip.x = atoi(valString.c_str());;
        valString = root.child("WalkClips").child("DOWN_LEFT_2").attribute("y").value();
        clip.y = atoi(valString.c_str());;
        walk_clips[Sprite::DOWN_LEFT_2] = clip;
        
        valString = root.child("WalkClips").child("DOWN_LEFT_3").attribute("x").value();
        clip.x = atoi(valString.c_str());;
        valString = root.child("WalkClips").child("DOWN_LEFT_3").attribute("y").value();
        clip.y = atoi(valString.c_str());;
        walk_clips[Sprite::DOWN_LEFT_3] = clip;
        
        valString = root.child("WalkClips").child("DOWN_LEFT_4").attribute("x").value();
        clip.x = atoi(valString.c_str());;
        valString = root.child("WalkClips").child("DOWN_LEFT_4").attribute("y").value();
        clip.y = atoi(valString.c_str());;
        walk_clips[Sprite::DOWN_LEFT_4] = clip;
        
        valString = root.child("WalkClips").child("DOWN_1").attribute("x").value();
        clip.x = atoi(valString.c_str());;
        valString = root.child("WalkClips").child("DOWN_1").attribute("y").value();
        clip.y = atoi(valString.c_str());;
        walk_clips[Sprite::DOWN_1] = clip;
        
        valString = root.child("WalkClips").child("DOWN_2").attribute("x").value();
        clip.x = atoi(valString.c_str());;
        valString = root.child("WalkClips").child("DOWN_2").attribute("y").value();
        clip.y = atoi(valString.c_str());;
        walk_clips[Sprite::DOWN_2] = clip;
        
        valString = root.child("WalkClips").child("UP_1").attribute("x").value();
        clip.x = atoi(valString.c_str());;
        valString = root.child("WalkClips").child("UP_1").attribute("y").value();
        clip.y = atoi(valString.c_str());;
        walk_clips[Sprite::DOWN_3] = clip;
        
        valString = root.child("WalkClips").child("DOWN_4").attribute("x").value();
        clip.x = atoi(valString.c_str());;
        valString = root.child("WalkClips").child("DOWN_4").attribute("y").value();
        clip.y = atoi(valString.c_str());;
        walk_clips[Sprite::DOWN_4] = clip;
        
        valString = root.child("WalkClips").child("RIGHT_1").attribute("x").value();
        clip.x = atoi(valString.c_str());;
        valString = root.child("WalkClips").child("RIGHT_1").attribute("y").value();
        clip.y = atoi(valString.c_str());;
        walk_clips[Sprite::RIGHT_1] = clip;
        
        valString = root.child("WalkClips").child("RIGHT_2").attribute("x").value();
        clip.x = atoi(valString.c_str());;
        valString = root.child("WalkClips").child("RIGHT_2").attribute("y").value();
        clip.y = atoi(valString.c_str());;
        walk_clips[Sprite::RIGHT_2] = clip;
        
        valString = root.child("WalkClips").child("RIGHT_3").attribute("x").value();
        clip.x = atoi(valString.c_str());;
        valString = root.child("WalkClips").child("RIGHT_3").attribute("y").value();
        clip.y = atoi(valString.c_str());;
        walk_clips[Sprite::RIGHT_3] = clip;
        
        valString = root.child("WalkClips").child("RIGHT_4").attribute("x").value();
        clip.x = atoi(valString.c_str());;
        valString = root.child("WalkClips").child("RIGHT_4").attribute("y").value();
        clip.y = atoi(valString.c_str());;
        walk_clips[Sprite::RIGHT_4] = clip;
        
        valString = root.child("WalkClips").child("DOWN_RIGHT_1").attribute("x").value();
        clip.x = atoi(valString.c_str());;
        valString = root.child("WalkClips").child("DOWN_RIGHT_1").attribute("y").value();
        clip.y = atoi(valString.c_str());;
        walk_clips[Sprite::DOWN_RIGHT_1] = clip;
        
        valString = root.child("WalkClips").child("DOWN_RIGHT_2").attribute("x").value();
        clip.x = atoi(valString.c_str());;
        valString = root.child("WalkClips").child("DOWN_RIGHT_2").attribute("y").value();
        clip.y = atoi(valString.c_str());;
        walk_clips[Sprite::DOWN_RIGHT_2] = clip;
        
        valString = root.child("WalkClips").child("DOWN_RIGHT_3").attribute("x").value();
        clip.x = atoi(valString.c_str());;
        valString = root.child("WalkClips").child("DOWN_RIGHT_3").attribute("y").value();
        clip.y = atoi(valString.c_str());;
        walk_clips[Sprite::DOWN_RIGHT_3] = clip;
        
        valString = root.child("WalkClips").child("DOWN_RIGHT_4").attribute("x").value();
        clip.x = atoi(valString.c_str());;
        valString = root.child("WalkClips").child("DOWN_RIGHT_4").attribute("y").value();
        clip.y = atoi(valString.c_str());;
        walk_clips[Sprite::DOWN_RIGHT_4] = clip;
        
        valString = root.child("WalkClips").child("UP_RIGHT_1").attribute("x").value();
        clip.x = atoi(valString.c_str());;
        valString = root.child("WalkClips").child("UP_RIGHT_1").attribute("y").value();
        clip.y = atoi(valString.c_str());;
        walk_clips[Sprite::UP_RIGHT_1] = clip;
        
        valString = root.child("WalkClips").child("UP_RIGHT_2").attribute("x").value();
        clip.x = atoi(valString.c_str());;
        valString = root.child("WalkClips").child("UP_RIGHT_2").attribute("y").value();
        clip.y = atoi(valString.c_str());;
        walk_clips[Sprite::UP_RIGHT_2] = clip;
        
        valString = root.child("WalkClips").child("UP_RIGHT_3").attribute("x").value();
        clip.x = atoi(valString.c_str());;
        valString = root.child("WalkClips").child("UP_RIGHT_3").attribute("y").value();
        clip.y = atoi(valString.c_str());;
        walk_clips[Sprite::UP_RIGHT_3] = clip;
        
        valString = root.child("WalkClips").child("UP_RIGHT_4").attribute("x").value();
        clip.x = atoi(valString.c_str());;
        valString = root.child("WalkClips").child("UP_RIGHT_4").attribute("y").value();
        clip.y = atoi(valString.c_str());;
        walk_clips[Sprite::UP_RIGHT_4] = clip;
    }
    
    return true;
}

void freeScriptedEnemyVisualMedia(LTexture* cTexture)
{
    if(cTexture != nullptr)
    {
        //delete cTexture;
        cTexture = nullptr;
    }
}


//function to load media for sprite
bool ScriptedEnemy::loadMedia(LTexture* thisTex, std::string path,SDL_Renderer* gRenderer)
{
    return Enemy::loadMedia(thisTex,path,gRenderer);
}



void ScriptedEnemy::setPointersToMedia(LTexture* cTexture,std::vector <SDL_Rect> &clips)
{
    Enemy::setPointerToTexture(cTexture);
    Enemy::setSpriteClips(&clips);
}


void ScriptedEnemy::handleEvent(Event& thisEvent){Enemy::handleEvent(thisEvent);}

void ScriptedEnemy::handleEvent_EnemyAI(RNGType& rngSeed)
{
    //setup rng with set probablities    
    boost::random::discrete_distribution <int> distDirection(probabilitiesDirection);
    boost::random::variate_generator <RNGType&, boost::random::discrete_distribution <> > DirectionDie(rngSeed,distDirection);
    
    std::int8_t thisRandNumber = DirectionDie();
    ScriptedEnemy::setRandNumber(thisRandNumber);
}


void ScriptedEnemy::RunLuaLogicForScriptedEnemy(std::string lua_file_path)
{

	//create a new lua state
	lua_State * L = luaL_newstate();

	//open all libraries
	luaL_openlibs(L);

	/* load the script */
	luaL_dofile(L, lua_file_path.c_str());

	/* the function name */
	lua_getglobal(L, "logic");

	/* the first argument, random number */
	lua_pushnumber(L, Enemy::getRandNumber());

	/* the second argument, enemy state */
	lua_pushnumber(L, (int)Enemy::getEnemyState());

	/* call the function with 2 arguments, return 0 result */
	lua_call(L, 2, 0);
	
	lua_close(L);
}

void ScriptedEnemy::logic(float& timeStep, std::vector<DungeonTile*> &dungeonTiles)
{
    
    //if cockroach is not colliding with wall
    if(Enemy::getEnemyState() != Enemy::EnemyState::COLLIDE_WITH_WALL)
    {
        //move enemy
        ScriptedEnemy::moveOnTiles_TileType(timeStep,dungeonTiles);
    }
    
    ScriptedEnemy::reactToCollision();
    Enemy::checkViewForPlayer();
    
    RunLuaLogicForScriptedEnemy("../data/EnemyPacks/goldroach/cockroach.lua");
    
    //increment loop count 
    Enemy::incrementLoopCount();
    //if 5th time interval has passed
    if(Enemy::getLoopCount() >= 10 )
    {
        //reset loop count
        Enemy::resetLoopCount();
        //Set state to determine new direction
        //ScriptedEnemy::pushState(ScriptedEnemy::ScriptedEnemyState::DETERMINE_DIRECTION);
    }
}




void ScriptedEnemy::runLogicState_MovingNoPlayer(float& timeStep)
{
    //if cockroach is in state of determining direction
    if(ScriptedEnemy::getCurrentState() == ScriptedEnemy::ScriptedEnemyState::DETERMINE_DIRECTION)
    {
        switch(ScriptedEnemy::getRandNumber())
        {
            case 0:{ScriptedEnemy::pushState(ScriptedEnemy::ScriptedEnemyState::MOVE_UP); break;}
            case 1:{ScriptedEnemy::pushState(ScriptedEnemy::ScriptedEnemyState::MOVE_LEFT); break;}
            case 2:{ScriptedEnemy::pushState(ScriptedEnemy::ScriptedEnemyState::MOVE_RIGHT); break;}
            case 3:{ScriptedEnemy::pushState(ScriptedEnemy::ScriptedEnemyState::MOVE_DOWN); break;}
            case 4:{ScriptedEnemy::pushState(ScriptedEnemy::ScriptedEnemyState::PAUSE); break;}
        }
    }
    
    //go through cockroach movements on stack
    else
    {
        //pop current state if stack is not empty and loop count is reset
        if(!state_stack.empty() && Enemy::getLoopCount() == 0){ScriptedEnemy::popState();}
    }
    
    //check if player can be seen
    Enemy::checkViewForPlayer();
    
    //make cockroach react to collision
    ScriptedEnemy::reactToCollision();
}

//variable to use in runLogicState_SeePlayer
//keeps track of which interval player was seen
static std::int8_t movingSeePlayerLoopCountStart;
//bool to check if tempInterval set
static bool movingSeePlayerLoopStartSet = false;

void ScriptedEnemy::runLogicState_MovingSeePlayer(float& timeStep)
{
    //std::cout << "Player seen! \n";
    
    //get time interval player seen
    if(!movingSeePlayerLoopStartSet)
    {
        movingSeePlayerLoopStartSet = true;
        movingSeePlayerLoopCountStart = Enemy::getLoopCount();
    }
    
    //move in direction player was seen
    switch(Enemy::getFaceDirection())
    {
        case Sprite::FaceDirection::NORTH:
        {
            ScriptedEnemy::pushState(ScriptedEnemy::ScriptedEnemyState::MOVE_UP); 
            break;
        }
        case Sprite::FaceDirection::EAST:
        {
            ScriptedEnemy::pushState(ScriptedEnemy::ScriptedEnemyState::MOVE_RIGHT); 
            break;
        }
        case Sprite::FaceDirection::SOUTH:
        {
            ScriptedEnemy::pushState(ScriptedEnemy::ScriptedEnemyState::MOVE_DOWN); 
            break;
        }
        case Sprite::FaceDirection::WEST:
        {
            ScriptedEnemy::pushState(ScriptedEnemy::ScriptedEnemyState::MOVE_LEFT); 
            break;
        }
        default:{break;}
    }
    
    //if time interval is reset
    if(Enemy::getLoopCount() == 0)
    {
        movingSeePlayerLoopStartSet = false;
        Enemy::setEnemyState(Enemy::EnemyState::MOVING_NO_PLAYER);
    }
    
    //make cockroach react to collision
    ScriptedEnemy::reactToCollision();
}


void ScriptedEnemy::runLogicState_PushedBack(float& timeStep)
{
    //if count of times enemy has been pushed back is less than number of times 
    //enemy has to be pushed back
    if( ScriptedEnemy::getCountPushBack() < ScriptedEnemy::getNumTimesEnemyPushBack() )
    {
        Enemy::pushBackEnemy(timeStep,onePushBack,ScriptedEnemy::getPushBackDirection()); //get pushed back
        Enemy::incrementCountPushBack(); //increment count
    }
    //else set enemy state back to normal and reset count
    else
    {
        Enemy::setEnemyState(Enemy::EnemyState::MOVING_NO_PLAYER);
        //reset pushback variables if colliding with wall
        Enemy::resetPushBackVariables();
    }
}

void ScriptedEnemy::runLogicState_CollideWithWall(float& timeStep)
{ 
    std::int16_t pushBackDist = 2;
    
    Enemy::pushBackEnemy(timeStep,pushBackDist,CollisionDirection::WALL);
    
    //reset pushback variables if colliding with wall
    Enemy::resetPushBackVariables();
    
    //reset back to enemy state moving no player
    Enemy::setEnemyState(Enemy::EnemyState::MOVING_NO_PLAYER);
}

void ScriptedEnemy::runLogicState_HitByWeapon(float& timeStep)
{
    
}

void ScriptedEnemy::runLogicState_HitPlayer(float& timeStep)
{
    
}

void ScriptedEnemy::reactToCollision()
{
    //check if cockroach was hit
   switch(Enemy::getCollisionObjectPtr()->typeOfCollision)
   {
       case CollisionType::HIT_BY_SWORD:
       {
            //Lower enemy health
           Enemy::decrementHealth(cockroach_HitBySwordDamage);
           //set number of times to push back enemy by 1 push back. 5 pixels
           std::int8_t numTimesPushBack = cockroach_PushBackBySword / onePushBack;
           Enemy::setNumTimesEnemyPushBack(numTimesPushBack);
           //set direction of push back for enemy
           Enemy::setPushBackDirection(ScriptedEnemy::getCollisionObjectPtr()->directionOfCollision); 
           //set state to enemy being pushed back
           Enemy::setEnemyState(Enemy::EnemyState::PUSHED_BACK);
           
		   //reset count for times enemy has been pushed back
		   Enemy::resetCountPushBack();
		   //reset collision type to none
		   Enemy::resetCollisionType();
           break;
        }
       case CollisionType::HIT_BY_BULLET:
       {
		    //Lower enemy health
           Enemy::decrementHealth(cockroach_HitByBulletDamage);
           //set number of times to push back enemy by 1 push back. 5 pixels
           std::int8_t numTimesPushBack = cockroach_PushBackByBullet / onePushBack;
           Enemy::setNumTimesEnemyPushBack(numTimesPushBack);
           //set direction of push back for enemy
           Enemy::setPushBackDirection(ScriptedEnemy::getCollisionObjectPtr()->directionOfCollision); 
           //set state to enemy being pushed back
           Enemy::setEnemyState(Enemy::EnemyState::PUSHED_BACK);
           
		   //reset count for times enemy has been pushed back
		   Enemy::resetCountPushBack();
		   //reset collision type to none
		   Enemy::resetCollisionType();
           
		   break;
	   }
       default:{ break;}
   }
   
   
}

void ScriptedEnemy::move(float& timeStep)
{
    switch(ScriptedEnemy::getCurrentState())
    {
        case ScriptedEnemy::ScriptedEnemyState::MOVE_UP:
        {
            Enemy::moveUp(timeStep); 
            break;
        }
        case ScriptedEnemy::ScriptedEnemyState::MOVE_LEFT:
        {
            Enemy::moveLeft(timeStep); 
            break;
        }
        case ScriptedEnemy::ScriptedEnemyState::MOVE_RIGHT:
        {
            Enemy::moveRight(timeStep); 
            break;
        }
        case ScriptedEnemy::ScriptedEnemyState::MOVE_DOWN:
        {
            Enemy::moveDown(timeStep); 
            break;
        }
        case ScriptedEnemy::ScriptedEnemyState::PAUSE:
        {
            Enemy::pause(timeStep); 
            break;
        }
    }
}


bool touchesDungeonWallVector( SDL_Rect& box, std::vector<DungeonTile*> &dungeonTiles );

bool ScriptedEnemy::moveOnTiles(float& timeStep, std::vector<DungeonTile*> &dungeonTiles)
{
    ScriptedEnemy::move(timeStep);
    
    //if dot touches a wall tile
    if(touchesDungeonWallVector( Enemy::getCollisionBox(), dungeonTiles ) )
    {
        //set enemy state to collide with wall
        Enemy::setEnemyState(Enemy::EnemyState::COLLIDE_WITH_WALL);

		return true;
    }
    else{Enemy::setEnemyState(Enemy::EnemyState::MOVING_NO_PLAYER);}
    
    Enemy::setMoveClip();
    ScriptedEnemy::setFrame();

	return false;
}

DungeonTile::TileType ScriptedEnemy::moveOnTiles_TileType(float& timeStep, std::vector<DungeonTile*> &dungeonTiles)
{
    ScriptedEnemy::move(timeStep);
    
    DungeonTile::TileType tileType = touchesDungeonTile(ScriptedEnemy::getCollisionBox(),
                                                        dungeonTiles);
    //if dot touches a wall tile
    if( tileType == DungeonTile::TileType::TOP_LEFT || tileType == DungeonTile::TileType::LEFT 
        || tileType == DungeonTile::TileType::BOTTOM_LEFT || tileType == DungeonTile::TileType::TOP || 
        tileType == DungeonTile::TileType::CENTER || tileType == DungeonTile::TileType::BOTTOM ||
        tileType == DungeonTile::TileType::TOP_RIGHT || tileType == DungeonTile::TileType::RIGHT || 
        tileType == DungeonTile::TileType::BOTTOM_RIGHT ||
        
        //door
        tileType == DungeonTile::TileType::DOOR ||
        // center hole
        tileType == DungeonTile::TileType::CENTER)
    {
        //set enemy state to collide with wall
        Enemy::setEnemyState(Enemy::EnemyState::COLLIDE_WITH_WALL);
    }
   
    Enemy::setMoveClip();
    ScriptedEnemy::setFrame();

    return tileType;
}

void ScriptedEnemy::moveBack(float& timeStep){Enemy::moveBack(timeStep);}


//Frame animation 

//function to determine which frame to use
void ScriptedEnemy::setFrame()
{
	int fCount = Enemy::getFrameCount();
    
    std::int8_t offsetForFrame = 0;
    
    //if frame count is more than 2, reset
    //divide frame count by 3 frames of animation to slow down animation
    // How integers work: 0/4 == 0 1/4 == 0 2/4 == 0 3/4 = 0 4/4 = 0
    //after 4th frame, reset frame count
    if(fCount/4 > 3){ScriptedEnemy::resetFrameCount();}
    
    if(Enemy::getSpriteState() == Sprite::State::STAND){offsetForFrame = 2;}
    else if(Enemy::getSpriteState() == Sprite::State::WALK)
    {
        //stand
        if(fCount/4 == 0){offsetForFrame = 0;}
        //step with left
        else if(fCount/4 == 1){offsetForFrame = 1;}
        //stand
        else if(fCount/4 == 2){offsetForFrame = 2;}
        //step with right
        else if(fCount/4 == 3){offsetForFrame = 3;}
    }
    
    Enemy::setFrameOffset(offsetForFrame);
}


void ScriptedEnemy::render(SDL_Rect& camera, SDL_Renderer* gRenderer, SDL_Rect* clip)
{
    //Enemy::render(camera,gRenderer,clip);
    
    if(Enemy::getPointerToTexture() != nullptr)
    {
        std::int16_t x = ScriptedEnemy::getCollisionBox().x - camera.x;
        std::int16_t y = ScriptedEnemy::getCollisionBox().y - camera.y;
        
        SDL_Rect* clip = ScriptedEnemy::getClipToShow();
        if(clip == nullptr){clip = &(*Enemy::getSpriteClips())[UP_1];}
        Enemy::getPointerToTexture()->render( x, y, gRenderer,clip);
    }
   
	//render collision box of enemy
   //ScriptedEnemy::renderEnemyCollisionBox(camera,gRenderer);
   //Enemy::renderEnemyView(camera,gRenderer);
}

void ScriptedEnemy::renderEnemyCollisionBox(SDL_Rect& camera, SDL_Renderer* gRenderer)
{
	 SDL_SetRenderDrawColor(gRenderer,
                           200,
                           0,
                           0,
                           50);
    
    SDL_Rect pBox = {  ScriptedEnemy::getCollisionBox().x - camera.x ,
                         ScriptedEnemy::getCollisionBox().y - camera.y ,
                        ScriptedEnemy::getCollisionBox().w,
                        ScriptedEnemy::getCollisionBox().h };
    SDL_RenderDrawRect(gRenderer,&pBox);
}


void ScriptedEnemy::pushState(ScriptedEnemy::ScriptedEnemyState state)
{
    state_stack.push(state);
}

void ScriptedEnemy::popState()
{
    state_stack.pop();
}

ScriptedEnemy::ScriptedEnemyState ScriptedEnemy::getCurrentState()
{
    return state_stack.top();
}




void ScriptedEnemy::sound(AudioRenderer* gAudioRenderer)
{
	extern ALuint scream_buffer;
		
	if(Enemy::getEnemyState() == Enemy::EnemyState::PUSHED_BACK)
	{
		std::cout << "cockroach scream called! \n";
		float x = Enemy::getPosX();
		float y = Enemy::getPosY();
		//if(scream_buffer != 0){gAudioRenderer->renderAudio(x,y,&scream_buffer);}
	}
}


