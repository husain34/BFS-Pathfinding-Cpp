Breadth-First Search (BFS) Pathfinding in C++
🚀 A C++ implementation of the Breadth-First Search (BFS) algorithm for pathfinding in a grid-based environment.
This program finds the shortest path from a start to an end position while avoiding obstacles. It visualizes the path using a simple console grid.

📌 Features
✅ Grid Representation using std::map<pair<int, int>, Node>
✅ Obstacle Handling to block certain paths
✅ Shortest Path Finding using BFS (Optimal for Unweighted Graphs)
✅ Backtracking to reconstruct the path
✅ Console Grid Visualization with obstacles and path markers

🔧 How It Works
The user defines the grid size (rows & columns).
Obstacles (||||||) can be placed at specific coordinates.
The program takes start and end coordinates.
BFS Algorithm finds the shortest path.
The grid is printed with the path (.) from start to end, while obstacles are shown as ||||||.

Example Output
Enter the number of rows in the grid: 5
Enter the number of columns in the grid: 5

Enter obstacle coordinates as 'x1 y1 x2 y2 ...' (type 'done' to finish):
1 1 2 2 done

Enter Start Coordinate:
Enter X coordinate: 0
Enter Y coordinate: 0

Enter End Coordinate:
Enter X coordinate: 4
Enter Y coordinate: 4

Grid with Path:
 0, 0| 0, 1| 0, 2| 0, 3| 0, 4|
  .  ||||||| 1, 2| 1, 3| 1, 4|
  .  | 2, 1||||||| 2, 3| 2, 4|
  .  | 3, 1| 3, 2| 3, 3| 3, 4|
  .  |  .  |  .  |  .  | 4, 4|
🔹 "." represents the shortest path.
🔹 "||||||" represents obstacles.

🏗 Future Improvements
🏆 Add support for diagonal movement
📌 Implement Dijkstra’s Algorithm for weighted graphs
🎨 GUI version using SFML or SDL
🤝 Contributing
Feel free to fork, improve, or optimize the project. Contributions are welcome!

