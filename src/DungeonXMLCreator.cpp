#include "DungeonXMLCreator.h"

#include "pugixml.hpp"
#include <iostream>

DungeonXMLCreator::DungeonXMLCreator()
{
	m_dungeonPtr = nullptr;
	
}

DungeonXMLCreator::~DungeonXMLCreator()
{
	
}

void DungeonXMLCreator::SetPointerToDungeon(Dungeon* thisDungeon){m_dungeonPtr = thisDungeon;}

void DungeonXMLCreator::CreateXMLFile(std::string xml_file_path)
{
	
	std::cout << "Creating dungeon xml file...\n";
	
	// Generate new XML document within memory
    pugi::xml_document doc;
    
    // Generate XML declaration
    auto declarationNode = doc.append_child(pugi::node_declaration);
    declarationNode.append_attribute("version")    = "1.0";
    declarationNode.append_attribute("encoding")   = "ISO-8859-1";
    declarationNode.append_attribute("standalone") = "yes";
    
    // A valid XML doc must contain a single root node of any name
    auto root = doc.append_child("DungeonXML Root");
    
    //create tiles node
    pugi::xml_node tilesNode = root.append_child("Tiles");
    
   
    
    if(m_dungeonPtr)
    {
		std::cout << "Number of tiles: " << m_dungeonPtr->dungeonTileSet.size() << std::endl;
		
		for(size_t i = 0; i < m_dungeonPtr->dungeonTileSet.size(); i++)
		{
			 // Add child based on tile type
			pugi::xml_node nodeChild = tilesNode.append_child("Type");
			
			switch(m_dungeonPtr->dungeonTileSet[i]->getType())
			{
				case DungeonTile::TileType::GREEN:{ nodeChild.append_child(pugi::node_pcdata).set_value("GREEN"); break;}
				case DungeonTile::TileType::BLUE:{ nodeChild.append_child(pugi::node_pcdata).set_value("BLUE"); break;}
				case DungeonTile::TileType::RED:{ nodeChild.append_child(pugi::node_pcdata).set_value("RED"); break;}
				case DungeonTile::TileType::TOP:{ nodeChild.append_child(pugi::node_pcdata).set_value("TOP"); break;}
				case DungeonTile::TileType::TOP_LEFT:{ nodeChild.append_child(pugi::node_pcdata).set_value("TOP_LEFT"); break;}
				case DungeonTile::TileType::TOP_RIGHT:{ nodeChild.append_child(pugi::node_pcdata).set_value("TOP_RIGHT"); break;}
				case DungeonTile::TileType::LEFT:{ nodeChild.append_child(pugi::node_pcdata).set_value("LEFT"); break;}
				case DungeonTile::TileType::CENTER:{ nodeChild.append_child(pugi::node_pcdata).set_value("CENTER"); break;}
				case DungeonTile::TileType::RIGHT:{ nodeChild.append_child(pugi::node_pcdata).set_value("RIGHT"); break;}
				case DungeonTile::TileType::BOTTOM_LEFT:{ nodeChild.append_child(pugi::node_pcdata).set_value("BOTTOM_LEFT"); break;}
				case DungeonTile::TileType::BOTTOM:{ nodeChild.append_child(pugi::node_pcdata).set_value("BOTTOM"); break;}
				case DungeonTile::TileType::BOTTOM_RIGHT:{ nodeChild.append_child(pugi::node_pcdata).set_value("BOTTOM_RIGHT"); break;}
				default:{std::cout << "Tile type not handled!\n"; break;}
			}
			
		}
		
	}
    
    
    // Save XML tree to file.
    // Remark: second optional param is indent string to be used;
    // default indentation is tab character.
	bool saveSucceeded = doc.save_file(xml_file_path.c_str(), PUGIXML_TEXT("  "));
	assert(saveSucceeded);

	std::cout << "Finished creating dungeon xml file!\n";
}
