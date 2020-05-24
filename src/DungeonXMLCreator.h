#ifndef DUNGEONXMLCREATOR_H
#define DUNGEONXMLCREATOR_H

#include "Dungeon.h"

#include <string>


class DungeonXMLCreator
{
public:

	DungeonXMLCreator();
	~DungeonXMLCreator();
	
	//set pointer to dungeon
	void SetPointerToDungeon(Dungeon* thisDungeon);
	
	//create xml file
	void CreateXMLFile(std::string xml_file_path);
	
	
private:
	Dungeon* m_dungeonPtr;
	
};

#endif
