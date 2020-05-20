#include "dungeon_media_loader.h"


bool loadDungeon_Door_Key_Media(SDL_Renderer* gRenderer)
{
    if(!setupLoad_DungeonMedia(gRenderer))
    {
        return false;
    }
    
    if(!setupLoad_DoorMedia(gRenderer))
    {
        return false;
    }
    
    if(!setupLoad_KeyMedia(gRenderer))
    {
        return false;
    }
    
    return true;
}

void freeDungeon_Door_Key_Media()
{
    //free dungeon media
    freeDungeonMedia(&dungeonTilesTexture,&dungeonMusicSource,&dungeonMusicBuffer);
    freeDoorMedia(&doorTexture,&doorSource,&doorBufferOpen,&doorBufferFail);
    freeKeyMedia(&keyTexture,&keySource,&keyBuffer);
}

ALuint dungeonMusicSource;
ALuint dungeonMusicBuffer;
LTexture dungeonTilesTexture;
bool setupLoad_DungeonMedia(SDL_Renderer* gRenderer)
{
    
    //load dungeon media
    if(!loadDungeonMedia(gRenderer,&dungeonTilesTexture,&dungeonMusicSource,&dungeonMusicBuffer) )
    {
        printf("Failed to load dungeon media! \n");
        return false;
    }
    
    return true;
}

LTexture doorTexture;
ALuint doorSource;
ALuint doorBufferOpen;
ALuint doorBufferFail;
std::vector <SDL_Rect> doorClips;
bool setupLoad_DoorMedia(SDL_Renderer* gRenderer)
{
    
    //load door media
    if(!loadDoorMedia(gRenderer,&doorTexture,&doorSource,
                        &doorBufferOpen,&doorBufferFail,doorClips) )
    {
        printf("Failed to load door media! \n");
        return false;
    }
    
    return true;
}

LTexture keyTexture;
ALuint keySource;
ALuint keyBuffer;
bool setupLoad_KeyMedia(SDL_Renderer* gRenderer)
{
    
    
    //load key media
    if(!loadKeyMedia(gRenderer,&keyTexture,&keySource,&keyBuffer) )
    {
        printf("Failed to load key media! \n");
        return false;
    }
    
    return true;
}
