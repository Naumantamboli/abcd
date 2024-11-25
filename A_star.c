#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include <math.h>

#define N 4

typedef struct
{
    int x, y;
    int f, g, h;
    bool closed;
    int parent_x, parent_y;
} Node;

// Euclidean distance calculation
int heuristic(Node *a, Node *b)
{
    return (int)(sqrt((a->x - b->x) * (a->x - b->x) + (a->y - b->y) * (a->y - b->y)));
}

bool isValid(int x, int y, int grid[N][N])
{
    return (x >= 0 && x < N && y >= 0 && y < N && grid[x][y] == 0);
}

void aStarSearch(int grid[N][N], Node start, Node goal)
{
    // Array to hold information for each cell
    Node nodes[N][N];
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            nodes[i][j].x = i;
            nodes[i][j].y = j;
            nodes[i][j].f = INT_MAX;
            nodes[i][j].g = INT_MAX;
            nodes[i][j].h = INT_MAX;
            nodes[i][j].closed = false; // Mark whether the cell has been visited or not
            nodes[i][j].parent_x = -1;
            nodes[i][j].parent_y = -1;
        }
    }

    // Initialize the start node
    int x = start.x, y = start.y;
    nodes[x][y].f = 0;
    nodes[x][y].g = 0;
    nodes[x][y].h = 0;
    nodes[x][y].parent_x = x;
    nodes[x][y].parent_y = y;

    while (true)
    {
        // Find the node with the smallest f value
        int minF = INT_MAX, current_x = -1, current_y = -1;
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                if (!nodes[i][j].closed && nodes[i][j].f < minF)
                {
                    minF = nodes[i][j].f;
                    current_x = i;
                    current_y = j;
                }
            }
        }

        // If the current node is the goal, we have found the path
        if (current_x == goal.x && current_y == goal.y)
        {
            printf("Path found!\n");
            while (current_x != start.x || current_y != start.y)
            {
                printf("(%d, %d) <- ", current_x, current_y);
                int temp_x = nodes[current_x][current_y].parent_x;
                current_y = nodes[current_x][current_y].parent_y;
                current_x = temp_x;
            }
            printf("(%d, %d)\n", start.x, start.y);
            return;
        }

        // Mark the current node as closed
        nodes[current_x][current_y].closed = true;

        // Possible moves (right, left, down, up)
        int dx[4] = {1, -1, 0, 0};
        int dy[4] = {0, 0, 1, -1};

        for (int i = 0; i < 4; i++)
        {
            int newX = current_x + dx[i];
            int newY = current_y + dy[i];

            // Check if the new cell is valid and not closed
            if (isValid(newX, newY, grid))
            {
                int newG = nodes[current_x][current_y].g + 1;
                int newH = heuristic(&nodes[newX][newY], &goal);
                int newF = newG + newH; // heuristic function

                // Update cell if a better path is found
                if (newF < nodes[newX][newY].f)
                {
                    nodes[newX][newY].f = newF;
                    nodes[newX][newY].g = newG;
                    nodes[newX][newY].h = newH;
                    nodes[newX][newY].parent_x = current_x;
                    nodes[newX][newY].parent_y = current_y;
                }
            }
        }
    }
}

int main()
{
    int grid[N][N];
    Node start, goal;

    // Input grid values from the user
    printf("Enter the grid (4x4) values (0 for open space, 1 for obstacle):\n");
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            scanf("%d", &grid[i][j]);
        }
    }

    // Input start and goal positions
    printf("Enter start position (x y): ");
    scanf("%d %d", &start.x, &start.y);

    printf("Enter goal position (x y): ");
    scanf("%d %d", &goal.x, &goal.y);

    // Perform A* search
    aStarSearch(grid, start, goal);

    return 0;
}
