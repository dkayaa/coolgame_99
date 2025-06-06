# coolgame_99
Exploring Game Dev using C++ and SDL. Its a pretty basic game where players navigate a maze to find the exit, whilst avoiding enemies. 

## Building
The project uses a cmake file as well as SDL3 and SDL_image libraries. To build the project, first navigate to `CMakeLists.txt` and specify the absolute path to the SDL3 and SDL_image directories.

Then, execute the following commands from the root directory.
```
rm -rf build 
cd build 
cmake ..
make
./coolgame_99
```
## Map Generation
The map is define by a text file `test.txt` located in `/data`. A user can use the following characters to define game artifacts
```
W: Wall 
P: Player 
E: Enemy 
G: Goal
' '(whitespace): Floor
```

An indicative map file is provided in the repo. 

## Enemy Pathfinding: 
Enemy pathfinding is acheived by executing bounded BFS from each player, to some defined `depth`. Any enemies found within these bounds are directed to follow the path to target player. Pathfinding is executed periodically to update enemy pathing. 

## Collision Detection: 
Collision detection is employed using the Separating Axis Theorem (SAT). The game uses two basic shapes; Circles and Rectangles, and SAT is employed every frame to detect and rectify overlapping shapes.