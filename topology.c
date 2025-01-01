#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// Queue structure
typedef struct Queue {
    int items[MAX];
    int front, rear;
} Queue;

// Graph structure
typedef struct Graph {
    int vertices;
    int adjMatrix[MAX][MAX];
} Graph;

// Function to initialize the queue
void initQueue(Queue* q) {
    q->front = -1;
    q->rear = -1;
}

// Function to check if the queue is empty
int isEmpty(Queue* q) {
    return q->front == -1;
}

// Function to enqueue an element
void enqueue(Queue* q, int value) {
    if (q->rear == MAX - 1) {
        printf("Queue Overflow\n");
    } else {
        if (q->front == -1) {
            q->front = 0;
        }
        q->rear++;
        q->items[q->rear] = value;
    }
}

// Function to dequeue an element
int dequeue(Queue* q) {
    if (isEmpty(q)) {
        printf("Queue Underflow\n");
        return -1;
    } else {
        int item = q->items[q->front];
        q->front++;
        if (q->front > q->rear) {
            q->front = q->rear = -1;
        }
        return item;
    }
}

// Function to create a graph
void createGraph(Graph* g, int vertices) {
    g->vertices = vertices;
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            g->adjMatrix[i][j] = 0;
        }
    }
}

// Function to add an edge in the graph
void addEdge(Graph* g, int u, int v) {
    g->adjMatrix[u][v] = 1;
}

// Function to perform topological sorting (Kahn's algorithm)
void topologicalSort(Graph* g) {
    int inDegree[MAX] = {0};
    Queue q;
    initQueue(&q);
    
    // Calculate in-degree (number of incoming edges for each vertex)
    for (int i = 0; i < g->vertices; i++) {
        for (int j = 0; j < g->vertices; j++) {
            if (g->adjMatrix[i][j] == 1) {
                inDegree[j]++;
            }
        }
    }
    
    // Enqueue all vertices with in-degree 0
    for (int i = 0; i < g->vertices; i++) {
        if (inDegree[i] == 0) {
            enqueue(&q, i);
        }
    }
    
    int count = 0;
    
    // Process vertices
    while (!isEmpty(&q)) {
        int u = dequeue(&q);
        printf("%d ", u);
        count++;
        
        // Reduce in-degree of neighboring vertices
        for (int v = 0; v < g->vertices; v++) {
            if (g->adjMatrix[u][v] == 1) {
                inDegree[v]--;
                if (inDegree[v] == 0) {
                    enqueue(&q, v);
                }
            }
        }
    }
    
    // If count does not match number of vertices, there is a cycle in the graph
    if (count != g->vertices) {
        printf("\nThere exists a cycle in the graph\n");
    }
}

// Main function
int main() {
    Graph g;
    int vertices, edges;
    int u, v;
    
    printf("Enter the number of vertices: ");
    scanf("%d", &vertices);
    
    createGraph(&g, vertices);
    
    printf("Enter the number of edges: ");
    scanf("%d", &edges);
    
    printf("Enter the edges (u v):\n");
    for (int i = 0; i < edges; i++) {
        scanf("%d %d", &u, &v);
        addEdge(&g, u, v);
    }
    
    printf("Topological Sorting: ");
    topologicalSort(&g);
    
    return 0;
}

