#ifndef DUNGEON_MEDIA_LOADER_H
#define DUNGEON_MEDIA_LOADER_H

#include "globalvariables.h"
#include "LTexture.h"

bool loadDungeon_Door_Key_Media(SDL_Renderer* gRenderer);
void freeDungeon_Door_Key_Media();

//Dungeon Media
//friend functions from DungeonNode class
bool setupLoad_DungeonMedia(SDL_Renderer* gRenderer);
bool loadDungeonMedia(SDL_Renderer* gRenderer,LTexture* tileMap,ALuint* source,ALuint* buffer);
void freeDungeonMedia(LTexture* tileMap,ALuint* source,ALuint* buffer);

extern ALuint dungeonMusicSource;
extern ALuint dungeonMusicBuffer;
extern LTexture dungeonTilesTexture;

//media for key
bool setupLoad_KeyMedia(SDL_Renderer* gRenderer);
bool loadKeyMedia(SDL_Renderer* gRenderer,LTexture* keyTexture,
    ALuint* source,ALuint* buffer);
void freeKeyMedia(LTexture* keyTexture,ALuint* source,ALuint* buffer);

extern LTexture keyTexture;
extern ALuint keySource;
extern ALuint keyBuffer;


 
 //media for door
bool setupLoad_DoorMedia(SDL_Renderer* gRenderer);
bool loadDoorMedia(SDL_Renderer* gRenderer,
                            LTexture* doorTexture,
                            ALuint* source,
                            ALuint* doorBufferOpen, 
                            ALuint* doorBufferFail,
                            std::vector <SDL_Rect> &doorClips);
void freeDoorMedia(
                            LTexture* doorTexture,
                            ALuint* doorSource,
                            ALuint* doorBufferOpen, 
                            ALuint* doorBufferFail);
                            
extern LTexture doorTexture;
extern ALuint doorSource;
extern ALuint doorBufferOpen;
extern ALuint doorBufferFail;
extern std::vector <SDL_Rect> doorClips;



#endif
