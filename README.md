*This project has been created as part of the 42 curriculum by __ssharmaz__*.

# Description

This project is a small 2D game.
Its purpose is to have you work with textures, sprites, and other basic gameplay elements.

# Instructions

Current implementation should be executed on linux. 

## How to run
Make first:
```
make
```
then run with
```
./so_long <map-file.ber>
```

# Resources

## MiniLibX Documentation
https://harm-smits.github.io/42docs/libs/minilibx/getting_started.html#initialization


# TODO

### Proper window management
Now so_long opens a window, but it could not be closed. 

### Add t_game struct for saving the game data
Create a t_game struct for map, player position, collectible count, and move counter.

### Map loading
Read the .ber file, load it into memory, split it into rows, and store width/height.

### Basic map validation
Check all mandatory subject rules: 
- allowed characters only
- rectangular map
- walls around the border
- exactly one P
- exactly one E
- at least one C

### Path validation so the player can reach every collectible and the exit

### Draw a map with all objects
Start with a simple tile-based renderer: floor, wall, player, collectible, exit. Load XPM assets with MiniLibX, calculate window size from map dimensions, and draw the full map each frame or redraw on movement.

### Implement player management with W/A/S/D
- Handle W/A/S/D pressing
- Block movement through walls
- Collect C
- count moves
- Allow to go through E after all collectibles are gathered

### Print move counter

### Verify cleanup and error handling.
Free map memory, destroy images/windows/display, and exit cleanly on errors or window close.

### Add test maps and a test script
Create a few valid and invalid .ber maps:
- minimal valid map
- bad borders
- bad counts
- unreachable collectible
- unreachable exit
- non-rectangular map
Create a test script to ensure ./so_long return an Error in every case it should. 

### Norminette

### Test with Valgrind

### Do bonus?
