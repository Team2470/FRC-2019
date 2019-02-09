


Autonomous vs Teleoperated
======
1. No difference between the two modes.

Drive
======
##Basic Flow
1. 

Release Hatch
======
##Basic Flow
1. Driver pulls up to "station"
2. DS alerts user that its within TBD inches of anything 
3. Driver tells bot to go into "autonomous release":
4. Bot goes into "autonomous release":
	- camera switches "VISION_PROCESSOR"
	- align center of robot with center of target
	- align front of bot parallel with target front
	- move within TBD inches of target
	- DS shows that bot is controlling the bot
	- all other control of bot is disabled
	- DS shows that bot is "aligned"
5. Driver selects to release hatch
	- Bot pushes off hatch
	- TBD if bot will need to move backwards or something at this time....
6. Bot return back to "driver operated"
	- camera switches "DRIVER_CAMERA"

##Alternate Flows
1. Driver can abort out of "autonomous release"
	- Bot returns to "driver operated"
	- DS shows the user is in controller

## Design Notes


Climb Podium
======
##Basic Flow
Driver tells bot to "approach podium"
2. Bot switches camera to  "DRIVER_CAMERA"
3. Driver drives up to podium
	- DS shows distance from front of bot
	- DS shows angle
4? Should bot take over at all?
5. DS will show if bot is aligned correctly
6. Driver put bot in "climb" mode
	- Is there anything we should disable at this time? maybe the control of movement is VERY slow??
	- DS shows that the bot is in "climb"
7. Driver tells bot to rise
	- Bot actuates its front and rear lift actuators
	- DS displays when bot has cleared the podium
8. The driver tells the bot to "fall forward"
	- Bot retracts its front lifters
	- Bot drives forward - TBD how long (how do we not drive off podium??) or is this driver controlled
    - if manually controlled only allow it to go forward?
    - greatly limit how fast the bot can maneuver
	- Driver tells bot to retract its rear lifters

##Alternate Flows
1. Driver can abort
  - Bot will stop anything autonomous that it's doing
  - 
