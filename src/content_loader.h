#include <string>
#include <vector>
#include <unordered_map>

#include "globalvariables.h"
#include "LTexture.h"

struct EnemyContent
{
	std::string name;
	std::string xml_def_filepath;
	std::string script_filepath;
	std::string mediaDir;
	LTexture script_enemy_texture;
    std::vector <SDL_Rect> script_enemy_walk_clips;
};

typedef std::unordered_map<std::string,EnemyContent> enemy_content_map;

extern enemy_content_map enemyContentMap;

void LoadContentFromXMLFiles();

