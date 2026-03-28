# so_long Project Guide

This file describes the project as it works now.

The current project already covers the core mandatory gameplay loop:
- load a `.ber` map
- validate that the map is well-formed and playable
- create the MLX window with the correct size
- load XPM textures
- draw the map
- move the player with `W`, `A`, `S`, `D`
- collect every `C`
- print the move count after each successful move
- allow exiting only after all collectibles are gathered
- close cleanly on win, `Esc`, invalid input, or window close

## 1. Main Approach

The project is built around four simple ideas.

### 1. The map is the source of truth

The map stored in `game->map` is not only input data. It is also the live game
state.

That means:
- validation reads from it
- rendering reads from it
- movement updates it

Because of that, there is one shared representation of the world instead of
separate copies for logic and drawing.

### 2. Fail early before graphics

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

This matters because the map decides:
- whether the program should even start
- where the player is
- how many collectibles exist
- how large the window must be

### 3. One struct owns the whole program

The `t_game` struct stores all long-lived state:
- MLX pointers
- image pointers
- map data
- map dimensions
- player position
- collectible counters
- move counter

This keeps function signatures small and makes cleanup predictable.

### 4. Redraw the whole map after each change

The current render strategy is intentionally simple:
- when the window is exposed, draw everything
- when the player moves, draw everything again

That is not the most optimized approach, but it is easy to reason about and is
perfectly fine for a small 42 project.

## 2. Tile Meaning

The game uses the classic `so_long` tile set:

- `1`: wall
- `0`: floor
- `P`: player
- `C`: collectible
- `E`: exit

These characters are used in three places:
- map validation
- rendering
- movement rules

## 3. Runtime Logic

### Step 1: program start

`main()` creates a `t_game`, calls `game_init()`, then enters `mlx_loop()`.

`main()` stays small on purpose. It delegates real work to dedicated modules.

### Step 2: input validation

`game_init()` first zero-initializes the full struct, then checks:
- there is exactly one map argument
- the file name ends with `.ber`

If that fails, the program exits before touching MLX.

### Step 3: map loading

`map_load()` opens the file and reads it line by line with `get_next_line()`.

This is important because blank lines must be preserved. If the project used a
split function that skipped empty lines, an invalid map could look valid after
parsing.

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

At this point the map is structurally correct, but it still might be impossible
to finish.

### Step 5: path validation

That is why the project also runs `map_validate_path()`.

The path check answers a different question:

**Can the player actually reach every collectible and the exit?**

This is where `flood_fill()` is needed.

`flood_fill()` starts at the player position and marks every reachable non-wall
tile. After that traversal, the code scans the copied map. If any `C` or `E`
is still untouched, the map is rejected.

Without `flood_fill()`, the project would accept maps that are formally correct
but unwinnable.

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

### Step 8: movement rules

`move_player()` enforces the gameplay rules:

- moving outside the map does nothing
- moving into a wall does nothing
- moving onto floor succeeds
- moving onto a collectible succeeds and increments `collected`
- moving onto the exit is blocked until `collected == collectibles`
- moving onto the exit after all collectibles are gathered ends the game

On every successful non-exit move, the function:
- changes the old player tile to `0`
- changes the new tile to `P`
- updates `player_x` and `player_y`
- increments `moves`
- prints the move count
- redraws the map

The move counter is printed only for successful moves, which matches the game
logic: failed attempts do not count as movement.

### Step 9: cleanup

Every exit path goes through `game_exit()`, which calls `game_destroy()`.

That cleanup path frees:
- loaded textures
- map memory
- the MLX window
- the MLX display connection

Having one shared cleanup path prevents partial-startup leaks and keeps the
error paths simple.

## 4. Why The Map Is Copied For Flood Fill

`flood_fill()` marks visited tiles.

If it ran directly on `game->map`, the real game state would be damaged:
- walls and floors would no longer be distinguishable in the same way
- rendering would no longer reflect the original tile layout
- movement would operate on modified data

That is why `duplicate_map()` exists.

The pair has a clear division of responsibility:
- `duplicate_map()` protects the real game state
- `flood_fill()` answers the reachability question

## 5. Function-By-Function Explanation

### `src/so_long/so_long.c`

`int main(int ac, char **av)`
- Entry point of the program.
- Creates the main `t_game` object.
- Starts initialization, enters the MLX loop, and performs final cleanup when
  the loop returns.

### `src/so_long/startup.c`

`static int has_ber_extension(char *path)`
- Checks whether the provided path ends with `.ber`.
- Exists to reject invalid input before opening the file.

`static void install_hooks(t_game *game)`
- Registers the keyboard hook, window-destroy hook, and expose hook.
- Exists so all event wiring is kept in one small place.

`void game_destroy(t_game *game)`
- Frees textures, map memory, window resources, and MLX display state.
- Exists to centralize cleanup logic.

`void game_exit(t_game *game, int exit_code, char *message)`
- Optional error printing plus cleanup plus `exit()`.
- Exists so success and error exits use the same shutdown path.

`void game_init(t_game *game, int ac, char **av)`
- Zero-initializes the full state, validates input, loads and validates the map,
  creates the window, loads textures, draws the map, and installs hooks.
- Exists as the single bootstrap function for the whole project.

`int handle_destroy(t_game *game)`
- Called when the user closes the window.
- Exists to adapt the MLX event callback to the shared exit path.

`int handle_keypress(int keysym, t_game *game)`
- Handles `Esc` and movement keys.
- Exists to translate raw keyboard events into game actions.

### `src/so_long/helpers.c`

`void logerr(char *s)`
- Writes an error string to standard error followed by a newline.
- Exists as the project's tiny shared error-output helper.

### `src/so_long/map_load.c`

`static int append_map_row(t_game *game, char *row)`
- Grows the `game->map` array by one row and appends the new string.
- Exists because the file is read incrementally and the row count is not known
  in advance.

`static int store_map_line(t_game *game, char *line)`
- Removes the trailing newline from a line returned by `get_next_line()` and
  stores the row.
- Exists to normalize file input into plain map strings.

`void map_free(char **map)`
- Frees a null-terminated array of strings.
- Exists because both the real map and the flood-fill copy use the same layout.

`void map_load(t_game *game, char *path)`
- Opens the `.ber` file and fills `game->map` row by row.
- Exists to isolate all file-reading logic from validation and gameplay.

### `src/so_long/map_validate.c`

`static int is_valid_tile(char tile)`
- Checks whether a character belongs to the allowed tile set.
- Exists to make character validation explicit and readable.

`static void register_tile(t_game *game, int *players, int x, int y)`
- Updates counters and stores the player position while the map is scanned.
- Exists so one pass over the map can both validate and collect gameplay data.

`static void validate_rows(t_game *game, int *players)`
- Checks rectangular shape, valid characters, and closed borders for every row.
- Exists to group all per-cell structural rules in one place.

`static void validate_counts(t_game *game, int players)`
- Verifies the required counts for player, exit, and collectibles.
- Exists because tile counts are a different validation concern from row shape.

`void map_validate(t_game *game)`
- Orchestrates structural validation, resets gameplay counters, and launches the
  reachability check.
- Exists as the public validation entry point after loading.

### `src/so_long/map_path.c`

`static char **duplicate_map(char **map, int height)`
- Builds a deep copy of the map.
- Exists so path validation can modify the copy without damaging the real map.

`static void flood_fill(char **map, int x, int y, t_game *game)`
- Recursively marks every reachable non-wall tile.
- Exists to prove the map is playable, not only well-formed.

`static void check_reachable_tiles(t_game *game, char **copy)`
- Scans the flood-filled copy for unreachable `C` or `E` tiles.
- Exists to turn the traversal result into a simple final validation decision.

`void map_validate_path(t_game *game)`
- Creates the map copy, runs flood fill, checks the result, and frees the copy.
- Exists as the public reachability-validation function.

### `src/so_long/render.c`

`static void destroy_image(void *mlx, void **img)`
- Safely destroys one MLX image and nulls its pointer.
- Exists to keep image cleanup repetitive but safe.

`static void load_asset(void **img, t_game *game, char *path, char *name)`
- Loads one XPM file and verifies that its size matches `TILE_SIZE`.
- Exists so all asset loading follows the same validation rules.

`static void *tile_image(t_game *game, char tile)`
- Chooses the correct sprite for a given map tile.
- Exists to convert map characters into image pointers.

`static void draw_tile(t_game *game, int x, int y)`
- Draws one tile at the correct pixel position.
- Exists to keep the map-drawing loop small and readable.

`void load_textures(t_game *game)`
- Loads all five required game textures.
- Exists as the public texture-loading step during startup.

`void destroy_textures(t_game *game)`
- Destroys all loaded textures.
- Exists as the matching cleanup step for `load_textures()`.

`int draw_map(t_game *game)`
- Clears the window and redraws every map tile.
- Exists as the main render entry point used during startup, expose events, and
  successful movement.

### `src/so_long/move.c`

`static void print_number(int number)`
- Writes a positive integer to standard output without using `printf`.
- Exists to support move-count printing with minimal dependencies.

`static void print_moves(int moves)`
- Prints the move count followed by a newline.
- Exists so move output formatting lives in one place.

`static void apply_move(t_game *game, int next_x, int next_y, char next_tile)`
- Performs the state update for a successful move onto floor or collectible.
- Exists to keep `move_player()` focused on rules and branching.

`void move_player(t_game *game, int dx, int dy)`
- Applies the movement rules, handles collectibles, blocks premature exit usage,
  prints moves, redraws the map, and ends the game on a valid exit move.
- Exists as the single gameplay action for keyboard movement.

### `src/gnl/get_next_line.c`

`static char *ft_zerostring(size_t size)`
- Allocates a zero-filled string buffer.
- Exists as a small local helper for dynamic string storage inside GNL.

`static char *ft_realloc_str(char **src, size_t size)`
- Grows the persistent storage string before appending fresh read data.
- Exists because `get_next_line()` builds the current line incrementally.

`static char *get_line(char **str)`
- Extracts the next complete line from storage and keeps any remainder for the
  next call.
- Exists to separate "read more bytes" from "return one line."

`char *get_next_line(int fd)`
- Reads from the file descriptor until one line is available or EOF is reached.
- Exists because map loading is line-oriented and blank rows must be preserved.

## 6. What Is Still Outside The Current Scope

The current gameplay loop is in place, but a few project-level tasks remain:
- add an automated map test script
- run `norminette`
- run Valgrind checks
- decide whether to continue into bonus features

Bonus work would likely mean:
- enemy patrols
- sprite animation
- on-screen move counter
- additional polish beyond the mandatory part
