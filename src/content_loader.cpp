#include "content_loader.h"

#include "pugixml.hpp"
#include <iostream>
#include <string>
#include "globalvariables.h"

enemy_content_map enemyContentMap;

void SetEnemyContentFromEnemyDirXMLFile(std::string xml_enemy_scripts_file_dir,
									   std::string xml_enemy_scripts_file_path)
{
	// Create empty XML document within memory
    pugi::xml_document doc;
    
    // Load XML file into memory
    // Remark: to fully read declaration entries you have to specify
    // "pugi::parse_declaration"
    pugi::xml_parse_result result = doc.load_file(xml_enemy_scripts_file_path.c_str(),
												pugi::parse_default);
    if (!result)
    {
        std::cout << "Parse error: " << result.description()
            << ", character pos= " << result.offset;
        return;
    }
    
    pugi::xml_node enemyDirRoot = doc.child("EnemyDirRoot");
    
    size_t iterator = 0;
	
	//go through each tile type in tiles node
	for (pugi::xml_node enemyNode = enemyDirRoot.first_child(); enemyNode; enemyNode = enemyNode.next_sibling())
	{
		
		std::string valName = enemyNode.attribute("name").value();
		std::string valFilepath= enemyNode.attribute("filepath").value();
		
		//assuming file paths in xml file is set relative to xml filepath itself
		std::string filepath = xml_enemy_scripts_file_dir + "/" + valFilepath;
		std::cout << "file read:" << filepath << std::endl;
		
		EnemyContent ec; ec.name = valName; ec.script_filepath = filepath;
		std::pair<std::string,EnemyContent> thisEnemyContentPair (valName,ec);
		enemyContentMap.insert (thisEnemyContentPair);
		
		iterator++;		
	}
}

void LoadAllScriptFilesFromXMLFiles()
{	
	std::string xml_enemy_scripts_file_dir = DATADIR_STR + "/EnemyPacks";
	std::string xml_enemy_scripts_file_path = xml_enemy_scripts_file_dir + "/enemy_directory.xml";
	SetEnemyContentFromEnemyDirXMLFile(xml_enemy_scripts_file_dir,xml_enemy_scripts_file_path);
	
}


