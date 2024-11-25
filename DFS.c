#include <stdio.h>
#include <stdlib.h>

struct stack {
    int size;
    int top;
    int *S;
};

void createStack(struct stack *st, int size) {
    st->size = size;
    st->top = -1;
    st->S = (int *)malloc(st->size * sizeof(int));
}

void push(struct stack *st, int x) {
    if (st->top == st->size - 1) {
        printf("Stack Overflow\n");
    } else {
        st->top++;
        st->S[st->top] = x;
    }
}

int pop(struct stack *st) {
    int x = -1;
    if (st->top == -1) {
        printf("Stack Underflow\n");
    } else {
        x = st->S[st->top];
        st->top--;
    }
    return x;
}

int isEmpty(struct stack *st) {
    return st->top == -1;
}

void DFS(int **G, int start, int destination, int n) {
    struct stack st;
    createStack(&st, n);

    int visited[n];
    for (int i = 0; i < n; i++) {
        visited[i] = 0;
    }

    push(&st, start);
    while (!isEmpty(&st)) {
        int i = pop(&st);
        if (visited[i] == 0) {
            printf("%d ", i);
            visited[i] = 1;

            // Stop traversal if destination vertex is reached
            if (i == destination) {
                printf("\nDestination vertex %d reached.\n", destination);
                free(st.S);
                return;
            }

            for (int j = n - 1; j >= 0; j--) {
                if (G[i][j] == 1 && visited[j] == 0) {
                    push(&st, j);
                }
            }
        }
    }

    free(st.S);
}

int main() {
    int n, source, destination;

    printf("Enter the number of vertices: ");
    scanf("%d", &n);

    int **G = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        G[i] = (int *)malloc(n * sizeof(int));
    }

    printf("Enter the adjacency matrix (1 for edge, 0 for no edge):\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &G[i][j]);
        }
    }

    printf("Enter the source vertex: ");
    scanf("%d", &source);

    printf("Enter the destination vertex: ");
    scanf("%d", &destination);

    printf("DFS Traversal: ");
    DFS(G, source, destination, n);

    for (int i = 0; i < n; i++) {
        free(G[i]);
    }
    free(G);

    return 0;
}
