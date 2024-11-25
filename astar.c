#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 100
#define INF 999

typedef struct {
    int adjMatrix[MAX][MAX];
    int num;
    int heuristic[MAX];  
} Graph;

// Function to get the node with the minimum f(n) value
int getMinCostNode(int f[], bool visited[], int num) {
    int min = INF;
    int minIndex = -1;
    for (int i = 0; i < num; i++) {
        if (!visited[i] && f[i] < min) {
            min = f[i];
            minIndex = i;
        }
    }
    return minIndex;
}

void aStarSearch(Graph *g, int start, int goal) {
    bool visited[MAX] = { false };
    int gCost[MAX];  // Actual cost from start to each node
    int fCost[MAX];  // Estimated total cost (f(n) = g(n) + h(n))
    int parent[MAX]; // For reconstructing the path
    
    for (int i = 0; i < g->num; i++) {
        gCost[i] = INF;
        fCost[i] = INF;
        parent[i] = -1;
    }

    gCost[start] = 0;  // g(start) = 0
    fCost[start] = g->heuristic[start];  // f(start) = h(start)

    printf("A* Search Traversal: ");

    while (true) {
        int current = getMinCostNode(fCost, visited, g->num);

        if (current == -1) {
            printf("\nGoal node %d not reachable.\n", goal);
            return;
        }

        printf("%d ", current);

        if (current == goal) {
            printf("\nGoal node %d reached.\n", goal);
            
            // Optionally, you can print the path from start to goal here.
            return;
        }

        visited[current] = true;

        for (int i = 0; i < g->num; i++) {
            if (g->adjMatrix[current][i] < INF && !visited[i]) {  // There's a valid edge between current and i
                int newCost = gCost[current] + g->adjMatrix[current][i];  // Actual cost to reach i
                if (newCost < gCost[i]) {
                    gCost[i] = newCost;
                    fCost[i] = newCost + g->heuristic[i];  // f(i) = g(i) + h(i)
                    parent[i] = current;
                }
            }
        }
    }
}

int main() {
    Graph g;
    int i, j, edges, v1, v2, weight, start, goal;

    printf("Enter the number of vertices: ");
    scanf("%d", &g.num);

    // Initialize adjacency matrix with INF to represent no edge between nodes
    for (i = 0; i < g.num; i++) {
        for (j = 0; j < g.num; j++) {
            g.adjMatrix[i][j] = INF;  
        }
    }

    printf("Enter the number of edges: ");
    scanf("%d", &edges);

    printf("Enter the edges with weights (v1 v2 weight):\n");
    for (i = 0; i < edges; i++) {
        scanf("%d %d %d", &v1, &v2, &weight);
        g.adjMatrix[v1][v2] = weight;  // Directed edge from v1 to v2 with given weight
    }

    printf("Enter heuristic values:\n");
    for (i = 0; i < g.num; i++) {
        printf("Heuristic value for vertex %d: ", i);
        scanf("%d", &g.heuristic[i]);
    }

    printf("Graph (Adjacency Matrix):\n");
    for (i = 0; i < g.num; i++) {
        for (j = 0; j < g.num; j++) {
            if (g.adjMatrix[i][j] == INF) {
                printf("INF ");
            } else {
                printf("%d ", g.adjMatrix[i][j]);
            }
        }
        printf("\n");
    }

    printf("Enter the start vertex: ");
    scanf("%d", &start);

    printf("Enter the goal vertex: ");
    scanf("%d", &goal);

    aStarSearch(&g, start, goal);

    return 0;
}