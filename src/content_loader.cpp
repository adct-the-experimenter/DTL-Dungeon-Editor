#include "load_script_files.h"

#include "pugixml.hpp"
#include <iostream>
#include <string>

void GetScriptFilesFromEnemyDirXMLFile(std::string xml_enemy_scripts_file_dir,
									   std::string xml_enemy_scripts_file_path,
									   std::vector <std::string> *enemyFiles)
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
	for (pugi::xml_node filePathNode = enemyDirRoot.first_child(); filePathNode; filePathNode = filePathNode.next_sibling())
	{	
		std::string valString = filePathNode.first_child().value();
		
		//assuming file paths in xml file is set relative to xml filepath itself
		std::string filepath = xml_enemy_scripts_file_dir + "/" + valString;
		std::cout << "file read:" << filepath << std::endl;
		enemyFiles->push_back(valString);
		
		iterator++;		
	}
}
