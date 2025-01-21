#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


#define MAX_NODES 100
#define INF INT_MAX

// Function to find the vertex with the minimum distance value, from the set of vertices not yet included in MST
int extractMin(int dist[], int visited[], int n) {
    int min = INF, min_index = -1;
    for (int v = 0; v < n; v++) {
        if (!visited[v] && dist[v] < min) {
            min = dist[v];
            min_index = v;
        }
    }
    return min_index;
 }
  // Function to print the constructed MST stored in parent[]
   void printMST(int prev[], int graph[MAX_NODES][MAX_NODES], int n)
   {
         printf("Edge \tWeight\n");
        for (int i = 1; i < n; i++) {
           printf("%d - %d \t%d \n", prev[i], i, graph[i][prev[i]]);
        }
    }

// Function implementing Prim's algorithm as described in the notes
void primMST(int graph[MAX_NODES][MAX_NODES], int n, int src) {
    int dist[MAX_NODES];     // Stores the minimum weight to reach each node
    int prev[MAX_NODES];   // Stores the MST structure
    int visited[MAX_NODES]={0}; // Marks nodes included in the MST

    // Step 1: Initialize distances, parent array, and visited status
    for (int i = 0; i < n; i++) {
        dist[i] = INF;
        prev[i] = -1;
        visited[i] = 0;
    }
    
    // Set the distance of the source node to 0
    dist[src] = 0;

    // Step 2: Loop to construct the MST
    for (int count = 0; count < n - 1; count++) {
        // Step 3: Find the vertex with the minimum distance that is not yet included in MST
        int u = extractMin(dist, visited, n);
        visited[u] = 1;

        // Step 4: Update the distances of adjacent vertices
        for (int v = 0; v < n; v++) {
            // Only consider vertices not yet in MST and with a smaller edge cost than current dist[v]
            if (graph[u][v] && !visited[v] && graph[u][v] < dist[v]) {
                dist[v] = graph[u][v];
                prev[v] = u;  // Update parent to include edge in MST
            }
        }
    }

    // Step 6: Print the MST
     printMST(prev, graph, n);
  
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

    primMST(graph, n, src);

    return 0;
}
