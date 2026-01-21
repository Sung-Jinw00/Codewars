import re

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
    """
        Execute a nested RoboScript code string with group repetition and return the resulting grid.

        args:
            code: A string containing RoboScript commands with optional nested groups in parentheses,
                followed by an optional digit indicating repetition. Commands include:
                - 'F': move forward and draw a mark ('*')
                - 'L': turn left 90 degrees
                - 'R': turn right 90 degrees
                - Parentheses indicate grouping, e.g., "(F3R)2" repeats "F3R" twice

        The function decodes all nested groups, applies repetitions, then simulates movement
        on a 2D grid starting at the top-left corner. The grid expands dynamically to fit the path.

        returns:
            A string representing the 2D grid with '*' marking the path and spaces for empty cells.

        example:
            >>> execute("(L(F5(RF3))(((R(F3R)F7))))")
            "    ****\r\n    *  *\r\n    *  *\r\n********\r\n    *   \r\n    *   "
    """
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

# print("expected = LFFFFFRFFFRFFFRFFFFFFF")
# answer = execute("(L(F5(RF3))(((R(F3R)F7))))")
# print(f"answer :\n{answer}")
# # expected = "LFFFFFRFFFRFFFRRFFFRFFFFFFF"
# expected = "    ****\r\n    *  *\r\n    *  *\r\n********\r\n    *   \r\n    *   "
# print(f"expected :\n{expected}")
# print("meme input") if answer == expected else ''
