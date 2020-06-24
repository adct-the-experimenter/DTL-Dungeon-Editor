#ifndef MY_ENEMY_H
#define MY_ENEMY_H

#include "enemy.h"
#include <array>

//lua c ibrary files
extern "C" {
    #include "lua.h"
    #include "lauxlib.h"
    #include "lualib.h"
}

class ScriptedEnemy : public Enemy
{
    
public:

 //constructor to set up resources
    ScriptedEnemy( int x, int y,int width,int height);

    //destructor to free resources
    virtual ~ScriptedEnemy();
                                    
    
    //function to load media for sprite
    virtual bool loadMedia(LTexture* thisTex, std::string path,SDL_Renderer* gRenderer);
    
    //function to load media outside class
    friend bool loadScriptedEnemyMedia(std::string xml_file_path,
									LTexture* cTexture,
                                    std::vector <SDL_Rect> &clips,
                                    SDL_Renderer* gRenderer );
    //function to free media outside of class
    friend void freeScriptedEnemyMedia(LTexture* cTexture);                                
                        
    
    //function to set 
    void setPointersToMedia(LTexture* cTexture,std::vector <SDL_Rect> &clips);
    

     //Takes key presses and adjusts sprite's velocity
    virtual void handleEvent(Event& thisEvent);
    
    //Takes random seed and determines actions
    virtual void handleEvent_EnemyAI(RNGType& rngSeed);
    
    virtual void logic(float& timeStep, std::vector<DungeonTile*> &dungeonTiles);
    


 /** Move sprite**/
    virtual void move(float& timeStep);
    
    virtual bool moveOnTiles(float& timeStep, std::vector<DungeonTile*> &dungeonTiles);

    //moves dot based on time since last render and returns tile type of tile dot collides with
    virtual DungeonTile::TileType moveOnTiles_TileType(float& timeStep, std::vector<DungeonTile*> &dungeonTiles);
    
    virtual void moveBack(float& timeStep);
    
    //Frame animation 
  
    //function to determine which frame to use
    virtual void setFrame();
    
    
    //Shows the sprite on screen
    virtual void render(SDL_Rect& camera, SDL_Renderer* lRenderer, SDL_Rect* clip = NULL);

//Collision object Functions
    
    //function to do logic for reacting to certain collision types
    virtual void reactToCollision();
    

//State
  
    
    virtual void runLogicState_MovingNoPlayer(float& timeStep);
    virtual void runLogicState_MovingSeePlayer(float& timeStep);
    virtual void runLogicState_HitByWeapon(float& timeStep);
    virtual void runLogicState_HitPlayer(float& timeStep);
    virtual void runLogicState_PushedBack(float& timeStep);
    virtual void runLogicState_CollideWithWall(float& timeStep);
    
    
    //state specific to greedy zombie
    enum class ScriptedEnemyState : std::int8_t {MOVE_UP = 0,MOVE_DOWN,MOVE_LEFT,MOVE_RIGHT,
                                            PAUSE,
                                            DETERMINE_DIRECTION};
        
//Sound
	virtual void sound(AudioRenderer* gAudioRenderer);
	
	int lua_moveUp(lua_State* L, float& timeStep);
    int lua_moveDown(lua_State* L, float& timeStep);
    int lua_moveLeft(lua_State* L, float& timeStep);
    int lua_moveRight(lua_State* L, float& timeStep);
    int lua_pause(lua_State* L,float& timeStep);
    
private:
    //members not inherited from enemy
    
    //Array for probabilities of which direction to take
    std::array <double,5> probabilitiesDirection;
    
    std::stack <ScriptedEnemy::ScriptedEnemyState> state_stack;
    
    void pushState(ScriptedEnemy::ScriptedEnemyState state);
    void popState();
    ScriptedEnemy::ScriptedEnemyState getCurrentState();
    
    void setupScriptedEnemyCollisionObject();
    
    void renderEnemyCollisionBox(SDL_Rect& camera, SDL_Renderer* gRenderer);
    
//Lua functions
    
    //logic for scripted enemy
    void RunLuaLogicForScriptedEnemy(std::string lua_file_path, float& timeStep);
    
    //wrapper functions for C++ functions to be called from Lua
    int lua_moveOnTiles_TileType(lua_State* L,float& timeStep);
    
    
    
    
};

#endif
