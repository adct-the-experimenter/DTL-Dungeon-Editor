#include "lua_cpp_script_base.h"

#include "load_script_files.h"


//pointer to lua interpreter
lua_State * L = nullptr;

//pointer to scripted enemy used in  function wraps for lua
ScriptedEnemy* ext_se_ptr = nullptr;


static int function_wrap_moveUp(lua_State* L)
{
	if(ext_se_ptr)
	{
		float timeStep = lua_tonumber(L,1); //get timestep from first argument
		//std::cout << "up called! timeStep:" << timeStep << std::endl;
		ext_se_ptr->moveUp(timeStep);
	}
	
	return 0;
}

static int function_wrap_moveLeft(lua_State* L)
{
	if(ext_se_ptr)
	{
		float timeStep = lua_tonumber(L,1); //get timestep from first argument
		//std::cout << "left called! timeStep:" << timeStep << std::endl;
		ext_se_ptr->moveLeft(timeStep);
	}
	
	return 0;
}

static int function_wrap_moveRight(lua_State* L)
{
	if(ext_se_ptr)
	{
		float timeStep = lua_tonumber(L,1); //get timestep from first argument
		//std::cout << "right called! timeStep:" << timeStep << std::endl;
		ext_se_ptr->moveRight(timeStep);
	}
	
	return 0;
}

static int function_wrap_moveDown(lua_State* L)
{
	if(ext_se_ptr)
	{
		float timeStep = lua_tonumber(L,1); //get timestep from first argument
		//std::cout << "down called! timeStep:" << timeStep << std::endl;
		ext_se_ptr->moveDown(timeStep);
	}
	
	return 0;
}



void InitLuaInterpreter()
{
	//create a new lua state
	L = luaL_newstate();

	//open all libraries
	luaL_openlibs(L);
	
	//Expose the c++ functions to the lua environment
	lua_register(L, "moveUp", function_wrap_moveUp);
	lua_register(L, "moveLeft", function_wrap_moveLeft);
	lua_register(L, "moveRight", function_wrap_moveRight);
	lua_register(L, "moveDown", function_wrap_moveDown);
	
}

#include <chrono>

void RunEnemyLogicFromScript(ScriptedEnemy* se_ptr, std::string lua_file_path, 
							float& timeStep,int& enemyState, int& loopCount, int& enemyFaceDirection )
{
	
	//std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
	
	if(L)
	{
		luaL_dofile(L, lua_file_path.c_str());
		
		ext_se_ptr = se_ptr;
		
		/* the function name */
		lua_getglobal(L, "logic");
		
		/* the first argument, time step */
		lua_pushnumber(L, timeStep);

		/* the third argument, enemy state */
		lua_pushnumber(L, enemyState);
		
		/* the fourth argument, loop count */
		lua_pushnumber(L, loopCount);
		
		/* the fifth argument, enemy face direction*/
		lua_pushnumber(L, enemyFaceDirection);

		/* call the function with 4 arguments, return 0 result */
		if (lua_pcall(L, 4, 0, 0))     
		{
			std::cout << "lua_pcall() failed! Check lua script " << lua_file_path.c_str() << "\n";
		}
			
		lua_pop(L, 0);
		
	}
	
	//std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
	
	//std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;
}

void EndLuaInterpreter()
{
	if(L)
	{
		lua_close(L);
	}
}
