import heapq
import math

def heuristic(a, b):
   
    return abs(a[0] - b[0]) + abs(a[1] - b[1])

def greedy_best_first_search(grid, start, goal):
    
    rows, cols = len(grid), len(grid[0])
    visited = set()
    priority_queue = []

    # Push the start node with its heuristic value
    heapq.heappush(priority_queue, (heuristic(start, goal), start))
    came_from = {}

    while priority_queue:
        _, current = heapq.heappop(priority_queue)

        if current in visited:
            continue

        visited.add(current)

        # Check if we reached the goal
        if current == goal:
            # Reconstruct the path
            path = []
            while current in came_from:
                path.append(current)
                current = came_from[current]
            path.append(start)
            return path[::-1]  # Reverse the path

        # Explore neighbors
        x, y = current
        for dx, dy in [(-1, 0), (1, 0), (0, -1), (0, 1)]:  # Up, Down, Left, Right
            neighbor = (x + dx, y + dy)
            if 0 <= neighbor[0] < rows and 0 <= neighbor[1] < cols:  # Check boundaries
                if grid[neighbor[0]][neighbor[1]] == 0 and neighbor not in visited:  # Free cell
                    heapq.heappush(priority_queue, (heuristic(neighbor, goal), neighbor))
                    came_from[neighbor] = current

    return None  # No path found

# Example grid (0 = free cell, 1 = obstacle)
grid = [
    [0, 1, 0, 0, 0],
    [0, 1, 0, 1, 0],
    [0, 0, 0, 1, 0],
    [0, 1, 1, 1, 0],
    [0, 0, 0, 0, 0]
]

start = (0, 0)  # Starting position
goal = (4, 4)  # Treasure position

path = greedy_best_first_search(grid, start, goal)

if path:
    print("Path to the treasure:", path)
else:
    print("No path found to the treasure.")