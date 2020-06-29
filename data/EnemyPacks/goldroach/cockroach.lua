


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


--[[ loop count from 0 to 9]]--



function logic(timeStep, enemyState, loopCount)
	
	
	--print("Running logic cockroach.lua!")
	--print("enemy state:", enemyState)
	--print("timeStep:", timeStep)
	--print("loop count:", loopCount)
	
	
	--[[ generate a random number integer from 1 to 3]]--
	randNumber = math.random(4) 
	
	if(loopCount == 9.0)
	then
		if( randNumber == 1 )
		then
		   moveUp(timeStep)
		   moveUp(timeStep)
		elseif( randNumber == 2 )
		then   
		   moveLeft(timeStep)
		   moveDown(timeStep)
		elseif( randNumber == 3 )
		then
		   moveRight(timeStep)
		   moveUp(timeStep)
		else
		   moveDown(timeStep)
		end
	end
	
	
end




