#include "DungeonMap.h"

DungeonMap::DungeonMap()
{
    
}

DungeonMap::~DungeonMap()
{
    
}

bool checkCollision(SDL_Rect& a, SDL_Rect& b);
    

void DungeonMap::setClipsForTiles()
{
    //Set tile clips
    for(size_t i = 0; i < dungeonTilesVector.size(); ++i)
    {
        dungeonTilesVector[i]->setTileClips();
    }
    
}

//function to free resources from tiles
void DungeonMap::freeTiles()
{
    for(size_t i = 0; i < dungeonTilesVector.size(); i++ )
    {
        delete dungeonTilesVector[i];
    }
}

void DungeonMap::setDungeonCameraForDot(Dot* mainDotPointer, 
                                        std::int16_t& screenWidth, std::int16_t& screenHeight,
                                        SDL_Rect* camera)
{
    std::int16_t LEVEL_WIDTH = screenWidth;
    std::int16_t LEVEL_HEIGHT = screenHeight;
    //set place for dot to move in
    mainDotPointer->setPlace(screenWidth,screenHeight);

    lCamera = camera;
}

void DungeonMap::moveMainDot(Dot* mainDotPointer,float &timeStep)
{
    //set camera over dot
    mainDotPointer->setCamera(*lCamera);

    //move dot independent of frames, but rather dependent on time. includes collision detection
    mainDotPointer->moveOnTiles_TileType(timeStep, dungeonTilesVector );

}


void DungeonMap::renderTiles(SDL_Renderer* gRenderer,LTexture* tileTextureMap)
{
    for(size_t i = 0; i < dungeonTilesVector.size(); ++i)
    {
        dungeonTilesVector[i]->render(tileTextureMap,*lCamera,gRenderer);
    }
}


void DungeonMap::renderDotInDungeonMap(SDL_Renderer* gRenderer, Dot* mainDotPointer)
{
    //render dot
    mainDotPointer->render(*lCamera,gRenderer);
}

void setupNewDoorObject(Door* thisDoor,
                            LTexture* doorTexture,
                            ALuint* source,
                            ALuint* doorBufferOpen, 
                            ALuint* doorBufferFail );


bool checkDotCollidesWithDoor(Door* thisDoor, Dot* mainDot);

void DungeonMap::doorToDot_Logic(Dot* mainDotPointer,float& timeStep)
{
     if( dungeonDoorsVector.size() == 1)
    {
        
        checkDotCollidesWithDoor(dungeonDoorsVector[0],mainDotPointer);
        if(dungeonDoorsVector[0]->getDoorCollidedState() == Door::DoorCollided::DOT_TO_DOOR1
            || dungeonDoorsVector[0]->getDoorCollidedState() == Door::DoorCollided::DOT_TO_DOOR2)
        {
            //move dot back
            mainDotPointer->moveBack(timeStep);
        }
    }
     else if( dungeonDoorsVector.size() > 1 )
    {
        for(size_t i=0; i < dungeonDoorsVector.size(); ++i)
        {
            //if either of doors are within camera
            if( checkCollision(*lCamera,dungeonDoorsVector[i]->getCollisionBoxDoor1())
                || checkCollision(*lCamera,dungeonDoorsVector[i]->getCollisionBoxDoor2()))
            {
                //if dot collides with door
                if( checkDotCollidesWithDoor(dungeonDoorsVector[i],mainDotPointer) )
                {
                    //check if door is open
                     dungeonDoorsVector[i]->openDoorLogic();
                        
                    //if door is open and oot collides with it
                    if(dungeonDoorsVector[i]->getDoorCollidedState() == Door::DoorCollided::DOT_TO_DOOR1
                        && dungeonDoorsVector[i]->getDoorState() == Door::State::DOOR_OPEN)
                    {
                        DungeonMap::transferDotThroughDoor(mainDotPointer,dungeonDoorsVector[i],true);
                        dungeonDoorsVector[i]->resetDoorsToClose();
                    }
                    else if(dungeonDoorsVector[i]->getDoorCollidedState() == Door::DoorCollided::DOT_TO_DOOR2
                            && dungeonDoorsVector[i]->getDoorState() == Door::State::DOOR_OPEN)
                    {
                        DungeonMap::transferDotThroughDoor(mainDotPointer,dungeonDoorsVector[i],false);
                        dungeonDoorsVector[i]->resetDoorsToClose();
                    }
                    //if door isn't open
                    else if(dungeonDoorsVector[i]->getDoorState() == Door::State::DOOR_CLOSED)
                    {
                        //if dot is colliding with door
                        if(checkCollision(dungeonDoorsVector[i]->getCollisionBoxDoor1(), 
                                            mainDotPointer->getCollisionBox())
                            )
                        {
                            mainDotPointer->moveBack(timeStep);
                        }
                        else if( checkCollision(dungeonDoorsVector[i]->getCollisionBoxDoor2(), 
                                            mainDotPointer->getCollisionBox()) )
                        {
                            mainDotPointer->moveBack(timeStep);
                        }
                    }
                }
            }
        }
    }
}

void DungeonMap::renderDoors(SDL_Renderer* gRenderer)
{
    for(size_t i = 0; i < dungeonDoorsVector.size(); ++i)
    {
        if( checkCollision(*lCamera,dungeonDoorsVector[i]->getCollisionBoxDoor1())
                || checkCollision(*lCamera,dungeonDoorsVector[i]->getCollisionBoxDoor2()))
        {
            dungeonDoorsVector[i]->render(*lCamera,gRenderer);
        }
    }
}

void DungeonMap::door_handle_events(Event& thisEvent)
{
    //for all doors
    for(size_t i = 0; i < dungeonDoorsVector.size(); ++i)
    {
        //if door 1 collision box is within camera
        //or door 2 collision box is withing camera
        if(checkCollision( dungeonDoorsVector[i]->getCollisionBoxDoor1(),*lCamera)  ||
            checkCollision( dungeonDoorsVector[i]->getCollisionBoxDoor2(),*lCamera) )
        {
            dungeonDoorsVector[i]->handle_event(thisEvent);
        }
        
    }
}


void DungeonMap::transferDotThroughDoor(Dot* mainDotPointer, Door* thisDoor, bool One_To_Two)
{
    //make dot exit to right of door
    
    if(One_To_Two)
    {
        //change dot's position to door 2's position
        float x = thisDoor->getCollisionBoxDoor2().x + 
                    thisDoor->getCollisionBoxDoor2().w + 
                    mainDotPointer->getCollisionBox().w;
                    
        float y = thisDoor->getCollisionBoxDoor2().y +
                  mainDotPointer->getCollisionBox().h;
        //set x and y position of dot
        mainDotPointer->setPosX(x);
        mainDotPointer->setPosY(y);
    }
    else
    {
        //change dot's position to door 1's position
        float x = thisDoor->getCollisionBoxDoor1().x +
                    thisDoor->getCollisionBoxDoor1().w +
                    + mainDotPointer->getCollisionBox().w;
                    
        float y = thisDoor->getCollisionBoxDoor1().y + 
                    mainDotPointer->getCollisionBox().h;
        //set x and y position of dot
        mainDotPointer->setPosX(x);
        mainDotPointer->setPosY(y);
    }
}


void DungeonMap::freeDoorsAndKeys()
{
    if(dungeonDoorsVector.size() > 0)
    {
        for(size_t i = 0; i < dungeonDoorsVector.size(); ++i)
        {
            delete dungeonDoorsVector[i];
        }
    }
    
    if(dungeonKeysVector.size() > 0)
    {
        for(size_t i = 0; i < dungeonKeysVector.size(); ++i)
        {
            delete dungeonKeysVector[i];
        }
    }
}

void DungeonMap::play_door_sounds()
{
    //for all doors
    for(size_t i = 0; i < dungeonDoorsVector.size(); ++i)
    {
        dungeonDoorsVector[i]->playSounds();
    }
}
