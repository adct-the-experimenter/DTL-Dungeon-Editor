


--[[ Enemy State ]]--
--[[ enums for enemy state copied from C++ side ]]--
MOVING_NO_PLAYER = 0 
MOVING_SEE_PLAYER = 1
HIT_BY_WEAPON = 2
HIT_PLAYER = 3
PUSHED_BACK = 4
COLLIDE_WITH_WALL = 5
--[[ Enemy State ]]--

--[[ Enemy Face Direction]]--
FD_NORTH = 0 
FD_NORTHEAST = 1
FD_EAST = 2
FD_SOUTHEAST = 3
FD_SOUTH = 4
FD_SOUTHWEST = 5
FD_WEST = 6
FD_NORTHWEST = 7


--[[ Logic implemenetation ]]--


--[[ loop count from 0 to 9]]--



function logic(timeStep, enemyState, loopCount, enemyFaceDirection)
	
	
	--print("Running logic cockroach.lua!")
	--print("enemy state:", enemyState)
	--print("timeStep:", timeStep)
	--print("loop count:", loopCount)
	--print("face direction:", enemyFaceDirection)
	
	--[[ generate a random number integer from 1 to 4]]--
	randNumber = math.random(5) 
	
	if(enemyState == MOVING_NO_PLAYER)
	then
		if(loopCount == 9.0)
		then
			if( randNumber == 1 )
			then
			   moveUp(timeStep)
			elseif( randNumber == 2 )
			then   
			   moveLeft(timeStep)
			elseif( randNumber == 3 )
			then
			   moveRight(timeStep)
			else
			   moveDown(timeStep)
			end
		end
	end
	
	if(enemyState == MOVING_SEE_PLAYER)
	then
	
		if(enemyFaceDirection == FD_NORTH)
		then
			moveUp(timeStep)
		elseif(enemyFaceDirection == FD_NORTHEAST)
		then
			moveUp(timeStep)
			moveRight(timeStep)
		elseif(enemyFaceDirection == FD_EAST)
		then
			moveRight(timeStep)
		elseif(enemyFaceDirection == FD_SOUTHEAST)
		then
			moveDown(timeStep)
			moveRight(timeStep)
		elseif(enemyFaceDirection == FD_SOUTH)
		then
			moveDown(timeStep)
		elseif(enemyFaceDirection == FD_SOUTHWEST)
		then
			moveDown(timeStep)
			moveLeft(timeStep)
		elseif(enemyFaceDirection == FD_WEST)
		then
			moveLeft(timeStep)
		elseif(enemyFaceDirection == FD_NORTHWEST)
		then
			moveUp(timeStep)
			moveLeft(timeStep)
		end
	end
	
end
