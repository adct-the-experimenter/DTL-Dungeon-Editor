#include "DungeonCreator.h"

DungeonCreator::DungeonCreator()
{
	ptrDungeonToEdit = nullptr;
	
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
		m_dungeonCreatorState = DungeonCreatorState::PUT_TILE;
	}
	
	switch(m_dungeonCreatorState)
	{
		case DungeonCreatorState::PUT_TILE:
		{
			DungeonCreator::PutTile(DungeonTile::TileType::CENTER);
		}
	}
	
	//reset mouse state
	m_mouseState = MouseState::NONE;
	//reset dungeon creator state
	m_dungeonCreatorState = DungeonCreatorState::NONE;
}

void DungeonCreator::PutTile(DungeonTile::TileType type)
{
	std::cout << "Put tile called!\n";
	std::cout << "mouseX: " << mouseX << " , mouseY: " << mouseY << std::endl;
	
	if(ptrDungeonToEdit)
	{
		int tileX,tileY;
		
		 //Adjust to camera
		tileX = mouseX + ptrDungeonToEdit->lCamera.x;
		tileY = mouseY + ptrDungeonToEdit->lCamera.y;
		
		std::cout << "tileX: " << tileX << " , tileY: " << tileY << std::endl;
		
		DungeonTile* thisTile = ptrDungeonToEdit->getDungeonTileFromPosition(tileX,tileY);
		thisTile->setType(type);
		thisTile->setTileClips();
	}
}

void DungeonCreator::SetupCamera()
{
	/*
    //Mouse offsets
    int x = 0, y = 0;
    
    //Get mouse offsets
    SDL_GetMouseState( &x, &y );
    
    //Move camera to the left if needed
    if( x < globalTileWidth )
    {
        camera.x -= 20;
    }
    
    //Move camera to the right if needed
    if( x > SCREEN_WIDTH - globalTileWidth )
    {
        camera.x += 20;
    }
    
    //Move camera up if needed
    if( y < globalTileWidth )
    {
        camera.y -= 20;
    }
    
    //Move camera down if needed
    if( y > SCREEN_HEIGHT - globalTileWidth )
    {
        camera.y += 20;
    }
    
     //Keep the camera in bounds.
    if( camera.x < 0 )
    {
        camera.x = 0;    
    }
    if( camera.y < 0 )
    {
        camera.y = 0;    
    }
    if( camera.x > LEVEL_WIDTH - camera.w )
    {
        camera.x = LEVEL_WIDTH - camera.w;    
    }
    if( camera.y > LEVEL_HEIGHT - camera.h )
    {
        camera.y = LEVEL_HEIGHT - camera.h;    
    } 
    * */
    
}
