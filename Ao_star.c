#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

#define N 4

typedef struct {
    int x, y;         // Coordinates
    int h;            // Heuristic value
    bool solved;      // Whether this node is solved
    bool part_of_solution; // Whether it's part of the solution path
    int parent_x, parent_y;
} Node;

// Heuristic function (can use Manhattan distance or others as needed)
int heuristic(Node *a, Node *b) {
    return abs(a->x - b->x) + abs(a->y - b->y);  // Manhattan distance
}

// Check if a position is valid within the grid and not an obstacle
bool isValid(int x, int y, int grid[N][N]) {
    return (x >= 0 && x < N && y >= 0 && y < N && grid[x][y] == 0);
}

// Function to find minimum cost path using AO* algorithm
void aoStarSearch(int grid[N][N], Node start, Node goal) {
    // Initialize nodes for the grid
    Node nodes[N][N];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            nodes[i][j].x = i;
            nodes[i][j].y = j;
            nodes[i][j].h = heuristic(&nodes[i][j], &goal);
            nodes[i][j].solved = false;
            nodes[i][j].part_of_solution = false;
            nodes[i][j].parent_x = -1;
            nodes[i][j].parent_y = -1;
        }
    }

    int current_x = start.x, current_y = start.y;
    
    while (true) {
        // Mark the current node as solved and part of the solution path
        nodes[current_x][current_y].solved = true;
        nodes[current_x][current_y].part_of_solution = true;

        // If we reached the goal, stop
        if (current_x == goal.x && current_y == goal.y) {
            printf("Solution path found:\n");
            int x = goal.x, y = goal.y;
            while (x != start.x || y != start.y) {  
                printf("(%d, %d) <- ", x, y);
                int temp_x = nodes[x][y].parent_x;
                y = nodes[x][y].parent_y;
                x = temp_x;
            }
            printf("(%d, %d)\n", start.x, start.y);
            return;
        }

        // Check all possible moves (right, left, down, up)
        int dx[4] = {1, -1, 0, 0};
        int dy[4] = {0, 0, 1, -1};
        int min_h = INT_MAX, next_x = -1, next_y = -1;

        for (int i = 0; i < 4; i++) {
            int newX = current_x + dx[i];
            int newY = current_y + dy[i];

            // Check if the move is valid
            if (isValid(newX, newY, grid)) {
                if (nodes[newX][newY].h < min_h && !nodes[newX][newY].solved) {
                    min_h = nodes[newX][newY].h;
                    next_x = newX;
                    next_y = newY;
                }
            }
        }

        // If no valid next node, backtrack
        if (next_x == -1 || next_y == -1) {
            nodes[current_x][current_y].solved = false;
            nodes[current_x][current_y].part_of_solution = false;
            current_x = nodes[current_x][current_y].parent_x;
            current_y = nodes[current_x][current_y].parent_y;
        } else {
            nodes[next_x][next_y].parent_x = current_x;
            nodes[next_x][next_y].parent_y = current_y;
            current_x = next_x;
            current_y = next_y;
        }
    }
}

int main() {
    int grid[N][N];
    Node start, goal;

    // Input grid values from the user
    printf("Enter the grid (4x4) values (0 for open space, 1 for obstacle):\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &grid[i][j]);
        }
    }

    // Input start and goal positions
    printf("Enter start position (x y): ");
    scanf("%d %d", &start.x, &start.y);

    printf("Enter goal position (x y): ");
    scanf("%d %d", &goal.x, &goal.y);

    // Perform AO* search
    aoStarSearch(grid, start, goal);

    return 0;
}
