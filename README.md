*This project has been created as part of the 42 curriculum by ssharmaz*.

# Description

This project is a small 2D game.
Its purpose is to have you work with textures, sprites, and other basic gameplay elements.

You need to provide a map file (there are some in the maps/valid folder).
Move the player with `W`, `A`, `S`, `D`.

# Instructions

Current implementation should be executed on linux, where MLX lib and X11 libraries installed.

If your MLX headers or library are in a non-standard location, override the flags when building:

```bash
make MLX_CPPFLAGS='-I/path/to/mlx/include' MLX_LDFLAGS='-L/path/to/mlx/lib'
```

## How to run the game:
Make first:
```
make
```
then run with
```
./so_long <map-file.ber>
```
You could find some maps to play in the `maps/valid` folder.

# Resources

## MiniLibX Documentation
https://harm-smits.github.io/42docs/libs/minilibx/getting_started.html#initialization

# so_long implementation

How the project works:
- it loads a `.ber` map
- validate that the map is well-formed and playable
- create the MLX window with the correct size
- load XPM textures
- draw the map
- print the move count after each successful move
- open the exit after all collectibles are gathered
- allow exiting only after all collectibles are gathered
- close cleanly on win, `Esc`, invalid input, or window close

A player could:
- move the player with `W`, `A`, `S`, `D`
- collect every `C`
- reach exit 'E' after they collected all `C`.

## 1. Approach description

### 1.1. One struct for the program data

The `t_game` struct stores all long-lived state:
- MLX pointers
- image pointers
- map data
- map dimensions
- player position
- collectible counters
- move counter

### 1.2. Fail early before graphics

The program does not open a window until the map is trusted.

The startup order is:
1. initialize `t_game`
2. validate arguments
3. load the map
4. validate map structure and reachability
5. compute the window size
6. initialize MLX
7. create the window
8. load textures
9. draw the map
10. install hooks and enter the loop

### 1.3. The map as the source of truth

The map stored in `game->map` is holding the game state.
- rendering reads from it
- movement updates it

### 4. Redraw the whole map after each change

The game will redraw the whole map:
- when the window is exposed, draw everything
- when the player moves, draw everything again

## 2. Maps description

The game's map holds the tile set:

- `1`: wall
- `0`: floor
- `P`: player
- `C`: collectible
- `E`: exit

To be valid, a map must contain 1 exit, 1 starting position and at least 1
collectible.

Besides that,
- The map must be rectangular.
- The map must be enclosed/surrounded by walls. If it is not, the program will
return an error.
- The program will verify if there is a valid path in the map to any collectible or the exit.

## 3. Runtime Logic

### Step 1: program start

`main()` creates a `t_game`, calls `game_init()`, then enters `mlx_loop()`.

### Step 2: input validation

`game_init()` first zero-initializes the full struct, then checks:
- there is exactly one map argument
- the file name ends with `.ber`

### Step 3: map loading

`map_load()` opens the file and reads it line by line with `get_next_line()`.

### Step 4: map validation

`map_validate()` checks:
- the file is not empty
- the first row is not empty
- every row has the same width
- only valid tile characters are used
- the outer border is fully closed by walls
- there is exactly one player
- there is exactly one exit
- there is at least one collectible

At this point the map is correct, but we still need to validate paths:
that every collectible and exit are accessable for a player.

### Step 5: path validation

`map_validate_path()` create a copy of a map and use `flood_fill()` to verify paths.

`flood_fill()` starts at the player position and marks every reachable non-wall tile. After that traversal, the code scans the copied map. If any `C` or `E`
is still untouched, the map is rejected.

But `flood_fill()` marks visited tiles.

If it ran directly on `game->map`, the real game state would be damaged.
That is we need `duplicate_map()`.

### Step 6: graphics setup

After validation succeeds, `game_init()` computes:
- `window_width = map_width * TILE_SIZE`
- `window_height = map_height * TILE_SIZE`

Then it:
- initializes MLX
- creates the window
- loads all tile images
- draws the current map
- installs event hooks

### Step 7: event handling

The game currently reacts to three kinds of events:

- `Esc`
  Close the game immediately.

- window close button
  Close the game through the same cleanup path.

- expose event
  Redraw the map when the window needs repainting.

- `W`, `A`, `S`, `D`
  Try to move the player.

  You could also interrupt the execution with a Ctrl-C. In this case allocated memory will not be freed.

### Step 8: movement rules

`move_player()` enforces the gameplay rules:

- moving outside the map does nothing
- moving into a wall does nothing
- moving onto floor succeeds
- moving onto a collectible succeeds and increments `collected`
- moving onto the exit is blocked until `collected == collectibles`
- when `collected == collectibles`, the exit is redrawn with the open texture
- moving onto the exit after all collectibles are gathered ends the game with a `You Win` message.

On every successful non-exit move, the function:
- changes the old player tile to `0`
- changes the new tile to `P`
- updates `player_x` and `player_y`
- increments `moves`
- prints the move count
- redraws the map

The move counter is printed only for successful moves, which matches the game logic:
failed attempts do not count as movement.

### Step 9: cleanup

Every exit path goes through `game_exit()`, which calls `game_destroy()`.

That cleanup path frees:
- loaded textures
- map memory
- the MLX window
- the MLX display connection
