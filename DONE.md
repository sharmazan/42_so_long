# so_long Project Guide

This file explains the project as it exists now.

The current project is no longer only a validation skeleton. It now:
- checks the input map path
- loads the `.ber` file
- validates map structure and playability
- computes the window size from the map
- loads XPM assets
- draws the whole map as static tiles
- keeps the window alive until the user presses `Esc` or closes it

What is still missing:
- player movement
- collectible pickup
- move counter
- win logic

## 1. Main Approach

The architecture follows one rule:

**the program should trust the map before it starts the visual part.**

That means the startup order is:
1. initialize `t_game`
2. validate arguments
3. load the map
4. validate the map
5. compute window size
6. initialize MLX
7. create the window
8. load the tile images
9. draw the map
10. enter the MLX loop

This order is important because:
- invalid maps should fail early with clear errors
- the map defines the future window size
- rendering depends on valid tile data
- gameplay will later depend on the same trusted state

## 2. Central State: `t_game`

Everything important lives in `t_game`.

The idea is simple:
- one struct stores all long-lived state
- every stage of the program receives the same object
- cleanup becomes predictable because one object owns everything

Current fields:

- `mlx`
  MLX connection pointer returned by `mlx_init()`.

- `win`
  MLX window pointer returned by `mlx_new_window()`.

- `floor_img`
  Image pointer for the floor tile.

- `wall_img`
  Image pointer for the wall tile.

- `player_img`
  Image pointer for the player tile.

- `collectible_img`
  Image pointer for the collectible tile.

- `exit_img`
  Image pointer for the exit tile.

- `map_path`
  The path received from the command line.

- `map`
  The loaded map as `char **`.

- `window_width`
  Window width in pixels.

- `window_height`
  Window height in pixels.

- `map_width`
  Map width in tiles.

- `map_height`
  Map height in tiles.

- `player_x`
  Player column from the map.

- `player_y`
  Player row from the map.

- `collectibles`
  Number of collectibles in the map.

- `collected`
  Reserved for future gameplay.

- `exits`
  Number of exits in the map.

- `moves`
  Reserved for future gameplay.

This struct already contains what the next steps will need, so movement and
render updates can reuse the same state instead of redesigning the program.

## 3. Runtime Logic

### Step 1: `main`

`main()` creates a `t_game`, calls `game_init()`, then enters `mlx_loop()`.

`main()` is intentionally small because the real logic belongs in dedicated
functions.

### Step 2: bootstrap

`game_init()` first zero-initializes every field in `t_game`.

This matters because cleanup is allowed to run even after partial startup. A
field that starts as `NULL` or `0` is safe to check later.

### Step 3: argument validation

The program currently accepts only:
- exactly one argument after the program name
- a filename ending with `.ber`

If the input is wrong, the program exits before touching MLX.

### Step 4: map loading

`map_load()` opens the file and reads it line by line with `get_next_line()`.

This approach is used because the map is naturally line-based and blank lines
must be preserved. A blank line inside the file must be seen and rejected later,
not silently skipped.

### Step 5: map validation

`map_validate()` checks:
- the map is not empty
- the first row is not empty
- the map is rectangular
- only valid symbols are used
- the border is fully closed by walls
- there is exactly one player
- there is exactly one exit
- there is at least one collectible

Then `map_validate_path()` checks reachability.

### Step 6: reachability check

Format validation alone does not guarantee that a map is playable.

A map can look correct and still be impossible to finish:
- a collectible may be trapped
- the exit may be blocked off
- the player may be isolated from the rest of the map

That is why the project uses `flood_fill`.

`flood_fill` starts from the player position and walks through every reachable
non-wall tile. After that traversal, if a `C` or `E` is still untouched, the
map is invalid.

This is the reason `flood_fill` exists:

**it verifies playability, not just file format.**

### Step 7: window size

Once the map is valid:
- `window_width = map_width * TILE_SIZE`
- `window_height = map_height * TILE_SIZE`

The current `TILE_SIZE` is `32`, so every tile image is expected to be `32x32`.

### Step 8: graphics setup

After the map is known to be valid, the program:
- calls `mlx_init()`
- creates the window
- loads all XPM assets
- draws the map once
- installs the hooks

The assets live in the root `assets/` directory and are loaded at runtime.

### Step 9: redraw behavior

The program uses an expose hook so the map is redrawn if the window needs to be
painted again.

That means the render path is not only "draw once and hope." The current code
already has a proper redraw entry point.

### Step 10: cleanup

Every exit goes through `game_exit()`, which calls `game_destroy()`.

`game_destroy()` frees:
- all loaded images
- the map
- the MLX window
- the MLX display connection

This gives the project one shared cleanup path for:
- invalid input
- invalid maps
- missing assets
- MLX startup failures
- `Esc`
- window close

## 4. Why The Map Is Copied For Path Validation

`flood_fill` marks visited cells.

If it modified the real map:
- the original tile data would be lost
- future rendering and gameplay would no longer know what each tile originally
  was

So the code first makes a deep copy with `duplicate_map()` and runs
`flood_fill()` on that copy only.

That is why both functions are needed:
- `duplicate_map()` preserves the real game state
- `flood_fill()` answers the reachability question

## 5. Function-By-Function Explanation

This section explains every current function and why it exists.

### `src/so_long/so_long.c`

#### `int main(int ac, char **av)`

Purpose:
- create the main game state
- initialize the program
- enter the MLX loop
- run final cleanup after the loop ends

Why it exists:
- it is the program entry point
- it stays intentionally small so the rest of the logic remains modular

### `src/so_long/startup.c`

#### `static int has_ber_extension(char *path)`

Purpose:
- check whether the provided map path ends with `.ber`

Why it exists:
- map filenames are part of the input contract
- failing early here produces a clear user error

#### `static void install_hooks(t_game *game)`

Purpose:
- register all current MLX callbacks

Current hooks:
- key press
- window destroy
- expose / redraw

Why it exists:
- hook setup is easier to maintain when it lives in one place

#### `void game_destroy(t_game *game)`

Purpose:
- free every resource owned by `t_game`

Why it exists:
- cleanup should be centralized
- partial startup failures should still be able to clean safely

#### `void game_exit(t_game *game, int exit_code, char *message)`

Purpose:
- print an optional error
- destroy resources
- terminate the process

Why it exists:
- all exits should behave consistently

#### `void game_init(t_game *game, int ac, char **av)`

Purpose:
- run the complete startup sequence

Why it exists:
- startup order matters
- this function enforces that order from validation through first render

#### `int handle_destroy(t_game *game)`

Purpose:
- handle the window close event

Why it exists:
- the user must be able to close the window cleanly

#### `int handle_keypress(int keysym, t_game *game)`

Purpose:
- react to key input

Current behavior:
- exits on `Esc`

Why it exists:
- it is the minimal interactive hook required at this stage

### `src/so_long/helpers.c`

#### `void logerr(char *s)`

Purpose:
- write an error message to standard error

Why it exists:
- it keeps error output consistent across the project

### `src/so_long/map_load.c`

#### `static int append_map_row(t_game *game, char *row)`

Purpose:
- append one newly read row to the dynamic map array

Why it exists:
- the loader does not know the final map height in advance

#### `static int store_map_line(t_game *game, char *line)`

Purpose:
- normalize one line returned by `get_next_line()`

What it does:
- removes a trailing newline when present
- appends the cleaned row into `game->map`

Why it exists:
- the in-memory map should store pure tile rows, not newline characters

#### `void map_free(char **map)`

Purpose:
- free any `char **` map

Why it exists:
- both the real map and temporary copies need the same cleanup logic

#### `void map_load(t_game *game, char *path)`

Purpose:
- load the map file into memory

Why it exists:
- loading and validation are different concerns
- keeping them separate makes the code clearer

### `src/so_long/map_validate.c`

#### `static int is_valid_tile(char tile)`

Purpose:
- decide whether a character belongs to the allowed tile set

Why it exists:
- it isolates the tile alphabet rule in one helper

#### `static void register_tile(t_game *game, int *players, int x, int y)`

Purpose:
- update counters while the validation pass scans the map

Why it exists:
- validation also needs to extract useful runtime state such as player
  coordinates and collectible count

#### `static void validate_rows(t_game *game, int *players)`

Purpose:
- perform the main structural scan of the map

What it checks:
- rectangular shape
- legal characters
- closed borders

Why it exists:
- these are the core file-structure rules of `so_long`

#### `static void validate_counts(t_game *game, int players)`

Purpose:
- validate required entity counts after scanning

Why it exists:
- count validation is clearer as a separate stage from row scanning

#### `void map_validate(t_game *game)`

Purpose:
- run the full validation pipeline

Why it exists:
- callers should only need one public validation entry point

### `src/so_long/map_path.c`

#### `static char **duplicate_map(char **map, int height)`

Purpose:
- create a deep copy of the map

Why it exists:
- the reachability algorithm must not damage the real map

#### `static void flood_fill(char **map, int x, int y, t_game *game)`

Purpose:
- walk through every reachable tile starting from the player

How it works:
- stop outside the map
- stop on walls
- stop on already visited cells
- mark the current cell
- recurse in four directions

Why it exists:
- it is the actual playability check
- without it, the program would only know that the map is well-formed, not
  solvable

#### `static void check_reachable_tiles(t_game *game, char **copy)`

Purpose:
- inspect the flood-filled copy for unreachable `C` or `E`

Why it exists:
- `flood_fill()` marks reachability, and this function converts that result into
  a final pass/fail decision

#### `void map_validate_path(t_game *game)`

Purpose:
- run the complete reachability validation stage

Why it exists:
- it gives the rest of the project one clean public entry point for path
  validation

### `src/so_long/render.c`

#### `static void destroy_image(void *mlx, void **img)`

Purpose:
- safely destroy one MLX image pointer and clear it

Why it exists:
- image cleanup is repeated for every loaded asset

#### `static void load_asset(void **img, t_game *game, char *path, char *name)`

Purpose:
- load one XPM file into one MLX image pointer

What it also checks:
- the file exists and loads correctly
- the loaded image size matches `TILE_SIZE`

Why it exists:
- every asset must satisfy the same runtime rule
- a helper avoids repeating the same error handling five times

#### `static void *tile_image(t_game *game, char tile)`

Purpose:
- translate a map character into the image that should be drawn for that tile

Why it exists:
- rendering should depend on tile meaning, not scattered `if` blocks in the map
  loop

#### `static void draw_tile(t_game *game, int x, int y)`

Purpose:
- draw one tile at one map coordinate

Why it exists:
- the full map loop becomes simpler when the per-tile draw operation is isolated

#### `void load_assets(t_game *game)`

Purpose:
- load every tile image used by the current renderer

Why it exists:
- the project now has a fixed mandatory asset set and needs one place to load
  all of it

#### `void destroy_assets(t_game *game)`

Purpose:
- destroy every loaded tile image

Why it exists:
- all image cleanup should stay together

#### `void draw_map(t_game *game)`

Purpose:
- redraw the entire map to the window

What it does:
- clears the window
- loops over every row and column
- draws the image that corresponds to each map tile

Why it exists:
- the current renderer is intentionally simple and reliable
- full redraws are easy to understand and are enough for this stage

#### `int handle_expose(t_game *game)`

Purpose:
- redraw the map when the window needs repainting

Why it exists:
- a drawn window should remain visually correct after expose events

### `src/gnl/get_next_line.c`

The loader uses `get_next_line()` because the map file is line-based.

That is useful because:
- each line becomes one row
- blank lines are preserved
- validation sees the real file structure

#### `static char *ft_zerostring(size_t size)`

Purpose:
- allocate a zeroed string buffer

Why it exists:
- the line reader needs clean temporary buffers and expanded storage

#### `static char *ft_realloc_str(char **src, size_t size)`

Purpose:
- grow the persistent storage buffer before appending new data

Why it exists:
- file reads arrive in chunks and the buffered data size is not fixed

#### `static char *get_line(char **str)`

Purpose:
- cut the next full logical line out of the persistent storage buffer

Why it exists:
- `get_next_line()` needs a helper that separates "read bytes" from
  "return one line"

#### `char *get_next_line(int fd)`

Purpose:
- return the next line from a file descriptor

Why it exists:
- it matches the loader's needs exactly

Important safety detail:
- the loop must handle `storage == NULL`
- that guard prevents the null-pointer crash that happens if `ft_strchr()` is
  called before any storage exists

## 6. Why Static Full-Map Redraw Is Enough Right Now

The current renderer redraws the whole map.

That is the right choice for this stage because:
- the map is still small
- there is no movement yet
- correctness is more important than optimization
- the code stays simple and easy to debug

Later, movement can still keep this approach or optimize it if needed.

## 7. Assets

The project now has a minimal asset set:
- `assets/floor.xpm`
- `assets/wall.xpm`
- `assets/player.xpm`
- `assets/collectible.xpm`
- `assets/exit.xpm`

These assets are intentionally simple.

Their job right now is not to look final. Their job is to prove that:
- asset loading works
- tile-to-image mapping works
- map dimensions match rendered dimensions
- cleanup works for loaded images

## 8. Build Logic

The root `Makefile` builds:
- `libft`
- `minilibx`
- `so_long`
- `get_next_line`

The inner `src/so_long/Makefile` builds:
- `so_long.c`
- `helpers.c`
- `startup.c`
- `map_load.c`
- `map_validate.c`
- `map_path.c`
- `render.c`
- `../gnl/get_next_line.c`

Current links:
- `-lmlx`
- `-lft`
- `-lXext`
- `-lX11`
- `-lm`
- `-lz`

## 9. Test Maps

The `maps/` directory contains:
- one valid map
- several invalid maps

The current tests support verification of:
- valid startup
- bad characters
- bad borders
- bad counts
- non-rectangular maps
- unreachable collectible
- unreachable exit
- blank lines

## 10. Current State

What is already implemented:
- input validation
- map loading
- structural map validation
- reachability validation
- map-based window sizing
- asset loading
- static map rendering
- redraw on expose
- cleanup for maps, images, window, and MLX state

What comes next:
- W/A/S/D movement
- collision against walls
- collectible pickup
- move counting
- exit behavior after collecting everything
