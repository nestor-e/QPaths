prgm: QPaths.cpp QPaths.h DataBuilder.h DataBuilder.cpp Tile.h Tile.cpp
	g++ -std=c++11 -O3 -o QLearnPathFinder QPaths.cpp Tile.cpp DataBuilder.cpp


dbg: QPaths.cpp QPaths.h DataBuilder.h DataBuilder.cpp Tile.h Tile.cpp
	g++ -g -std=c++11 -o QLearnPathFinderDBG QPaths.cpp Tile.cpp DataBuilder.cpp

clean:
	-@rm *.o QLearnPathFinder QLearnPathFinderDBG 2>/dev/null
