#include <string>
#include <vector>
#include <unordered_map>

struct EnemyContent
{
	std::string name;
	std::string script_filepath;
};

typedef std::unordered_map<std::string,EnemyContent> enemy_content_map;

extern enemy_content_map enemyContentMap;

void LoadAllScriptFilesFromXMLFiles();

