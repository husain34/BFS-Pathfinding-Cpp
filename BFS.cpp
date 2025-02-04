#include <iostream>
#include <map>
#include <list>
#include <deque>
#include <iomanip>
#include <sstream>
#include <limits>
#include <windows.h>
using namespace std;



// Class to represent a node in the grid
class Node {
    public:
    bool isExplored = false;  // Flag to check if node has been explored
    bool isBlock = false;     // Flag to check if node is an obstacle
    pair<int, int> cordinates; // Coordinates of the node
    Node* isconnected;        // Pointer to the connected node
};

// Function prototypes
void Obstacle();
pair<int, int> AddPair(pair<int, int> a, pair<int, int> b);
void Neighbours();
void BFS(pair<int, int> start, pair<int, int> end);
pair<int, int> FindCords(Node& Value);
void setColor(int color);

// Global variables for the grid, search frontier, and reached nodes
map<pair<int, int>, Node> grid;
deque<pair<int, int>> frontier;
map<pair<int, int>, Node> reached;
pair<int, int> currentNode;
int rows, cols;

int main() {
    cout << "BREATH FIRST SEARCH:" << endl;
    // Get grid dimensions from the user
    cout << "Enter the number of rows in the grid: ";
    cin >> rows;
    cout << "Enter the number of columns in the grid: ";
    cin >> cols;

    // Initialize start and end coordinates
    pair<int, int> start, end;
    pair<int, int> current;
    list<pair<int, int>> path;
    bool isPath;
    Node node[rows * cols];

    // Initialize the grid with nodes and their coordinates
    int count = 0;
    for (int i = 0; i < rows; i++) {
        cout << "|";
        for (int j = 0; j < cols; j++) {
            cout << setw(2) << i << "," << setw(2) << j << "|";
            grid[{i, j}] = node[count];
            grid[{i, j}].cordinates.first = i;
            grid[{i, j}].cordinates.second = j;
            count++;
        }
        cout << endl;
    }

    // Get obstacle coordinates from the user
    cout << "Enter obstacle coordinates as 'x1 y1 x2 y2 ...' (type 'done' to finish):\n";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    Obstacle();

    cout << endl;

    // Get start and end coordinates from the user
    cout << "Enter Start Coordinate:" << endl;
    cout << "Enter X coordinate: " << endl;
    cin >> start.first;
    cout << "Enter Y coordinate: " << endl;
    cin >> start.second;
    cout << endl;
    cout << "Enter End Coordinate:" << endl;
    cout << "Enter X coordinate: " << endl;
    cin >> end.first;
    cout << "Enter Y coordinate: " << endl;
    cin >> end.second;

    // Perform BFS to find the shortest path
    BFS(start, end);

    // Trace the path from end to start
    current = end;
    while (current != start) {
        current = FindCords(*grid[current].isconnected);
        if (current != start && current != end) {
            path.push_back(current);
        }
    }

    // Display the path
    count = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            for (pair<int, int> value : path) {
                if (value.first == i && value.second == j) {
                    isPath = true;
                }
            }
            if (isPath == true) {
                cout << setw(3) << "." << setw(3) << "|";
            } 
	    else if (grid[{i, j}].isBlock) {
                cout << "||||||";
            } 
	    else {
		if(grid[{i,j}].isExplored == true){
			setColor(4);
			cout << setw(2) << i << "," << setw(2) << j << "|";
			setColor(7);
		}
		else{
			cout << setw(2) << i << "," << setw(2) << j << "|";
		}
                
            }
            isPath = false;
        }
        cout << endl;
    }
system("pause");
    return 0;
}

void Obstacle(){
    string input;
    int x, y;
    getline(cin, input);
    stringstream ss(input);

    // Mark obstacles in the grid
    while (ss >> x >> y) {
        // Validate input
        if (x < 0 || x >= rows || y < 0 || y >= cols) {
            cout << "Invalid coordinate (" << x << "," << y << "), ignoring it.\n";
            continue;
        }
        grid[{x, y}].isBlock = true;
    }

    // Display grid with obstacles
        for (int i = 0; i < rows; i++) {
            cout << "|";
            for (int j = 0; j < cols; j++) {
                if (grid[{i, j}].isBlock == true) {
                    cout << "||||||";
                } else {
                    cout << setw(2) << i << "," << setw(2) << j << "|";
                }
            }
            cout << endl;
        }
}

void setColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

// Function to perform BFS to find the shortest path
void BFS(pair<int, int> start, pair<int, int> end) {
    frontier.push_back(start);

    // Loop until the goal is reached
    while (true) {
        currentNode = frontier.front();
        frontier.pop_front();
        Neighbours();

        if (currentNode == end) {
            break;
        }
    }
}

// Function to add two coordinate pairs together
pair<int, int> AddPair(pair<int, int> a, pair<int, int> b) {
    pair<int, int> c;
    c.first = a.first + b.first;
    c.second = a.second + b.second;
    return c;
}

// Function to explore the neighbors of the current node
void Neighbours() {
    pair<int, int> directions[] = {{1, 0}, {-1, 0}, {0, -1}, {0, 1}};
    list<pair<int, int>> neighbours;

    // Check all 4 possible directions for neighbors
    for (pair<int, int> Direction : directions) {
        pair<int, int> NeighbourCords = AddPair(currentNode, Direction);

        // If the neighbor is within bounds and not blocked, add it to the frontier
        if (grid.find(NeighbourCords) != grid.end() && 
            grid[NeighbourCords].isExplored == false && 
            grid[NeighbourCords].isBlock == false) {

            neighbours.push_back(NeighbourCords);
            grid[NeighbourCords].isExplored = true;
            grid[NeighbourCords].isconnected = &grid[currentNode];
        }
    }

    // Push neighbors to the frontier
    for (pair<int, int> Neighbour : neighbours) {
        frontier.push_back(Neighbour);
    }
}

// Function to find the coordinates of a node in the grid
pair<int, int> FindCords(Node& Value) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (grid[{i, j}].cordinates == Value.cordinates) {
                return {i, j};
            }
        }
    }
    return {-1, -1};  // Return invalid coordinates if not found
}
