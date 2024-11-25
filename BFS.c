#include <stdio.h>
#include <stdlib.h>

struct queue
{
    int size;
    int front;
    int rear;
    int *Q;
};

void create(struct queue *q, int size)
{
    q->size = size;
    q->front = q->rear = -1;
    q->Q = (int *)malloc(q->size * sizeof(int));
}

void Enqueue(struct queue *q, int x)
{
    if (q->rear == q->size - 1)
    {
        printf("The queue is full\n");
    }
    else
    {
        q->rear++;
        q->Q[q->rear] = x;
    }
}

int Dequeue(struct queue *q)
{
    int x = -1;
    if (q->rear == q->front)
    {
        printf("The queue is empty\n");
    }
    else
    {
        q->front++;
        x = q->Q[q->front];
    }
    return x;
}

int isempty(struct queue *q)
{
    if (q->rear == q->front)
    {
        return 1;
    }
    else
        return 0;
}

void BFS(int **G, int start, int n)
{
    int i = start;
    int j;
    struct queue q;
    create(&q, n);
    int *visited = (int *)malloc(n * sizeof(int));

    // Initialize all vertices as unvisited
    for (int k = 0; k < n; k++)
    {
        visited[k] = 0;
    }

    printf("%d ", i);
    visited[i] = 1;
    Enqueue(&q, i);

    while (!isempty(&q))
    {
        i = Dequeue(&q);

        for (j = 0; j < n; j++)
        {
            if (G[i][j] == 1 && visited[j] == 0)
            {
                printf("%d ", j);
                visited[j] = 1;
                Enqueue(&q, j);
            }
        }
    }
    free(visited);
}

int main()
{
    int n, start_vertex;

    // Get number of vertices
    printf("Enter the number of vertices: ");
    scanf("%d", &n);

    // Allocate memory for the adjacency matrix
    int **G = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++)
    {
        G[i] = (int *)malloc(n * sizeof(int));
    }

    // Input the adjacency matrix
    printf("Enter the adjacency matrix:\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%d", &G[i][j]);
        }
    }

    // Get the start vertex for BFS
    printf("Enter the start vertex: ");
    scanf("%d", &start_vertex);

    // Perform BFS
    printf("BFS Traversal starting from vertex %d: ", start_vertex);
    BFS(G, start_vertex, n);
    printf("\n");

    // Free the memory allocated for the adjacency matrix
    for (int i = 0; i < n; i++)
    {
        free(G[i]);
    }
    free(G);

    return 0;
}
