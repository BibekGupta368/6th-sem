#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define INF INT_MAX
#define MAX_NODES 100

// Function to find the vertex with the minimum distance value
int extractMin(int dist[], int visited[], int n) {
    int min = INF, min_index = -1;
    for (int v = 0; v < n; v++) {
        if (!visited[v] && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }
    return min_index;
}

// Dijkstra's algorithm for a graph represented using adjacency matrix
void dijkstra(int graph[MAX_NODES][MAX_NODES], int n, int src) {
    int dist[MAX_NODES];
    int prev[MAX_NODES];
    int visited[MAX_NODES] = {0};  // Array to track visited vertices

    // Initialize distances and previous nodes
    for (int i = 0; i < n; i++) {
        dist[i] = INF;
        prev[i] = -1;
    }
    dist[src] = 0;

    // Build min heap (implicitly managed in this code with extractMin)
    for (int count = 0; count < n - 1; count++) {
        int u = extractMin(dist, visited, n);
        visited[u] = 1;

        // Update dist value of the adjacent vertices of the picked vertex
        for (int v = 0; v < n; v++) {
            if (!visited[v] && graph[u][v] && dist[u] != INF && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
                prev[v] = u;
            }
        }
    }

    // Print the results
    printf("Vertex\tDistance from Source\tPath\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d ", i, dist[i], src);
        int path = i;
        while (prev[path] != -1) {
            printf("<- %d ", prev[path]);
            path = prev[path];
        }
        printf("\n");
    }
}

int main() {
    int n, e, src;
    printf("Enter the number of vertices: ");
    scanf("%d", &n);
    int graph[MAX_NODES][MAX_NODES] = {0};

    printf("Enter the number of edges: ");
    scanf("%d", &e);

    printf("Enter the edges and their weights (format: u v weight):\n");
    for (int i = 0; i < e; i++) {
        int u, v, weight;
        scanf("%d %d %d", &u, &v, &weight);
        graph[u][v] = weight;
        graph[v][u] = weight; // For undirected graph
    }

    printf("Enter the source vertex: ");
    scanf("%d", &src);

    dijkstra(graph, n, src);

    return 0;
}
