
//lua c library files
extern "C" {
    #include "lua.h"
    #include "lauxlib.h"
    #include "lualib.h"
}

#include "scripted_enemy.h"


//function to initialize lua interpreter
void InitLuaInterpreter();

//function to load all script files from certain xml files
void LoadAllScriptFilesFromXMLFiles();

//function to tun enemy logic from lua script
void RunEnemyLogicFromScript(ScriptedEnemy* se_ptr, std::string lua_file_path, float& timeStep,int& randNumber,int& enemyState );

//function to free resources for lua interpreter and close it
void EndLuaInterpreter();
