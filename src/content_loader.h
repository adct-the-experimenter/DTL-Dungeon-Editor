#include <string>
#include <vector>
#include <unordered_map>
#include <cstdint>

#include "globalvariables.h"
#include "LTexture.h"

struct EnemyContent
{
	std::string name; //name of enemy type
	std::string xml_def_filepath; //path to xml definition file of enemy
	std::string script_filepath; //path to lua script for enemy logic
	std::string mediaDir; //name of directory containing enemy content
	std::int16_t health; //health of enemy type
	float speed; //speed of enemy type
	LTexture script_enemy_texture; //texture of enemy type
    std::vector <SDL_Rect> script_enemy_walk_clips; //clips for walking for enemy
};

typedef std::unordered_map<std::string,EnemyContent> enemy_content_map;

extern enemy_content_map enemyContentMap;

void LoadContentFromXMLFiles();

//function to load media outside class
bool loadScriptedEnemyMedia(std::string xml_file_path,
									LTexture* cTexture,
                                    std::vector <SDL_Rect> &clips,
                                    SDL_Renderer* gRenderer );
                                    
//function to free media outside of class
void freeScriptedEnemyMedia(LTexture* cTexture);                                
    
//function to set enemy attributes for certain enemy type outside of class
bool setEnemyTypeAttributes(EnemyContent* thisEnemyContent, std::string xml_file_path);
