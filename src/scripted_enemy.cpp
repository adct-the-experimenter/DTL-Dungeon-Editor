#include "scripted_enemy.h"

#include "pugixml.hpp"
#include <iostream>
#include <string>



#include <cstdio>
#include <functional>

#include "lua_cpp_script_base.h"
#include "content_loader.h"

//constructor
ScriptedEnemy::ScriptedEnemy(std::string name, 
							std::int16_t health, float speed,
							int x, int y, int width, int height) : Enemy(x,y,width,height)
{
	
	m_name = name;
	
    Enemy::setHealth(health);
    
    Enemy::setEnemyState(Enemy::EnemyState::MOVING_NO_PLAYER);
    ScriptedEnemy::pushState(ScriptedEnemy::ScriptedEnemyState::DETERMINE_DIRECTION);
    
    //initialize speed
    Enemy::setSpeed(speed);
    
    probabilitiesDirection = {0.2, 0.2,0.2,0.2,0.3};
    
    //setup collision object for cockroach
    ScriptedEnemy::setupScriptedEnemyCollisionObject();
    
    //set view of cockroach
    Enemy::setEnemyView(Enemy::EnemyViewOption::LINE_OF_SIGHT);
    
    std::int16_t lineWidth = width; std::int16_t lineHeight = height * 2;
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
    CollisionBoxOwnerType type = CollisionBoxOwnerType::SCRIPTED_ENEMY;
    Enemy::setOwnerTypeOfCollisionObject(type);
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


void ScriptedEnemy::logic(float& timeStep, std::vector<DungeonTile*> &dungeonTiles)
{
    
    Enemy::checkViewForPlayer();
    ScriptedEnemy::reactToCollision();
    
    //int randNumber = (int)Enemy::getRandNumber();
	int enemyState = (int)Enemy::getEnemyState();
	int loopCount = Enemy::getLoopCount();
	int enemyFaceDirection = (int)Enemy::getFaceDirection();
	
	RunEnemyLogicFromScript(this,enemyContentMap.at(m_name).script_filepath,
							timeStep,enemyState,loopCount,enemyFaceDirection);
    
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

void ScriptedEnemy::moveUp(float& timeStep){Enemy::moveUp(timeStep); ScriptedEnemy::faceNorth();}
void ScriptedEnemy::moveLeft(float& timeStep){Enemy::moveLeft(timeStep); ScriptedEnemy::faceWest();}
void ScriptedEnemy::moveRight(float& timeStep){Enemy::moveRight(timeStep); ScriptedEnemy::faceEast();}
void ScriptedEnemy::moveDown(float& timeStep){Enemy::moveDown(timeStep); ScriptedEnemy::faceSouth();}
void ScriptedEnemy::pause(float& timeStep){Enemy:pause(timeStep);}


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
   ScriptedEnemy::renderEnemyCollisionBox(camera,gRenderer);
   Enemy::renderEnemyView(camera,gRenderer);
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
