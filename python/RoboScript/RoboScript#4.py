import re

def expand_patterns(code, pattern_dict, call_stack=None):
	if call_stack is None:
		call_stack = {}
	def replace_match(match):
		pid = int(match.group(1))
		if pid not in pattern_dict:
			raise Exception(f"Pattern {pid} not defined")
		call_stack[pid] = call_stack.get(pid, 0) + 1
		if call_stack[pid] > 2:
			raise Exception(f"Infinite recursion detected in pattern {pid}")
		expanded = expand_patterns(pattern_dict[pid], pattern_dict, call_stack)
		call_stack[pid] -= 1
		return expanded
	return re.sub( r'P(\d+)', replace_match, code)

def remove_patterns(code):
	pattern_regex  = r'p(\d+)(.*?)q'
	pattern_dict = {}
	for id, seq in re.findall(pattern_regex , code):
		id = int(id)
		if id in pattern_dict:
			raise Exception(f"Pattern {id} is defined more than once")
		pattern_dict[id] = seq
	return expand_patterns(re.sub(pattern_regex, '', code), pattern_dict)

def full_string(code):
	return re.sub(r'(.)\d+', lambda m: m[1] * int(m[0][1:]), code)

def find_group(code):
	i = code.rfind('(')
	if i == -1:
		return
	lvl = 1
	for j in range(i + 1, len(code)):
		if code[j] == '(':
			lvl += 1
		elif code[j] == ')':
			lvl -= 1
			if not lvl:
				return i, j

def RS2_decode(code):
	while '(' in code:
		i, j = find_group(code)
		k = j + 1
		while k < len(code) and code[k].isdigit():
			k += 1
		n = int(code[j+1:k] or 1)
		code = code[:i] + full_string(code[i+1:j]) * n + code[k:]
	return full_string(code)

def execute(code):
	if 'p' or 'P' in code:
		code = remove_patterns(code)
	code = RS2_decode(code)
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