import re

def print_map(grid):
	for row in grid:
		print('|', end='')
		print(''.join(row), end='')
		print('|')

def execute(code):
	"""
		Execute a simplified RoboScript drawing code and return the resulting grid as a string.

		args:
			code: A string containing RoboScript commands:
				- 'F': move forward and draw a mark ('*')
				- 'L': turn left 90 degrees
				- 'R': turn right 90 degrees
				- Digits after a command indicate repetition (e.g., "F3" repeats 'F' 3 times)

		The function simulates movement on a 2D grid, expanding it as needed to accommodate
		the path. The initial position starts at the top-left of the grid.

		returns:
			A string representing the 2D grid with '*' marking the path, and spaces for empty cells.

		example:
			>>> execute("LF5RF3RF3RF7")
			"    ****\r\n    *  *\r\n    *  *\r\n********\r\n    *   \r\n    *   "
	"""
	code = re.sub(r'(.)\d+', lambda m: m[1] * int(m[0][1:]), code)
	grid = [['*']]
	x = y = 0
	d = 0
	dirs = [(1,0),(0,1),(-1,0),(0,-1)]
	for c in code:
		if c == 'L':
			d = (d - 1) % 4
		elif c == 'R':
			d = (d + 1) % 4
		else:
			dx, dy = dirs[d]
			x += dx
			y += dy
			if y < 0:
				grid.insert(0, [' '] * len(grid[0]))
				y = 0
			if y == len(grid):
				grid.append([' '] * len(grid[0]))
			if x < 0:
				for r in grid: r.insert(0, ' ')
				x = 0
			if x == len(grid[0]):
				for r in grid: r.append(' ')
			grid[y][x] = '*'
	return '\r\n'.join(''.join(r) for r in grid)

# print(f"answer :\n{execute("LF5RF3RF3RF7")}")
# expected = "    ****\r\n    *  *\r\n    *  *\r\n********\r\n    *   \r\n    *   "
# print(f"expected :\n{expected}")
