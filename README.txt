+ Critical note
- Default map folder (maps) are in the same directory as .h and .cpp and can be selected whichever file path from console
- Specific file path expect full and specific input like "C:/School/ValidMap1.txt", or "ValidMap1.txt"
- File path must include .txt at the end
- Map folder is for the example maps used for easy loading
- AStar folder is for AStar saved file

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
	- sqrt() for ordering neighbours lists by distance/weight in GraphTools and GraphList
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
- Cell: represent a single node (grid cell) used by the A* algorithm
- Graph: abstract class defining the graph interface
- GraphList: graph implementation using adjacency list
- GraphTools: static utility class for graph construction and traversal (Load map to graph, DFS, and BFS)
- Map: represent the 20x20 grid loaded from a text file
- PathFinder: implement the A* algorithm and save it to file
- Validation: static utility class for console input validation
- GraphManager: main application controller

+ Validation
- Valid characters only: s x a b c d e f g h i j w p .
- Exactly one start 's' cell
- Exactly one exit 'x' cell
- Exactly 10 collectables from a to j
- Row and Column is 20 counts
- File path:
	- Path must contain a file extension ('.' must be present)
	- Extension must be ".txt" case-insensitive
- Int:
	- must be numeric, reject otherwise
	- value must fall within the specified range input
- String:
	- length must be between the specified range input

+ Instruction
The interface is console-based and expect the user to input from their keyboard
Menu option example look like
	1. Load Map from file
	2. Load Graph from Map
	3. Display Map
	4. Display Graph
	5. Run DFS
	6. Run BFS	
	7. Run AStar
	8. Display AStar Path
	9. Save AStar Path
	0. Exit
	Enter choice: <user enter here>
Specific menu example (For loading and saving file)
	1. Specific
	2. Default
	0. Back
	Enter choice: <user enter here>
The default file path can be select like this
	1. Map\ValidMap1.txt
	2. Map\ValidMap2.txt
	3. Map\InvalidMap1.txt
	4. Map\InvalidMap2.txt
	5. Map\InvalidMap3.txt
	6. Map\InvalidMap4.txt
	7. Map\InvalidMap5.txt
	8. Map\ValidMapNoPath1.txt
	9. Map\ValidMapNoPath2.txt
	0. Cancel
	Select map: <user selection>


