#include <stdio.h>
#define INF 99999
#define MAX 100

int dijkstra(int graph[MAX][MAX], int n, int src, int *comparisonCount) {
    int dist[MAX], visited[MAX];
    for (int i = 0; i < n; i++) {
        dist[i] = INF;
        visited[i] = 0;
    }

    dist[src] = 0;

    for (int count = 0; count < n - 1; count++) {
        // Find the minimum distance node from the unvisited set
        int min = INF, u = -1;
        for (int v = 0; v < n; v++) {
            (*comparisonCount)++;
            if (!visited[v] && dist[v] <= min) {
                min = dist[v];
                u = v;
            }
        }

        visited[u] = 1;

        // Update distances of adjacent vertices
        for (int v = 0; v < n; v++) {
            (*comparisonCount)++;
            if (!visited[v] && graph[u][v] && dist[u] != INF &&
                dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    // Print result
    printf("Vertex\tDistance from Source\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\n", i, dist[i]);
    }

    return 0;
}

int main() {
    int n, src;
    int graph[MAX][MAX];
    int comparisonCount = 0;

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    printf("Enter adjacency matrix (0 if no edge):\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &graph[i][j]);
        }
    }

    printf("Enter source vertex: ");
    scanf("%d", &src);

    dijkstra(graph, n, src, &comparisonCount);

    printf("\nTotal number of comparisons: %d\n", comparisonCount);

    return 0;
}
