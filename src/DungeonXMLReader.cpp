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
	
	//go through each tile type in tiles node
	for (pugi::xml_node tileType = tileRoot.first_child(); tileType; tileType = tileType.next_sibling())
	{	
		DungeonTile::TileType type = DungeonTile::TileType::EMPTY;
		
		//std::cout << tileType.first_child().name() << ": " << tileType.first_child().value() << std::endl;
		
		if(tileType.first_child().value() ==  "GREEN"){type = DungeonTile::TileType::GREEN; break;}
		else if(tileType.first_child().value() ==  "BLUE"){ type = DungeonTile::TileType::BLUE; break;}
		else if(tileType.first_child().value() ==  "RED"){ type = DungeonTile::TileType::RED; break;}
		else if(tileType.first_child().value() ==  "TOP"){ type = DungeonTile::TileType::TOP; break;}
		else if(tileType.first_child().value() ==  "TOP_LEFT"){ type = DungeonTile::TileType::TOP_LEFT; break;}
		else if(tileType.first_child().value() ==  "TOP_RIGHT"){ type = DungeonTile::TileType::TOP_RIGHT; break;}
		else if(tileType.first_child().value() ==  "LEFT"){ type = DungeonTile::TileType::LEFT; break;}
		else if(tileType.first_child().value() ==  "CENTER"){ type = DungeonTile::TileType::CENTER; break;}
		else if(tileType.first_child().value() ==  "RIGHT"){ type = DungeonTile::TileType::RIGHT; break;}
		else if(tileType.first_child().value() ==  "BOTTOM_LEFT"){ type = DungeonTile::TileType::BOTTOM_LEFT; break;}
		else if(tileType.first_child().value() ==  "BOTTOM"){ type = DungeonTile::TileType::BOTTOM; break;}
		else if(tileType.first_child().value() ==  "BOTTOM_RIGHT"){ type = DungeonTile::TileType::BOTTOM_RIGHT; break;}
		else{std::cout << "Tile type not handled!" << "i:" << iterator << std::endl; break;}
			
		dungeon->dungeonTileSet[iterator]->setType(type);
		
		iterator++;
	}
	
	dungeon->setTiles();
}
