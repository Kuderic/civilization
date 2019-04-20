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

### Setting up the Project
* Used oF project generator to create visual studio project
* Linked local project to github repository
* Set up catch2 testing
* Set up a way to switch between running unit tests and running actual program

### Creating base classes
#### Board Class
* Class to hold all tiles in the game
#### Tile Class
* Has a position
* Acts as a node with edges to neighboring tiles
* Alternate methods for getting neighboring tiles:
	* Using a 2-D vector in Board class and getting adjacent tiles in vector
	* Getting adjacent tiles by position since every tiles' position is stored
	* Ultimately a runtime / design choice