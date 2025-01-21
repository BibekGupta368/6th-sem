from datetime import date
#Implementation of DFS
def dfs(maze, start, end):
    rows, cols = len(maze), len(maze[0])
    stack = [(start, [start])]
    visited = set()
    visited.add(start)
    all_paths = []

    while stack:
        (x, y), path = stack.pop()

        # Check whether the end is reached
        if (x, y) == end:
            all_paths.append(path)
            continue

        # Explore the neighbors
        for dx, dy in [(-1, 0), (1, 0), (0, -1), (0, 1)]:
            nx, ny = x + dx, y + dy
            if 0 <= nx < rows and 0 <= ny < cols and maze[nx][ny] == 1 and (nx, ny) not in visited:
                visited.add((nx, ny))
                stack.append(((nx, ny), path + [(nx, ny)]))

    return all_paths if all_paths else "No path found"

# Example usage for DFS
maze = [
    [1, 0, 1, 1, 1],
    [1, 1, 0, 1, 0],
    [0, 1, 1, 1, 0],
    [1, 0, 0, 1, 1],
    [1, 1, 1, 0, 1],
]
start = (0, 0)
end = (4, 4)

print("DFS Paths:", dfs(maze, start, end))
print("-----------------------------------------------")
print("-----------------------------------------------")
print( "Name : Bibek Kumar Gupta \nRoll no: 22054031")
print("Date :" ,date.today())