import heapq

def uniform_cost_search(graph, start, goal):
    
    # Priority queue to store (cost, node, path)
    priority_queue = [(0, start, [start])]
    
    # Visited dictionary to store the minimum cost to reach each node
    visited = {}

    while priority_queue:
        # Pop the node with the lowest cost
        current_cost, current_node, path = heapq.heappop(priority_queue)

        # If the goal is reached, return the cost and path
        if current_node == goal:
            return current_cost, path

        # If the node is already visited with a lower cost, skip it
        if current_node in visited and visited[current_node] <= current_cost:
            continue

        # Mark the current node as visited with the current cost
        visited[current_node] = current_cost

        # Explore neighbors
        for neighbor, cost in graph.get(current_node, []):
            total_cost = current_cost + cost
            heapq.heappush(priority_queue, (total_cost, neighbor, path + [neighbor]))

    # If the goal is not reachable, return None
    return None

# Example usage
graph = {
    'A': [('B', 1), ('C', 4)],
    'B': [('C', 2), ('D', 5)],
    'C': [('D', 1)],
    'D': []
}

start_node = 'A'
goal_node = 'D'
result = uniform_cost_search(graph, start_node, goal_node)

if result:
    cost, path = result
    print(f"Optimal path: {path} with total cost: {cost}")
else:
    print("Goal not reachable from the start node.")
