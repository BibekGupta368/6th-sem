from collections import deque
from datetime import date

def bfs(maze, start, end):
    rows, cols = len(maze), len(maze[0])
    queue = deque([(start, [start])])
    visited = set()
    visited.add(start)

    while queue:
        (x, y), path = queue.popleft()

        if (x, y) == end:
            return path

    
        for dx, dy in [(-1, 0), (1, 0), (0, -1), (0, 1)]:
            nx, ny = x + dx, y + dy
            if 0 <= nx < rows and 0 <= ny < cols and maze[nx][ny] == 1 and (nx, ny) not in visited:
                visited.add((nx, ny))
                queue.append(((nx, ny), path + [(nx, ny)]))

    return "No path found"


maze = [
    [1, 0, 1, 1, 1],
    [1, 1, 0, 1, 0],
    [0, 1, 1, 1, 0],
    [1, 0, 0, 1, 1],
    [1, 1, 1, 0, 1],
]
start = (0, 0)
end = (3, 3)

print("BFS Path:", bfs(maze, start, end))
print("-----------------------------------------------")
print("-----------------------------------------------")
print( "Name : Bibek Kumar Gupta \nRoll no: 22054031")
print("Date :" ,date.today())