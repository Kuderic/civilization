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

- [ ] Add wall and floor to Tile class
	* Each tile may contain a floor and wall
	* Wall will be drawn first if it exists. Otherwise floor is drawn
- [ ] Implement Wall class
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