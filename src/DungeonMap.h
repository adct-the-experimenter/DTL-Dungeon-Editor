#ifndef DUNGEONMAP_H
#define DUNGEONMAP_H

#include "enemy.h"
#include "door.h"
#include "weapon.h"

#include <array>
#include <algorithm>    // std::random_shuffle
#include <ctime>

//class to contain graphical part of labyrinth

class DungeonMap
{
public:
    DungeonMap();
    ~DungeonMap();
    
    
    //function to set tile clips for tiles in DungeonMap
    void setClipsForTiles();
    
    //function to free tiles of DungeonMap
    void freeTiles();
    
    void setDungeonCameraForDot(Dot* mainDotPointer, 
                                std::int16_t& screenWidth, std::int16_t& screenHeight,
                                SDL_Rect* camera);
    //Door
    //function to create doors
    void createDoorsInDungeonMap(std::int8_t& numberDoors,
                                    LTexture* doorTexture,
                                    ALuint* source,
                                    ALuint* doorBufferOpen, 
                                    ALuint* doorBufferFail);
                                    
    
    //function to push dot back if collide with door
    void doorToDot_Logic(Dot* mainDotPointer,float& timeStep);
    
    //function to do door handle events 
    void door_handle_events(Event& thisEvent);
    
    //function to play sounds 
    void play_door_sounds();
    
    //function to transport dot through door
    //bool is true if going from one to two, false for two to one
    void transferDotThroughDoor(Dot* mainDotPointer, Door* thisDoor, bool One_To_Two);
    
    //function to free doors and keys of DungeonMap
    void freeDoorsAndKeys();
    
//Game loop functions

    //function to move main dot on tiles in DungeonMap
    void moveMainDot(Dot* mainDotPointer,float& timeStep);

    //function to render tiles
    void renderTiles(SDL_Renderer* gRenderer,LTexture* tileTextureMap);

    void renderDotInDungeonMap(SDL_Renderer* gRenderer,Dot* mainDotpointer);
    
    void renderDoors(SDL_Renderer* gRenderer);
    

    friend class Dungeon;
    
private:
    //vector of tiles in Dungeon map
    std::vector <DungeonTile*> dungeonTilesVector;
    
    //camera for dungeon map
    SDL_Rect* lCamera;

    //dungeon keys
    std::vector <Key*> dungeonKeysVector;
    //dungeon doors
    std::vector <Door*> dungeonDoorsVector;
    
    //pointer to vector of enemy pointers
    std::vector <Enemy*> *dungeonEnemiesVector;
    
    //pointer to array of weapon pointers
    std::array <Weapon*,1> *dungeonWeaponsArray;
};

#endif
