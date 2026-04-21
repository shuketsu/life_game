#Terminal Game of Life

This is a C implementation of John Conway’s "Game of Life," a famous mathematical concept from 1970. 
It’s a cellular automaton where complex patterns emerge from a few simple rules.

![Banner](~/b301102.png)

The program uses the ncurses library to render the simulation directly in your terminal.


How it works

The game world is a grid where cells live or die based on their neighbors:

   - Survival: A living cell stays alive if it has 2 or 3 neighbors.

   - Death: It dies from loneliness (fewer than 2 neighbors) or overpopulation (more than 3).

   - Birth: A new cell is born in an empty spot if exactly 3 neighbors surround it.


Requirements

You’ll need a C compiler (gcc) and the ncurses development library.

On Ubuntu/Debian, you can install it via:

	sudo apt-get install libncurses5-dev libncursesw5-dev

Setup and Launch

1. Compile the source code:

	gcc main.c -lncurses -o life

2. Run the game:

    ./life

3. To stop the simulation, just press any key.


Technical Details

   - Auto-scaling: The grid automatically detects and fits your terminal window size.

   - Toral World: The edges are connected, so cells that move off-screen wrap around to the other side.

   - Random Start: Every new session starts with a randomized 15% population density.
