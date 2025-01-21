import networkx as nx
import matplotlib.pyplot as plt
from collections import deque

def bi_directional_bfs(graph, start, end):
    if start == end:
        return [start]

    # Initialize queues and visited sets for both directions
    queue_start = deque([start])
    queue_end = deque([end])
    visited_start = {start}
    visited_end = {end}
    parent_start = {start: None}
    parent_end = {end: None}

    while queue_start and queue_end:
        # Expand from the start side
        if queue_start:
            current_start = queue_start.popleft()
            for neighbor in graph[current_start]:
                if neighbor not in visited_start:
                    visited_start.add(neighbor)
                    parent_start[neighbor] = current_start
                    queue_start.append(neighbor)
                    if neighbor in visited_end:  # Meeting point found
                        return reconstruct_path(parent_start, parent_end, neighbor)

        # Expand from the end side
        if queue_end:
            current_end = queue_end.popleft()
            for neighbor in graph[current_end]:
                if neighbor not in visited_end:
                    visited_end.add(neighbor)
                    parent_end[neighbor] = current_end
                    queue_end.append(neighbor)
                    if neighbor in visited_start:  # Meeting point found
                        return reconstruct_path(parent_start, parent_end, neighbor)

    return "No path found"

def reconstruct_path(parent_start, parent_end, meeting_point):
    # Reconstruct path from the start to the meeting point
    path_start = []
    current = meeting_point
    while current is not None:
        path_start.append(current)
        current = parent_start[current]
    path_start.reverse()  # Reverse to get the correct order

    # Reconstruct path from the meeting point to the end
    path_end = []
    current = parent_end[meeting_point]
    while current is not None:
        path_end.append(current)
        current = parent_end[current]

    return path_start + path_end

# Create a smaller graph
def create_small_graph():
    G = nx.Graph()
    edges = [
        ('A', 'B'), ('A', 'C'), ('B', 'D'), ('C', 'D'),
        ('C', 'E'), ('D', 'F'), ('E', 'G'), ('F', 'G'),
        ('G', 'H'), ('H', 'I')
    ]
    G.add_edges_from(edges)
    return G

# Visualization function
def visualize_graph(graph, path=None):
    plt.figure(figsize=(10, 6))
    pos = nx.spring_layout(graph, seed=42)
    nx.draw(graph, pos, with_labels=True, node_color='lightblue', node_size=600, font_size=12)

    if path:
        path_edges = list(zip(path, path[1:]))
        nx.draw_networkx_edges(graph, pos, edgelist=path_edges, edge_color='orange', width=2)

    plt.title("Graph Visualization with Bi-Directional BFS Path Highlighted")
    plt.show()

if __name__ == "__main__":
    small_graph = create_small_graph()
    start_node = 'A'
    end_node = 'H'

    # Find the shortest path using Bi-Directional BFS
    shortest_path = bi_directional_bfs(small_graph, start_node, end_node)
    print(f"Shortest path from {start_node} to {end_node}: {shortest_path}")

    # Visualize the graph and the path
    visualize_graph(small_graph, shortest_path)
