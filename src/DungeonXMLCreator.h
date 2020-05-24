#ifndef DUNGEONXMLCREATOR_H
#define DUNGEONXMLCREATOR_H

#include "Dungeon.h"

class DungeonXMLCreator
{
public:

	DungeonXMLCreator();
	~DungeonXMLCreator();
	
	void SetPointerToDungeon(Dungeon* thisDungeon);
	
	void CreateXMLFile();

private:
	Dungeon* m_dungeonPtr;
	
};

#endif
