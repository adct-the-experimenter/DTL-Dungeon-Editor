#include "enemy_media_loader.h"

#include "content_loader.h"

bool loadEnemyMedia(SDL_Renderer* gRenderer)
{
    
    if(!setupLoad_Cockroach(gRenderer)){return false;}
    
    if(!setupLoad_GreedyZombie(gRenderer)){return false;}
    
    for (auto& x: enemyContentMap) 
    {
		//std::cout << x.first << ": " << x.second << std::endl;
		if(!setupLoad_ScriptedEnemy(x.first,gRenderer) )
		{
			return false;
		}
	}
    //if(!setupLoad_ScriptedEnemy(gRenderer)){return false;}
    
    return true;
}


//Setup cockroach media
LTexture cockroach_texture;
std::vector <SDL_Rect> cockroach_walk_clips;
ALuint cockroach_scream_buffer;
bool setupLoad_Cockroach(SDL_Renderer* gRenderer)
{
    //load cockroach visual media
    if(!loadCockRoachVisualMedia(&cockroach_texture,
                        cockroach_walk_clips,
                        gRenderer )
    )
    {
        printf("Failed to load cockroach visual media! \n");
        return false;
    }
    
    //load cockroach audio media
    if(!loadCockRoachAudioMedia(&cockroach_scream_buffer))
    {
		printf("Failed to load cockroach audio media! \n");
        return false;
	}
    
    return true;
}

//Setup greedy zombie media
LTexture greed_zombie_texture;
std::vector <SDL_Rect> greed_zombie_walk_clips;
bool setupLoad_GreedyZombie(SDL_Renderer* gRenderer)
{
    //load greedy zombie media
    if(!loadGreedyZombieMedia(&greed_zombie_texture,
                        greed_zombie_walk_clips,
                        gRenderer )
    )
    {
        printf("Failed to load greedy zombie media! \n");
        return false;
    }
    
    return true;
}

//scripted enemy media
bool setupLoad_ScriptedEnemy(std::string enemy_type,SDL_Renderer* gRenderer)
{
    
	std::string xml_file_dir = enemyContentMap.at(enemy_type).mediaDir;
	std::string xml_file_path = enemyContentMap.at(enemy_type).xml_def_filepath;
	LTexture* script_enemy_texture = &enemyContentMap.at(enemy_type).script_enemy_texture;
	std::vector <SDL_Rect> *script_enemy_walk_clips = &enemyContentMap.at(enemy_type).script_enemy_walk_clips;
	
	//load scripted enemy media
    if(!loadScriptedEnemyVisualMedia(xml_file_path, xml_file_dir,
							   script_enemy_texture,
                               *script_enemy_walk_clips,
                               gRenderer )
    )
    {
        printf("Failed to load scripted enemy media! \n");
        std::cout << xml_file_path << " failed.\n";
        return false;
    }
    else
    {
		if(!setEnemyTypeAttributes(&enemyContentMap.at(enemy_type),enemyContentMap.at(enemy_type).xml_def_filepath) )
		{
			return false;
		}
	}
    
    return true;
}


void freeEnemyMedia()
{
	cockroach_texture.free();
    //freeCockRoachVisualMedia(&cockroach_texture);
    freeCockRoachAudioMedia(&cockroach_scream_buffer);
    //freeGreedyZombieMedia(&greed_zombie_texture);
    greed_zombie_texture.free();
    
    //freeScriptedEnemyVisualMedia(&script_enemy_texture);
    for (auto& x: enemyContentMap) 
    {
		//std::cout << x.first << ": " << x.second << std::endl;
		x.second.script_enemy_texture.free();
	}

}

