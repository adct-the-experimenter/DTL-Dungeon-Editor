#include "DungeonCreator.h"

DungeonCreator::DungeonCreator()
{
	ptrDungeonToEdit = nullptr;
	
	m_tile_input = DungeonTile::TileType::RED;
    m_enemy_input = EnemyInput::NONE;
    m_item_input = ItemInput::NONE;
	
}

DungeonCreator::~DungeonCreator()
{
	
}


void DungeonCreator::SetDungeonToEdit(Dungeon* dPtr)
{
	ptrDungeonToEdit = dPtr;
}

void DungeonCreator::handle_events(Event& thisEvent)
{
	if(thisEvent == Event::MOUSE_DOWN)
	{
		SDL_GetMouseState( &mouseX, &mouseY );
		m_mouseState = MouseState::MOUSE_DOWN;
	}
	else if(thisEvent == Event::MOUSE_UP)
	{
		SDL_GetMouseState( &mouseX, &mouseY );
		m_mouseState = MouseState::MOUSE_UP;
	}
}

void DungeonCreator::logic()
{
	//for now, every time mouse is clicked a tile is put
	if(m_mouseState == MouseState::MOUSE_DOWN)
	{
		m_dungeonCreatorState = DungeonCreatorState::NONE;
		
		DungeonCreator::SetStateFromInputCode();
	
		switch(m_dungeonCreatorState)
		{
			case DungeonCreatorState::PUT_TILE:
			{
				DungeonCreator::PutTile(m_tile_input);
				break;
			}
			
			case DungeonCreatorState::PUT_ENEMY:
			{
				DungeonCreator::PutEnemy(m_enemy_input);
				break;
			}
			default:{break;}
		}
	}
	
	
	
	//reset mouse state
	m_mouseState = MouseState::NONE;
	//reset dungeon creator state
	m_dungeonCreatorState = DungeonCreatorState::NONE;
	//reset tile and enemy input
	m_tile_input = DungeonTile::TileType::RED;
	m_enemy_input = EnemyInput::NONE;
}

void DungeonCreator::PutTile(DungeonTile::TileType type)
{
	//std::cout << "Put tile called!\n";
	//std::cout << "mouseX: " << mouseX << " , mouseY: " << mouseY << std::endl;
	
	if(ptrDungeonToEdit)
	{
		int tileX,tileY;
		
		 //Adjust to camera
		tileX = mouseX + ptrDungeonToEdit->lCamera.x;
		tileY = mouseY + ptrDungeonToEdit->lCamera.y;
		
		//std::cout << "tileX: " << tileX << " , tileY: " << tileY << std::endl;
		
		DungeonTile* thisTile = ptrDungeonToEdit->getDungeonTileFromPosition(tileX,tileY);
		thisTile->setType(type);
		thisTile->setTileClips();
	}
}

void DungeonCreator::PutEnemy(EnemyInput enemy_type)
{
	if(ptrDungeonToEdit)
	{
		int tileX,tileY;
		
		 //Adjust to camera
		tileX = mouseX + ptrDungeonToEdit->lCamera.x;
		tileY = mouseY + ptrDungeonToEdit->lCamera.y;
		
		//std::cout << "tileX: " << tileX << " , tileY: " << tileY << std::endl;
		
		ptrDungeonToEdit->m_enemy_inventory.CreateScriptEnemy();
		ptrDungeonToEdit->m_enemy_inventory.GetEnemyVector()->back()->placeChar(tileX,tileY);
	}
}

void DungeonCreator::GetTextInput(std::string text){m_textCode = text;}

void DungeonCreator::SetStateFromInputCode()
{
	if(m_textCode == "hole"){m_dungeonCreatorState = DungeonCreator::DungeonCreatorState::PUT_TILE; m_tile_input = DungeonTile::TileType::CENTER;}
	if(m_textCode == "red"){m_dungeonCreatorState = DungeonCreator::DungeonCreatorState::PUT_TILE; m_tile_input = DungeonTile::TileType::RED;}
	if(m_textCode == "green"){m_dungeonCreatorState = DungeonCreator::DungeonCreatorState::PUT_TILE; m_tile_input = DungeonTile::TileType::GREEN;}
	if(m_textCode == "blue"){m_dungeonCreatorState = DungeonCreator::DungeonCreatorState::PUT_TILE; m_tile_input = DungeonTile::TileType::BLUE;}
	if(m_textCode ==  "top"){m_dungeonCreatorState = DungeonCreator::DungeonCreatorState::PUT_TILE; m_tile_input = DungeonTile::TileType::TOP; }
	if(m_textCode ==  "topleft"){m_dungeonCreatorState = DungeonCreator::DungeonCreatorState::PUT_TILE; m_tile_input = DungeonTile::TileType::TOP_LEFT; }
	if(m_textCode ==  "topright"){m_dungeonCreatorState = DungeonCreator::DungeonCreatorState::PUT_TILE; m_tile_input = DungeonTile::TileType::TOP_RIGHT; }
	if(m_textCode ==  "left"){m_dungeonCreatorState = DungeonCreator::DungeonCreatorState::PUT_TILE; m_tile_input = DungeonTile::TileType::LEFT; }
	if(m_textCode ==  "right"){m_dungeonCreatorState = DungeonCreator::DungeonCreatorState::PUT_TILE; m_tile_input = DungeonTile::TileType::RIGHT; }
	if(m_textCode ==  "bottomleft"){m_dungeonCreatorState = DungeonCreator::DungeonCreatorState::PUT_TILE; m_tile_input = DungeonTile::TileType::BOTTOM_LEFT; }
	if(m_textCode ==  "bottom"){m_dungeonCreatorState = DungeonCreator::DungeonCreatorState::PUT_TILE; m_tile_input = DungeonTile::TileType::BOTTOM; }
	if(m_textCode ==  "bottomright"){m_dungeonCreatorState = DungeonCreator::DungeonCreatorState::PUT_TILE; m_tile_input = DungeonTile::TileType::BOTTOM_RIGHT; }
	if(m_textCode == "script"){m_dungeonCreatorState = DungeonCreator::DungeonCreatorState::PUT_ENEMY; m_enemy_input = DungeonCreator::EnemyInput::SCRIPTED_ENEMY;}
}
