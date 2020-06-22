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
    
    enum class DungeonCreatorState : std::int8_t { NONE = 0, PUT_TILE, PUT_ENEMY, PUT_ITEM};
    enum class MouseState : std::int8_t {NONE = 0, MOUSE_DOWN, MOUSE_UP, MOUSE_MOVING};
    
    
    enum class EnemyInput : std::int8_t {NONE = 0, COCKROACH, ZOMBIE, SCRIPTED_ENEMY };
    
    enum class ItemInput : std::int8_t {NONE = 0};
    
    void SetDungeonToEdit(Dungeon* dPtr);
    
    void SetupCamera();
    
    void PutTile(DungeonTile::TileType type);
    
    void PutEnemy(DungeonCreator::EnemyInput enemy_type);
   
    //game loop function to be called from main
    void handle_events(Event& thisEvent);
    void logic();
    
    void GetTextInput(std::string text);
    
    
    
    
private:

	int mouseX;
	int mouseY;
	
	std::string m_textCode;
	
	DungeonCreatorState m_dungeonCreatorState;
    MouseState m_mouseState;
    
    Dungeon* ptrDungeonToEdit;
    
    void SetStateFromInputCode();
    
    DungeonTile::TileType m_tile_input;
    EnemyInput m_enemy_input;
    ItemInput m_item_input;
    
};

#endif
