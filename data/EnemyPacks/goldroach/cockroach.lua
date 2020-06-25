


--[[ Enemy State ]]--
--[[ enums for enemy state copied from C++ side ]]--
MOVING_NO_PLAYER = 0 
MOVING_SEE_PLAYER = 1
HIT_BY_WEAPON = 2
HIT_PLAYER = 3
PUSHED_BACK = 4
COLLIDE_WITH_WALL = 5
--[[ Enemy State ]]--




--[[ Logic implemenetation ]]--


--[[ random number from 0 to 3]]--

function logic(timeStep,randomNumber, enemyState)
	
	
	--print("Running logic cockroach.lua!")
	--print("random number:", randomNumber)
	--print("enemy state:", enemyState)
	--print("timeStep:", timeStep)
	
	moveUp(timeStep)
	
	moveLeft(timeStep)
	
	moveRight(timeStep)
	
	moveRight(timeStep)
	
	moveDown(timeStep)
	
end




