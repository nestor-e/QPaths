Edward Nestor
CSCI 402: AI
Final Project: Q Learning Path Finder

        Directories:
The program and source code are in the src directory.
The data files describing the layout of the tiles is in the tileData directory.
Stored outputs from the program are in the results directory.


        Compiling:
From the src directory, the program can be compiled using:
    g++ -std=c++11 -o QLearnPathFinder QPaths.cpp Tile.cpp DataBuilder.cpp

or:
    make prgm


        Running:
From the src directory, run the program using:
    ./QLearnPathFinder {path to data} {initialize Q y/n} {use verbose printing y/n}

The data path should point to a metadata file containing required details and
file paths for loading in the map of tiles.
The correct path for this repository and data set is: ../tileData/metadata.txt

The second argument selects if the Q table should be pre-filled based on distance
from the home tile.

The third argument selects if Q Learning algorithm should report training progress
and values.

For example, to run the program with this data set, with training reports but
without initializing the Q table, the correct invocation is:
    ./QLearnPathFinder ../tileData/metadata.txt n y


        Read-Eval-Print Loop:
Once the program loads the data and completes the Q Learning process, it enters a
read-eval-print loop to allow specific paths to be computed.
    - To find the path to a room, type the name of the room
    - To list all rooms in the data, type "list"
    - To exit the loop, type "quit"
