import re

def print_map(grid):
	for row in grid:
		print('|', end='')
		print(''.join(row), end='')
		print('|')

def execute(code):
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

print(f"answer :\n{execute("LF5RF3RF3RF7")}")
expected = "    ****\r\n    *  *\r\n    *  *\r\n********\r\n    *   \r\n    *   "
print(f"expected :\n{expected}")
