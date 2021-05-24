OpenCraft, a Minecraft younger cousin (much younger)

![OpenCraft](https://user-images.githubusercontent.com/37122127/119279525-93409c00-bc2c-11eb-8a84-c1f4793359d7.png)

This game is developed with pure C++ and OpenGL, no game engines, no frameworks.  
# Description
It's a sandbox-like game, the player can travel anywhere and build anything. This freedom is possible because the game world is made of blocks, that the player can destroy and arrange freely. The game supports Third-Person Perspective (TPP - the camera is behind the player), but also First-Person Perspective (FPP - the camera is in the place of the characters eyes). The player can walk and run on an endless map.
# Controls
* Movement: W, S, A, D
* Jump: Space
* Flashlight (enable/disable): L
* Run: Double-tap W
* Adjusting Camera Distance: Mouse wheel
* Camera Movement: Mouse
# Game Mechanics
The game world consists of chunks. Chunk is a block set of 16 blocks wide, 16 blocks deep, and 128 blocks high.  
Each block can be destroyed, and then it can be replaced with another block. There are 256 different block types (IDs from 0 to 255, where 0 is an air).  
Every modification is saved on the world map. The chunks are loaded dynamically from the map. When the player enters a new area and the map in that location is empty, then new chunks are generated dynamically.  
When the player goes far away from a chunk, then this chunk is not rendered, but its state is saved in the map memory, so it can be loaded at any time.  
The player can choose a block to modify by looking at it. An invisible close-range laser beam comes out of the eyes of the character, when it is directed at a block, this block is the selected block, so it can be destroyed or another block can be placed on top of it.
# Software
* Language: [C++](https://www.cplusplus.com/) 17
* Graphics API: [OpenGL](https://www.opengl.org/)
* OpenGL Implementation: [freeglut](http://freeglut.sourceforge.net/)
* Platform: [Windows](https://www.microsoft.com/en-us/windows) 7 SP1 and newer
