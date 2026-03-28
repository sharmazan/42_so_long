*This project has been created as part of the 42 curriculum by __ssharmaz__*.

# Description

This project is a small 2D game.
Its purpose is to have you work with textures, sprites, and other basic gameplay elements.

# Instructions

Current implementation should be executed on linux. 

## How to run
Install libraries
```
sudo apt update
sudo apt install libx11-dev libxext-dev libbsd-dev
```

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

## Done
- Proper window management with `Esc` and window-close handling
- `t_game` state for map, window, player position, counters, and loaded assets
- Map loading through `get_next_line`
- Basic map validation for characters, shape, borders, player, exit, and
  collectibles
- Path validation so the player can reach every collectible and the exit
- Static tile rendering with XPM assets for floor, wall, player, collectible,
  and exit
- Window sizing from map dimensions
- Cleanup for map memory, images, window, and MLX display state
- Valid and invalid `.ber` fixture maps

## Next

### Implement player management with W/A/S/D
- Handle W/A/S/D pressing
- Block movement through walls
- Collect C
- count moves
- Allow to go through E after all collectibles are gathered

### Print move counter

### Add a test script
Create a script to ensure `./so_long` returns `Error` on every invalid map and
starts correctly on valid maps.

### Norminette

### Test with Valgrind

### Do bonus?
