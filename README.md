# UnRealVirtuality
Hot air balloon game. Inspired by that old-school helicopter flash game, and on-rail arcade shooters. 

https://i.ytimg.com/vi/FEcV7JQEiU4/maxresdefault.jpg


# Gameplay & Design
Designed for virtual reality headsets and motion controllers. 

### Arcade Mode

Pilot a hot air balloon that is automatically moving forward through an endless, procedurally generated environment, filled with obstacles. While also accelerating at an almost imperceptible rate. 

Avoid obstacles and survive for as long as possible. The game ends when the player collides with either an obstacle or the environment, at which point the player is awarded a score based on flight duration/distance covered. 

Screenshot: Updated balloon appearance, and added items/obstacles 
![Screenshot](https://i.ibb.co/72FRrp5/updat6.png)

Screenshot: Testing basic procedural obstacle course, for use in arcade mode. 
![Screenshot](https://i.ibb.co/fDgwMK9/update2.png)


## Items & Devices
  - Spawned as part of / on board the balloon. 
  - Items may be picked up by the player.
  - If anything is dropped (outside of basket/gondola), it is lost.
  - Devices may be interacted with by pushing buttons, turning knobs or pulling levers. 

### Devices 

#### Burners
Ignites flammable gas to heat air inside the envelope. Pull and hold handle to activate. 

#### Meters
Various dials, meters and such, showing wind direction and speed etc. 

### Items

#### Longbow
Use the classic longbow to shoot at things to clear a path, and score points.

#### Umbrella
Foldable umbrella, may be used as a shield while in unfolded state. Unfold by grabbing and moving handle/slider, unfold quickly to 
produce a wind gust effect and push nearby objects in the opposite direction.


## Obstacles

### Cardboard Clouds

#### White
Predictable movement, moves along horizontal path between two points on the Y-axis.

#### Yellow 
Unpredictable movement, sudden changes in direction, speed, path

#### Grey
Produces rain, fog and/Or strong winds and sudden changes in wind direction

#### Dark-Grey/Black
Produces random lightning bolts

### Helium Balloons

#### Red
Random/unpredictable movement which is also affected by wind direction and strength/speed. 
May explode on contact/impact with other obstacles, air balloon/player or arrows.

#### Pink
If punctured these balloons becomes high-velocity projectiles which are launched with force (like rockets) along a randomized flight path, before finally exploding 
shortly thereafter.

### Wind Mill
Rotating blades, affected by wind direction and strength/speed.

### Bridges / Logs


# Controls
Pull burner handle to ignite gas and increase altitude, let go of the handle to decrease altitude. 

Grab / Hold any of the sides of the basket with one of the motion controllers to tilt basket and cause the balloon to move sideways/strafe in the corresponding direction. 

# Misc.

* Wind affects how the balloon moves and wind direction and/or strength/speed changes sporadically 

* Score extra points by disabling, destroying or avoiding obstacles.

# Credits

- Unreal Engine 4.25 (Epic Games)

- Air Balloon Model created by Chroma3D
  - https://www.cgtrader.com/3d-models/aircraft/other/low-poly-cartoon-hot-air-balloon

- Toy Blocks created by muszka_pietruszka
  - https://www.turbosquid.com/3d-models/kids-toys-bricks-3d-model-1596831
  
- Low-Poly Environment by MacKenzie Shirk
  - https://marketplace-website-node-launcher-prod.ol.epicgames.com/ue/marketplace/en-US/product/stylized-low-poly-environment

- Low-Poly cloud mesh by creativeart
  - https://www.cgtrader.com/3d-models/various/various-models/low-poly-clouds-part-01
  
- Longbow & helium balloon models by Valve

- Umbrella model by enzodi24
  - https://www.turbosquid.com/3d-models/max-umbrella-opening-closing/1016555

