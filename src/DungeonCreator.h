#ifndef DUNGEONCREATOR_H
#define DUNGEONCREATOR_H

#include "Dungeon.h"

#include <array>
#include <algorithm>    // std::random_shuffle
#include <ctime>

//class to modify Dungeon

class DungeonCreator
{
public:
    DungeonCreator();
    ~DungeonCreator();
    
    void SetDungeonToEdit(Dungeon* dPtr);
    
    void SetupCamera();
    
    void PutTile();
   
    //game loop function to be called from main
    void handle_events(Event& thisEvent);
    void logic();
    
    enum class DungeonCreatorState : std::int8_t { NONE = 0, PUT_TILE};
    enum class MouseState : std::int8_t {NONE = 0, MOUSE_DOWN, MOUSE_UP, MOUSE_MOVING};
    
private:

	int mouseX;
	int mouseY;
	
	DungeonCreatorState m_dungeonCreatorState;
    MouseState m_mouseState;
    
    Dungeon* ptrDungeonToEdit;
};

#endif
