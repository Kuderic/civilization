# Dog Fortress

## Overview
**Dog Fortress** intends to be a simulation-like game (or rather a game-like simulation, since there is no winning).
It will stem inspiration from games such as Dwarf Fortress, Rimworld, Spore, and The Sims, among other simulation-styled games.

The gameplay will revolve around managing a colony of dogs (subject to change), each of which having its own needs, personality,
and characteristics. The player will be allowed to designate overall jobs for the colony to complete
such as mining, cutting down trees, building, crafting, harvesting, etc. Then, the dogs will attempt to complete the
jobs based on their assigned labors and 

The graphics for my game will be ASCII or tileset-based allowing for me to focus more on implementing gameplay mechanics and coding.
Below are some images from Dwarf Fortress, which will most closely resemble how I envision my game to look.

**Note:** By default Dwarf Fortress uses ASCII graphics. Tilesets are user-created and distributed
giving the game many graphical variations.

<img src="https://i.imgur.com/RwuGfv8.png" width="800"/>
<img src="https://is1-ssl.mzstatic.com/image/thumb/Purple111/v4/24/76/c7/2476c735-34c1-5730-faad-2c4583a4880e/pr_source.png/0x0ss.jpg" width="800"/>
<img src="https://cdn.vox-cdn.com/thumbor/pFP6_HQrC8gZ8O0u0YYy6cVsdaA=/0x58:1238x883/1200x800/filters:focal(0x58:1238x883)/cdn.vox-cdn.com/uploads/chorus_image/image/36556910/Huge_War_no_casaulties.0.0.JPG" width="800"/>
<img src="https://i.redd.it/jusc0a1jag1y.jpg" width="800"/>

## Possible Features

Some planned features to give a general idea of what I will attempt to do:

* Keyboard-based UI with possible mouse support
* Characteristics for colonists
  * Health, weight, age, walk-speed, skills, clothes and items
  * Body parts with individualized health (highly optional)
    * i.e. Damaged legs would affect walk speed
* A labor manager to designate which jobs each colony member is allowed to perform
* Skills system
  * i.e. Mining raises mining skill, which affects mining speed
* Mineable and buildable walls
* Resources that can be crafted or used in constructions
* Z-levels (up-down axis). Each tile (cube) would contain a wall and floor.
  * Can only view one level at a time.
* Basic combat system
* Animals to hunt/milk/shear/capture
* Pathing algorithm for units (Dijkstra's algorithm--each tile is a node).
* Hunger/thirst system for colonists
* Planting crops for harvest
* Sleeping in beds
* Procedural or random terrain generation
* Sounds for certain actions

## Libraries
The libraries which I currently plan to use in my project.

Core openFrameworks libraries:
* of.events
* of.graphics
  * ofImage
  * ofGraphics
  * ofTrueTypeFont
* of.math
  * ofVec2f (or ofVec3f if my game is 3-D)
* of.sound
* of.types
  * ofColor

openFrameworks addons:
* ofxGui
* OpenGL (maybe)
* FreeType (maybe)
