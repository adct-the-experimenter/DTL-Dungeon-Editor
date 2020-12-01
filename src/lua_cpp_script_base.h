
//lua c library files
extern "C" {
    #include "lua.h"
    #include "lauxlib.h"
    #include "lualib.h"
}

#include "scripted_enemy.h"


//function to initialize lua interpreter
void InitLuaInterpreter();

//function to tun enemy logic from lua script
void RunEnemyLogicFromScript(ScriptedEnemy* se_ptr, 
							std::string lua_file_path, 
							float& timeStep,int& enemyState, int& loopCount, int& enemyFaceDirection );

//function to free resources for lua interpreter and close it
void EndLuaInterpreter();
