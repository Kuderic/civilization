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
giving the game many graphical variations. Here are examples of what Dwarf Fortress looks like:

<img src="https://i.imgur.com/RwuGfv8.png" width="800"/>
<img src="https://i.redd.it/jusc0a1jag1y.jpg" width="800"/>

Here are some screenshots from my current progress on Dog Fortress:
<img src="http://i.imgur.com/uU3u40X.png" width="800">

[Click here to see gameplay.](https://i.imgur.com/2hiCD0c.gifv)

## Features
Some planned and completed features to give a general idea of what I will attempt to do:

Features:
[x] Keyboard-based UI with mouse support
[x] Colonists
  [ ] Health, weight, age, walk-speed, skills, clothes and items
  [ ] Body parts with individualized health (highly optional)
    * i.e. Damaged legs would affect walk speed
[x] Other Animals
[x] Mining walls
[x] Building walls
[x] Sounds for actions
[x] Pretty background music
[x] Pathing algorithm for units (A* algorithm).
[x] Camera controls, zoom in-out, pause
[ ] Procedural or random terrain generation
[ ] Resources that can be crafted or used in constructions
[ ] Skills system
  * i.e. Mining raises mining skill, which affects mining speed
[ ] Z-levels (up-down axis). Each tile (cube) would contain a wall and floor.
  * Can only view one level at a time.
[ ] Basic combat system
[ ] A labor manager to designate which jobs each colony member is allowed to perform
[ ] Hunt/milk/shear/capture animals
[ ] Hunger/thirst system for colonists
[ ] Planting crops for harvest
[ ] Sleeping in beds

## Updates
Read DEVELOPMENT.md for updates on my progress. 

## Libraries
The libraries which I plan to use in my project.

Core openFrameworks libraries:
* of.events
* of.graphics
  * ofImage
  * ofGraphics
  * ofTrueTypeFont
* of.math
  * ofVec3f
* of.sound
* of.types
  * ofColor

openFrameworks addons:
* ofxGui
* OpenGL (maybe)
* FreeType (maybe)
