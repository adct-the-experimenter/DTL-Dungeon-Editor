#ifndef DUNGEONXMLREADER_H
#define DUNGEONXMLREADER_H

#include <vector> //header for vector container class
#include <sstream> //header for string stream processing
#include <string>

#include "Dungeon.h"

//file to read from xml


class DungeonXMLReader
{
	
public:

	//constructor
	DungeonXMLReader();

	//destructor
	~DungeonXMLReader();

	//function to pass vector of notes to DungeonXMLHandler object
	void SetPointerToDungeon(Dungeon* thisDungeon);

private:

	//pointer to vector of notes
	Dungeon* m_dungeonPtr;

};

#endif
