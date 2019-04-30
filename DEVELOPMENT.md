# Developer Log

## Week One

### 4/9/2018 - External Library Experimentation
#### ofTrueTypeFont
I chose to experiment with this external library because outputting font properly to the screen is
very important to make sure that menus and descriptions work properly. It was also simple enough that I would be able to
get it to work properly as my first openFramework test project.
* Font has to go in the project folder or else nothing will show up to the screen
  * No warning message--simply does nothing
* Resources go into bin/data folder
* Will not output console message if file is not find
* Instances of ofTrueTypeFont must be setup before being used
* Each instance can turn a string into a texture that will then be drawn at (x, y)
* Supports multi-line strings
* There are many methods to modify how the font is formatted
  * setLetterSpacing() -- Space between characters (kerning)
  * setLineHeight() -- Space between consecutive lines of text in multiline strings
  * setSpaceSize() -- Size of spaces between words
* Very important getStringBoundingBox() method
  * Useful for drawing text based around other graphical elements
  * Returns an ofRectangle object. Can get itsa width and height for finding the width/height of the string
```cpp
ofRectangle rect = myFont.getStringBoundingBox(myString, x, y);

ofSetColor(0xcccccc);
ofDrawRectangle(rect.x, rect.y, rect.width, rect.height);
```

## Week Two

### 4/20/19 - Setting up the Project
* Used openFrameworks project generator to create visual studio project
* Linked local project to github repository
* Set up catch2 testing
* Set up a way to switch between running unit tests and running actual program

### Creating base classes
#### Board Class
* Class to hold all tiles in the game
#### Tile Class
* Has a position
* Has a pointer to an ofImage object that is drawn when draw() is called
* Acts as a node with edges to neighboring tiles
* Alternate methods for getting neighboring tiles:
	* Using a 2-D vector in Board class and getting adjacent tiles in vector
	* Getting adjacent tiles by position since every tiles' position is stored
	* Ultimately a runtime / design choice

I didn't run into any issues initially when making my Board and Tile classes. However, when 
I tried to use an image for my tiles I had issues loading my tile image. I eventually figured out
that even though my application runs from the bin folder, openFramworks classeslooks in bin/data for resources files.
Because of this, I had to go an extra directory up to access my actual resources folder
(i.e. `../../resources/tile.png`).


### 4/25/19 - Small Changes to Base Classes
* Changed the Board class tiles_ variable to use a 2-D array
	* A 2-D array helps with implementing methods and pathing algorithms.
* Added kBoardWidth and kBoardHeight constants to Board class
* Made tiles_ and position_ private variables of their respective classes.
* Renamed class variables so that they now end with an underscore, adhering to Google's C++ style guide.
* Added getters for Board and Tile


### 4/26/19 - Implementing Walls and Floors
Checklist of what I plan to accomplish today. 

- [x] Add wall and floor to Tile class
	* Each tile may contain a floor and wall
	* Wall will be drawn first if it exists. Otherwise floor is drawn
- [x] Implement Wall class
	* Walls restrict movement and will be mineable
	* Will have different types: i.e. stone, dirt, wood
- [x] Implement Floor class
	* Likely will just contain an image, but is good for future features
	* Will have different types: i.e. stone, dirt, wood
	* Could affect walk speed of colonists
- [x] Create different types of floors and walls
	* Can either be done with subclasses or an enum
	* Will have different images and properties (time to dig)
- [ ] Try to only draw outermost wall layer and leave rest black

While working on the Floor class, I couldn't decide how I wanted to manage loading floor textures.
Loading an image has to be done once before it can be assigned to a floor.
I've decided to make a static private variable (located in Floor) for each image,
but other alternatives I came up with were storing them in a vector and creating a custom class
for loading and referencing them.


### 4/27/19 - Basic Colonists and Gameplay
Today I want to implement basic colonists and gameplay features. To-do list:

- [x] Create Colonist class
	* Will look like dogs because dogs are cute
	* At first won't do anything until other actions are implemented
	* Start with one colonist at first. Implement more later
	- [ ] User-controlled movement
		* Let user control movement with arrow keys
		* Tests wall collision (make sure colonists can't move onto a tile with a wall)
	- [ ] Idle movement
		* Move in a random direction periodically
	- [ ] Dijkstra Algorithm
		* Calculate the shortest path between nodes (tiles)
		* Avoid walls
	- [ ] Directed movement
		* Give a colonist a location to move to
		* It will attempt to path there while avoiding walls

While making the Colonist class, I ran into the dilemma of how I should keep track of my entities (colonists).
Should they be stored in ofApp, Board, or in Tile? I decided to store them in Board because a Board
is made up entities and tiles but a tile isn't necessarily made up of an entity (although they are drawn
at the same position). To track entities as part of the Board class, I now need to change
how I keep track of my tiles positions in terms of pixels (for drawing them)
as well as their position in position on the board (in relation to other tiles)
so that it is consistent with how I store entity positions.
To do this, I will be storing all tile and entity positions
such that (x, y) represents their position in terms of each other
(e.g. (1, 0) means the tile in the top row, second from the left).
I will then calculate all pixel positions and dimensions when drawn() is called.

I also ended up making a parent class Entity that holds Colonist. Entity can be extended
to include other entities such as animals and enemies in the future.

### 4/28/19 - Basic Colonists and Gameplay (Cont.)

Today I am focusing on how I want to interface between my entities and the board and handle
the processing of my entities turns.
This is a large and important  task because they should interact in
such a way that remains loosely coupled so that my is program easily extendable.

I have decided to have my entities read the board state each frame and then create and store a 
TurnAction based on what they want to do. This TurnAction will then be parsed by the
board (or some other parser class) which will then call the correct public methods to achieve the action.
e.g. Dig Wall East -> entity.AddExperience(Mining) && east_tile.RemoveWall()

Furthermore, actions will take varying amounts of time. Since the game operates at
60 frames per second, I will need to store a counter in TurnAction that keeps track of how
many frames have passed for that given TurnAction.
This also means that each frame when the Entity is asked to create a TurnAction,
they won't create a new one if their current TurnAction is still what they want to do.
e.g. TurnAction is Dig Wall which takes 120 frames (2 seconds). entity.GetTurnAction()
will not alter TurnAction as long as the dig designation on the wall is not removed by the player.

Finishing yesterday's to-do list will have to wait until tomorrow.

- [x] Create TurnAction class
	* Has an internal progress bar which is incremented each frame
		* Max progress determined by action. e.g. Mining = 1600, Walking = 300
		* Progress speed is based on owner Entity's properties
		* This allows different entities to have differing speeds for actions
	* When progress is full, is parsed by board (for now) to complete action
- [x] Create Camera class
	* Can be moved with arrow keys
	* Draws parts of the board to screen
	* Board can be made bigger than screen

One issue I ran into while making the Camera class was parsing my clicks to the screen.
This is because now my mouse's coordinates didnt match up to the tile coordinates if
my camera was not at (0, 0). I easily fixed this by adding the camera's position vector
to the mouse position.

### 4/29/19 - Basic Colonists and Gameplay (Cont.)

Today I will try to finish up pathing algorithms for entities and start working
on basic gameplay/adding more features.

Also, I've come up with a way to only draw walls that are exposed to air.
I just check each wall's neighboring tiles.
If at least one neighbor has no wall, then I draw the wall.

To-do list:
- [x] Try to only draw outermost wall layer and leave rest black
- [x] Create Colonist class
	* Will look like dogs because dogs are cute
	* At first won't do anything until other actions are implemented
	* Start with one colonist at first. Implement more later
	- [ ] User-controlled movement
		* Let user control movement with arrow keys
		* Tests wall collision (make sure colonists can't move onto a tile with a wall)
	- [ ] Idle movement
		* Move in a random direction periodically if idle
	- [ ] Dijkstra Algorithm
		* Calculate the shortest path between nodes (tiles)
		* Avoid walls
	- [ ] Directed movement
		* Give a colonist a location to move to
		* It will attempt to path there while avoiding walls