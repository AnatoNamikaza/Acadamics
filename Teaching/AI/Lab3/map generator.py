import random

class Cell:
    def __init__(self, row, col):
        self.row = row
        self.col = col
        self.walls = {'top': True, 'right': True, 'bottom': True, 'left': True}
        self.visited = False

def generate_maze(rows, cols):
    maze = [[Cell(row, col) for col in range(cols)] for row in range(rows)]
    return maze

def remove_walls(maze, current_cell, next_cell):
    if current_cell.row == next_cell.row:
        if current_cell.col < next_cell.col:
            maze[current_cell.row][current_cell.col].walls['right'] = False
            maze[next_cell.row][next_cell.col].walls['left'] = False
        else:
            maze[current_cell.row][current_cell.col].walls['left'] = False
            maze[next_cell.row][next_cell.col].walls['right'] = False
    elif current_cell.col == next_cell.col:
        if current_cell.row < next_cell.row:
            maze[current_cell.row][current_cell.col].walls['bottom'] = False
            maze[next_cell.row][next_cell.col].walls['top'] = False
        else:
            maze[current_cell.row][current_cell.col].walls['top'] = False
            maze[next_cell.row][next_cell.col].walls['bottom'] = False

def get_neighbors(cell, rows, cols):
    neighbors = []
    if cell.row > 0:
        neighbors.append((cell.row - 1, cell.col))
    if cell.row < rows - 1:
        neighbors.append((cell.row + 1, cell.col))
    if cell.col > 0:
        neighbors.append((cell.row, cell.col - 1))
    if cell.col < cols - 1:
        neighbors.append((cell.row, cell.col + 1))
    return neighbors

def generate_binary_maze(rows, cols, num_walls_to_remove):
    maze = generate_maze(rows, cols)
    stack = []
    current_cell = maze[0][0]
    current_cell.visited = True
    while True:
        neighbors = get_neighbors(current_cell, rows, cols)
        unvisited_neighbors = [(r, c) for r, c in neighbors if not maze[r][c].visited]
        if unvisited_neighbors:
            next_row, next_col = random.choice(unvisited_neighbors)
            next_cell = maze[next_row][next_col]
            stack.append(current_cell)
            remove_walls(maze, current_cell, next_cell)
            next_cell.visited = True
            current_cell = next_cell
        elif stack:
            current_cell = stack.pop()
        else:
            break
    
    # Randomly remove walls
    for _ in range(num_walls_to_remove):
        row = random.randint(0, rows - 1)
        col = random.randint(0, cols - 1)
        direction = random.choice(['top', 'right', 'bottom', 'left'])
        maze[row][col].walls[direction] = False

    return maze

def print_maze_to_file(maze, filename):
    with open(filename, 'w') as f:
        for row in maze:
            for cell in row:
                if cell.walls['top']:
                    f.write("+---")
                else:
                    f.write("+   ")
            f.write("+\n")
            for cell in row:
                if cell.walls['left']:
                    f.write("|   ")
                else:
                    f.write("    ")
            f.write("|\n")
        for cell in maze[-1]:
            f.write("+---")
        f.write("+\n")

if __name__ == "__main__":
    rows = 20
    cols = 20
    num_walls_to_remove = 50
    maze_filename = "maze.txt"

    binary_maze = generate_binary_maze(rows, cols, num_walls_to_remove)
    print_maze_to_file(binary_maze, maze_filename)
    print("Maze saved to", maze_filename)