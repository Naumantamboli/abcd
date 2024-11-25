#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 100

typedef struct {
    int adjMatrix[MAX][MAX];
    int num;
    int heuristic[MAX];
} Graph;

int getMin(int heuristics[], bool visited[], int num, int current, Graph *g) {
    int min = 10000;
    int minIndex = -1;
    for (int i = 0; i < num; i++) {
        if (!visited[i] && heuristics[i] < min && g->adjMatrix[current][i] == 1) {
            min = heuristics[i];
            minIndex = i;
        }
    }
    return minIndex;
}

void bestFirstSearch(Graph *g, int start, int goal) {
    bool visited[MAX] = { false };
    int current = start;
    visited[start] = true;

    printf("Best-First Search Traversal: ");

    while (current != -1) {
        printf("%d ", current);

        if (current == goal) {
            printf("\nGoal node %d reached.\n", goal);
            return;
        }

        int next = getMin(g->heuristic, visited, g->num, current, g);

        if (next == -1) {
            printf("\nGoal node %d not reachable.\n", goal);
            return;
        }

        visited[next] = true;
        current = next;
    }
}

void displayGraph(Graph *g) {
    printf("\nGraph Representation:\n\n");
    for (int i = 0; i < g->num; i++) {
        printf("Vertex %d (H=%d) is connected to: ", i, g->heuristic[i]);
        for (int j = 0; j < g->num; j++) {
            if (g->adjMatrix[i][j] == 1) {
                printf("%d ", j);
            }
        }
        printf("\n");
    }
}

int main() {
    Graph g;
    int i, j, edges, v1, v2, start, goal;

    printf("Enter the number of vertices: ");
    scanf("%d", &g.num);

    // Initialize the adjacency matrix
    for (i = 0; i < g.num; i++) {
        for (j = 0; j < g.num; j++) {
            g.adjMatrix[i][j] = 0;
        }
    }

    // Get the edges of the graph
    printf("Enter the number of edges: ");
    scanf("%d", &edges);

    printf("Enter the edges (v1 v2):\n");
    for (i = 0; i < edges; i++) {
        scanf("%d %d", &v1, &v2);
        g.adjMatrix[v1][v2] = 1;
        g.adjMatrix[v2][v1] = 1;
    }

    // Get the heuristic values for each vertex
    printf("Enter heuristic values:\n");
    for (i = 0; i < g.num; i++) {
        printf("Heuristic value for vertex %d: ", i);
        scanf("%d", &g.heuristic[i]);
    }

    // Display the graph in text format
    displayGraph(&g);

    // Get the start and goal vertices
    printf("\nEnter the start vertex: ");
    scanf("%d", &start);

    printf("Enter the goal vertex: ");
    scanf("%d", &goal);

    // Perform Best-First Search
    bestFirstSearch(&g, start, goal);

    return 0;
}
