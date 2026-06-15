+ Critical note
- Default map folder (maps) are in the same directory as .h and .cpp and can be selected whichever file path from console
- Specific file path expect full and specific input like "C:/School/ValidMap1.txt", or "ValidMap1.txt"
- File path must include .txt at the end

+ Extension
- iostream: 
	- Console input/output across all files
- vector: 
	- Dynamic arrays for adjacency lists, neighbour lists, and A* path storage
	- Used in PathFinder, GraphList, GraphTools
- map:
	- key-value mappings for node label and index used in Graph
	- g-cost tracking used in PathFinder
- string:
	- File paths, error messages, and user input
	- Used in Validation, PathFinder, Map, GraphManager
- algorithm:
	- sort() for ordering neighbours lists by distance/weight in GraphTools and GraphList
	- reverse() for path construction in PathFinder
- set:
	- Closed list (explored cells) in PathFinder
	- Visited node tracking in DFS/BFS inside GraphTools
- queue:
	- BFS queue in GraphTools
	- A* Open List priority queue in PathFinder
- cmath:
	- sqrt for Euclidean distance calculations in GraphTools and PathFinder
- iomanip:
	- fixed and setprecision() for formatted decimal output of edge weights and path costs in GraphTools and PathFinder
- fstream:
	- File reading in Map and File writing in PathFinder
- sstream:
	- Included in Map for string stream operation during map parsing
- limits:
	- limit stream size in Validation to flush the cin input buffer

+ Class
- 