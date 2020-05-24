#include "DungeonXMLReader.h"

#include "pugixml.hpp"
#include <iostream>

DungeonXMLReader::DungeonXMLReader()
{

}

DungeonXMLReader::~DungeonXMLReader()
{
	
}

void DungeonXMLReader::SetDungeonTilesFromXML(std::string filepath, Dungeon* dungeon)
{
	// Create empty XML document within memory
    pugi::xml_document doc;
    
    // Load XML file into memory
    // Remark: to fully read declaration entries you have to specify
    // "pugi::parse_declaration"
    pugi::xml_parse_result result = doc.load_file(filepath.c_str(),
												pugi::parse_default);
    if (!result)
    {
        std::cout << "Parse error: " << result.description()
            << ", character pos= " << result.offset;
        return;
    }
    
    pugi::xml_node tileRoot = doc.child("DungeonXMLRoot").child("Tiles");

	int iterator = 0;
	
	//go thorugh each tile type in tiles node
	for (pugi::xml_node tileType = tileRoot.first_child(); tileType; tileType = tileType.next_sibling())
	{	
		std::cout << tileType.first_child().name() << ": " << tileType.first_child().value() << std::endl;	
	}

	/*
	for(size_t i = 0; i < dungeon->dungeonTileSet.size(); i++)
	{
		dungeon->dungeonTileSet[i] = 
	}
	*/
}
