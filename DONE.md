# so_long Project Guide

This file explains the project **as it exists now**.

It focuses on:
- the overall approach
- the runtime flow
- the role of `t_game`
- why each function exists
- why map validation is split into several steps

## 1. What The Project Does Right Now

The current project is the **mandatory backbone** of `so_long`.

At this stage it already does these things:
- checks program arguments
- loads a `.ber` map from disk
- stores the map in memory
- validates the map format and content
- checks that the player can really reach all collectibles and the exit
- calculates the window size from the map
- starts MiniLibX only after the map is known to be valid
- exits cleanly on `Esc` or window close

At this stage it does **not** yet do these things:
- draw tiles or sprites
- move the player
- collect items
- print moves
- finish the game

So the project is currently a **safe startup and validation pipeline** for the
future game.

## 2. Main Design Idea

The project is built around one important rule:

**Do not start the graphical part until the map is valid.**

That choice keeps the program simpler and safer.

Why this approach is useful:
- there is no point opening a window for an invalid map
- the map itself tells us how large the window should be
- player position, collectible count, and exit count all come from the map
- later gameplay logic depends on trusted map data

So the startup order is:
1. validate the input path
2. load the map
3. validate the map
4. compute window size
5. initialize MLX
6. enter the event loop

## 3. Central Data Structure: `t_game`

The whole project revolves around `t_game`.

`t_game` exists so that one struct can carry all state needed by:
- startup
- validation
- future rendering
- future movement
- cleanup

Current fields and why they exist:

- `mlx`
  Stores the MLX connection pointer returned by `mlx_init()`.

- `win`
  Stores the window pointer returned by `mlx_new_window()`.

- `map_path`
  Keeps the original map filename passed on the command line.

- `map`
  Stores the loaded map as an array of rows (`char **`).

- `window_width`
  Stores the width of the MLX window in pixels.

- `window_height`
  Stores the height of the MLX window in pixels.

- `map_width`
  Stores the width of the map in tiles.

- `map_height`
  Stores the height of the map in tiles.

- `player_x`
  Stores the player column found in the map.

- `player_y`
  Stores the player row found in the map.

- `collectibles`
  Stores how many `C` tiles exist in the map.

- `collected`
  Reserved for future gameplay so the game can count collected items.

- `exits`
  Stores how many `E` tiles exist in the map.

- `moves`
  Reserved for future gameplay so the game can count player moves.

This struct is intentionally larger than the currently implemented gameplay,
because it avoids redesigning the program later.

## 4. Runtime Flow

Here is the current runtime flow from start to finish.

### Step 1: `main`

`main()` creates a `t_game` variable, calls `game_init()`, then enters
`mlx_loop()`.

The reason `main()` is small is that all startup logic belongs in dedicated
functions, not in the entry point.

### Step 2: argument and state setup

`game_init()` zero-initializes the game struct and checks the argument list.

The program currently expects:
- exactly one map path
- a filename ending with `.ber`

If this fails, the program exits immediately with an error.

### Step 3: map loading

`map_load()` opens the file and reads it line by line with `get_next_line()`.

This is important because line-based reading preserves the real structure of the
map, including blank lines. That makes validation more trustworthy than using a
split helper that might silently skip empty rows.

### Step 4: map validation

`map_validate()` checks:
- the map is not empty
- the first row is not empty
- the map is rectangular
- all symbols are valid
- the border is closed by walls
- there is exactly one player
- there is exactly one exit
- there is at least one collectible

Then `map_validate_path()` checks reachability.

### Step 5: window sizing

Only after the map is valid, the program computes:
- `window_width = map_width * TILE_SIZE`
- `window_height = map_height * TILE_SIZE`

This means the map directly controls the future render area.

### Step 6: MLX setup

Only now does the program call:
- `mlx_init()`
- `mlx_new_window()`
- `mlx_hook()`

This keeps map errors separate from graphics errors.

### Step 7: event loop

Once initialization succeeds, the program enters `mlx_loop()`.

Current input behavior is minimal:
- `Esc` exits
- closing the window exits

### Step 8: cleanup

All exits go through `game_exit()` and `game_destroy()`.

That matters because cleanup must be consistent whether the program exits:
- after a map error
- after an MLX error
- after `Esc`
- after window close

## 5. Why Reachability Needs `flood_fill`

This is the part that often feels unclear at first, so it is worth spelling out.

Checks like:
- rectangular shape
- valid symbols
- closed border
- exactly one `P`
- exactly one `E`
- at least one `C`

are **not enough** to prove the map is playable.

A map can still pass all of those checks and be impossible to finish.

Example:
- the collectible may be boxed in by walls
- the exit may exist but be isolated
- the player may be trapped in a separate area

That is why the project needs `flood_fill`.

`flood_fill` is a graph traversal over the map:
- start from the player position
- walk to every reachable non-wall tile
- mark visited tiles

After that traversal, if any `C` or `E` is still unvisited, the map is invalid.

So the real reason for `flood_fill` is:

**it answers the gameplay question that simple format checks cannot answer:
"Can the player actually reach everything required to win?"**

That is why `flood_fill` is not optional. It is the only part that verifies
playability instead of just file format.

## 6. Why The Map Is Duplicated Before `flood_fill`

`flood_fill` marks visited cells.

If it modified the real map directly:
- the original map data would be destroyed
- later gameplay would not know which tiles were originally `0`, `C`, `E`, or
  `P`

So the code first creates a deep copy of the map and only runs `flood_fill` on
that copy.

This is why `duplicate_map()` exists.

## 7. Function-By-Function Explanation

This section explains **every current function** and why it exists.

### `src/so_long/so_long.c`

#### `int main(int ac, char **av)`

Purpose:
- create the main game state
- initialize the program
- enter the MLX loop
- perform final cleanup

Why it exists:
- every program needs one small entry point
- keeping `main()` short makes the rest of the program easier to reason about

### `src/so_long/startup.c`

#### `static int has_ber_extension(char *path)`

Purpose:
- verify that the provided filename ends with `.ber`

Why it exists:
- the project expects map files in that format
- rejecting bad filenames early makes user errors obvious

#### `static void install_hooks(t_game *game)`

Purpose:
- register MLX/X11 callbacks for key presses and window close

Why it exists:
- hook setup should live in one place
- this keeps `game_init()` focused on startup order

#### `void game_destroy(t_game *game)`

Purpose:
- free all owned runtime resources

What it frees now:
- the map
- the MLX window
- the MLX display connection

Why it exists:
- cleanup logic should not be duplicated across many exit paths

#### `void game_exit(t_game *game, int exit_code, char *message)`

Purpose:
- print an optional error
- destroy resources
- terminate the program

Why it exists:
- centralizes error exits and normal exits
- guarantees cleanup happens consistently

#### `void game_init(t_game *game, int ac, char **av)`

Purpose:
- orchestrate the complete startup sequence

What it does:
- zero-initializes the struct
- validates arguments
- stores the map path
- loads the map
- validates the map
- computes window size
- initializes MLX
- creates the window
- installs hooks

Why it exists:
- startup order matters
- this function enforces that order in one place

#### `int handle_destroy(t_game *game)`

Purpose:
- handle the window close event

Why it exists:
- MLX/X11 callbacks must have a function target
- it lets window-close behavior share the same cleanup path as every other exit

#### `int handle_keypress(int keysym, t_game *game)`

Purpose:
- react to key presses

Current behavior:
- exits when the pressed key is `XK_Escape`

Why it exists:
- it is the minimal input callback needed for a usable window lifecycle

### `src/so_long/helpers.c`

#### `void logerr(char *s)`

Purpose:
- print an error message to standard error followed by a newline

Why it exists:
- keeps output formatting consistent
- avoids duplicating low-level write logic in every error path

### `src/so_long/map_load.c`

#### `static int append_map_row(t_game *game, char *row)`

Purpose:
- append one allocated row to the in-memory `char **map`

Why it exists:
- the map height is not known before reading the file
- the code therefore needs dynamic growth while loading

#### `static int store_map_line(t_game *game, char *line)`

Purpose:
- convert one raw GNL line into one clean map row

What it does:
- removes a trailing newline if present
- appends the row into `game->map`

Why it exists:
- `get_next_line()` returns text lines, but the map should be stored without
  trailing `\n`

#### `void map_free(char **map)`

Purpose:
- free any map array

Why it exists:
- both the real map and temporary validation copies need the same cleanup logic

#### `void map_load(t_game *game, char *path)`

Purpose:
- read the map file into memory

Why it exists:
- loading is a separate concern from validation
- keeping it separate makes error handling and future testing easier

### `src/so_long/map_validate.c`

#### `static int is_valid_tile(char tile)`

Purpose:
- check whether one character belongs to the allowed subject alphabet

Why it exists:
- the character check is reused for every tile in the map
- a helper keeps that rule explicit and easy to maintain

#### `static void register_tile(t_game *game, int *players, int x, int y)`

Purpose:
- update counters and remember key positions while scanning tiles

Why it exists:
- validation needs more than pass/fail
- the game also needs the player position and collectible count for later steps

#### `static void validate_rows(t_game *game, int *players)`

Purpose:
- perform the main row-by-row validation pass

What it checks:
- rectangle shape
- legal tile symbols
- border walls

Why it exists:
- this is the natural place for the structural rules of the map

#### `static void validate_counts(t_game *game, int players)`

Purpose:
- enforce required entity counts after scanning the map

Why it exists:
- counting and checking are conceptually different steps
- separating them keeps the logic clearer

#### `void map_validate(t_game *game)`

Purpose:
- run the full validation pipeline after loading

Why it exists:
- it is the public validation entry point
- callers should not need to know the internal order of validation steps

### `src/so_long/map_path.c`

#### `static char **duplicate_map(char **map, int height)`

Purpose:
- create a writable copy of the map

Why it exists:
- `flood_fill` must modify something
- the original game map must remain unchanged

#### `static void flood_fill(char **map, int x, int y, t_game *game)`

Purpose:
- traverse all tiles reachable from the player

How it works:
- stop on walls
- stop outside the map
- stop on already-visited cells
- mark current cell as visited
- recurse in four directions

Why it exists:
- it proves actual reachability
- it catches invalid maps that look fine structurally but are impossible to win

#### `static void check_reachable_tiles(t_game *game, char **copy)`

Purpose:
- verify that no collectible or exit was left unreachable after flood fill

Why it exists:
- `flood_fill` marks reachable cells, but another function must interpret the
  result and turn it into pass/fail

#### `void map_validate_path(t_game *game)`

Purpose:
- run the complete reachability test

Why it exists:
- it is the public path-validation entry point
- callers should not need to manually duplicate maps or inspect flood-fill
  results

### `src/gnl/get_next_line.c`

These functions exist because `map_load()` needs one reliable line reader.

Using `get_next_line()` is a good fit here because:
- maps are line-based
- blank lines must be preserved
- each file row should become one map row

#### `static char *ft_zerostring(size_t size)`

Purpose:
- allocate a zero-initialized string buffer

Why it exists:
- the reader needs clean temporary buffers and resized storage

#### `static char *ft_realloc_str(char **src, size_t size)`

Purpose:
- grow the internal storage string before appending more read bytes

Why it exists:
- the amount of unread buffered content is not fixed

#### `static char *get_line(char **str)`

Purpose:
- cut the next line out of the persistent storage buffer

Why it exists:
- `get_next_line()` needs a helper that separates "read bytes" from
  "return next logical line"

#### `char *get_next_line(int fd)`

Purpose:
- return the next line from a file descriptor

Why it exists:
- it gives the map loader exactly one row at a time
- it preserves file structure cleanly

Important detail:
- this implementation uses one static storage pointer
- that is acceptable here because the project reads one map file at a time

Important safety fix:
- the loop condition must handle `storage == NULL`
- without that guard, the very first call can segfault when using `libft`'s
  `ft_strchr()`

## 8. Why The Code Uses `get_next_line` Instead Of Splitting The Whole File

Reading the file with `get_next_line()` is intentional.

It is better than building one big string and splitting it later because:
- each physical line is processed exactly once
- blank lines are preserved naturally
- there is no need for a custom split function
- the control flow matches the real structure of the map file

For `so_long`, preserving blank lines matters because a blank line inside the
map should be rejected as invalid, not silently ignored.

## 9. Build Logic

The root `Makefile` builds:
- `libft`
- `minilibx`
- the `so_long` sources
- the `gnl` sources

The inner `src/so_long/Makefile` compiles the game executable from:
- `so_long.c`
- `helpers.c`
- `startup.c`
- `map_load.c`
- `map_validate.c`
- `map_path.c`
- `../gnl/get_next_line.c`

Current link dependencies are:
- `libft`
- `mlx`
- `X11`
- `Xext`
- `m`
- `z`

`ft_printf` is not part of the current active build because the present code
does not use it.

## 10. Map Fixtures

The `maps/` directory is there to support manual validation checks.

It contains:
- one valid minimal map
- several invalid maps covering common rule violations

These files help verify:
- correct acceptance of valid input
- correct rejection of bad borders
- correct rejection of bad counts
- correct rejection of unreachable goals
- correct rejection of blank lines and shape errors

## 11. Current State Of The Architecture

The current architecture is intentionally simple:

- one central runtime struct: `t_game`
- one startup coordinator: `game_init`
- one loading stage: `map_load`
- one validation stage: `map_validate`
- one path-check stage: `map_validate_path`
- one cleanup path: `game_exit` -> `game_destroy`

That is a good base for the next steps because rendering and movement can now be
added on top of trusted map data instead of being mixed together with input
parsing and validation.
