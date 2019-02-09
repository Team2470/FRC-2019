
The following are a list of use cases for the 2019 robot:
- Drive: The driver moving the bot around the field getting it into position do do a different use case.
- Release Hatch: Aligning the robot up with a target and attaching a hatch.
- Climb Podium: The end game of climbing up the podium for final points.

Drive
======
## Basic Flow
1. Drive will control the movement of the robot via an analog joystick
2. Camera will be in "DRIVER_CAMERA" mode
2. DS will display distance from the front of the bot
3. DS will display "field" angle	

## Alternate Flow

## Design Notes:
- Plan is to use a mecanum drive - cartesian?
- Gyro will "zero" itself to the field at startup

Release Hatch
======
## Basic Flow
1. Driver pulls up to "station"
2. DS alerts user that its within TBD inches of anything 
3. Driver tells bot to go into "autonomous release":
4. Bot goes into "autonomous release":
	- DS shows that bot is controlling the bot
	- Camera switches to "VISION_PROCESSOR"
	- All other control of bot is disabled
	- These will all happen together
		- align center of robot with center of target
		- align front of bot parallel with target front
		- move within TBD inches of target
	- DS shows when the bot is "aligned"
5. Driver selects to release hatch
	- Bot pushes off hatch
	- TBD if bot will need to move backwards or something at this time....
6. Bot return back to "driver operated"
	- camera switches "DRIVER_CAMERA"

## Alternate Flows
1. Driver can abort out of "autonomous release"
	- Bot returns to "driver operated"
	- DS shows the user is in controller

## Design Notes
- The "final" release of the hatch may be done autonomously (step 5)

Climb Podium
======
## Basic Flow
1. Driver tells bot they're going to "approach podium"
2. Bot switches camera to  "DRIVER_CAMERA"
3. Driver drives up to podium
	- DS shows distance from front of bot
	- DS shows angle to field
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

## Alternate Flows
1. Driver can abort
  - Bot will stop anything autonomous that it's doing
 


Autonomous vs Teleoperated
======
- No difference between the two modes.

