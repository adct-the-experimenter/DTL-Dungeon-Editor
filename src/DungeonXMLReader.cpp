#include "DungeonXMLReader.h"
#include <iostream>

DungeonXMLReader::DungeonXMLReader()
{
	m_dungeonPtr = nullptr;
}

DungeonXMLReader::~DungeonXMLReader()
{
    m_dungeonPtr = nullptr;
}

void DungeonXMLReader::SetPointerToDungeon(Dungeon* thisDungeon){m_dungeonPtr = thisDungeon;}

