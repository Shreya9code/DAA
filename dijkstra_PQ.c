#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX 100
#define INF 99999

// Priority Queue Node
typedef struct {
    int vertex;
    int dist;
} PQNode;

// Min Heap (Priority Queue)
typedef struct {
    PQNode* arr[MAX];
    int size;
} MinHeap;

int comparisonCount = 0;

// Utility to swap two nodes
void swap(PQNode** a, PQNode** b) {
    PQNode* temp = *a;
    *a = *b;
    *b = temp;
}

// Heapify up
void heapifyUp(MinHeap* heap, int idx) {
    while (idx > 0 && heap->arr[idx]->dist < heap->arr[(idx - 1) / 2]->dist) {
        comparisonCount++;
        swap(&heap->arr[idx], &heap->arr[(idx - 1) / 2]);
        idx = (idx - 1) / 2;
    }
}

// Heapify down
void heapifyDown(MinHeap* heap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < heap->size && heap->arr[left]->dist < heap->arr[smallest]->dist) {
        comparisonCount++;
        smallest = left;
    }
    if (right < heap->size && heap->arr[right]->dist < heap->arr[smallest]->dist) {
        comparisonCount++;
        smallest = right;
    }

    if (smallest != idx) {
        swap(&heap->arr[idx], &heap->arr[smallest]);
        heapifyDown(heap, smallest);
    }
}

// Create and push into priority queue
void push(MinHeap* heap, int v, int d) {
    PQNode* node = (PQNode*)malloc(sizeof(PQNode));
    node->vertex = v;
    node->dist = d;
    heap->arr[heap->size] = node;
    heapifyUp(heap, heap->size);
    heap->size++;
}

// Pop minimum from priority queue
PQNode* pop(MinHeap* heap) {
    if (heap->size == 0) return NULL;
    PQNode* root = heap->arr[0];
    heap->arr[0] = heap->arr[--heap->size];
    heapifyDown(heap, 0);
    return root;
}

// Dijkstra's Algorithm using priority queue
void dijkstra(int graph[MAX][MAX], int V, int src) {
    int dist[MAX], visited[MAX] = {0};

    for (int i = 0; i < V; i++) dist[i] = INF;
    dist[src] = 0;

    MinHeap* pq = (MinHeap*)malloc(sizeof(MinHeap));
    pq->size = 0;

    push(pq, src, 0);

    while (pq->size > 0) {
        PQNode* node = pop(pq);
        int u = node->vertex;
        free(node);

        if (visited[u]) continue;
        visited[u] = 1;

        for (int v = 0; v < V; v++) {
            comparisonCount++;
            if (!visited[v] && graph[u][v] != INF) {
                if (dist[u] + graph[u][v] < dist[v]) {
                    dist[v] = dist[u] + graph[u][v];
                    push(pq, v, dist[v]);
                }
            }
        }
    }

    printf("\nVertex\tDistance from Source\n");
    for (int i = 0; i < V; i++) {
        printf("%d\t%d\n", i, dist[i]);
    }

    printf("\nTotal comparisons: %d\n", comparisonCount);
}

// Main function to accept input
int main() {
    int V;
    int graph[MAX][MAX];

    printf("Enter number of vertices: ");
    scanf("%d", &V);

    printf("Enter adjacency matrix (use %d for INF):\n", INF);
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            scanf("%d", &graph[i][j]);
        }
    }

    int src;
    printf("Enter source vertex (0 to %d): ", V - 1);
    scanf("%d", &src);

    dijkstra(graph, V, src);

    return 0;
}
