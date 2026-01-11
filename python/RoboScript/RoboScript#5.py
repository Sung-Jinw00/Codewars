import re
GREEN = "\033[32m"
RED   = "\033[31m"
RESET = "\033[0m"

def expand_patterns(code, pattern_dict, call_stack=None):
	if call_stack is None:
		print(f"code = {code}, pattern_dict = {pattern_dict}")
		call_stack = {}
	def replace_match(match):
		pid = match.group(1)
		if pid not in pattern_dict:
			raise Exception(f"Pattern {pid} not defined")
		call_stack[pid] = call_stack.get(pid, 0) + 1
		if call_stack[pid] > 10:
			raise Exception(f"Infinite recursion detected in pattern {pid}")
		expanded = expand_patterns(pattern_dict[pid], pattern_dict, call_stack)
		call_stack[pid] -= 1
		return expanded
	return re.sub( r'P(\d+)', replace_match, code)

def remove_useless_parenthesis(code):
	# find empty parenthesis
	empty = code.find('()')
	while empty != -1:
		start = empty
		end = start + 1
		n = len(code)
		# get wider empty parenthesis if things like "(...()...)" exist
		while (		start - 1 >= 0 and code[start - 1] == '('
				and end + 1 < n and code[end + 1] == ')'):
			start -= 1
			end += 1
		# get n from (...)n too
		while end + 1 < n and code[end + 1].isdigit():
			end += 1
		# remove empty parenthesis
		code = code[:start] + code[end + 1:]
		# until no more
		empty = code.find('()')
	return code

def check_unmatched_parenthesis(code):
	lvl = 0
	for c in code:
		if c == '(':
			lvl += 1
		elif c == ')':
			lvl -= 1
			if lvl < 0:
				raise Exception("Unmatched closing parenthesis")
	if lvl != 0:
		raise Exception("Unmatched opening parenthesis")

def build_patterns(code, outer_patterns=None):
	if outer_patterns is None:
		outer_patterns = {}
	i = 0
	n = len(code)
	local_patterns = {}
	clean_code = ''
	while i < n:
		if code[i] == 'p':
			j = i + 1
			while j < n and code[j].isdigit():
				j += 1
			pid = code[i+1:j]
			lvl = 1
			start_content = j
			while j < n and lvl > 0:
				if code[j] == 'p' and j+1 < n and code[j+1].isdigit():
					lvl += 1
				elif code[j] == 'q':
					lvl -= 1
				j += 1
			content = code[start_content:j-1]
			if pid in local_patterns:
				raise Exception(f"Pattern {pid} redefined in the same scope")
			clean_content, nested_patterns = build_patterns(content, {**outer_patterns, **local_patterns})
			print(f"clear content = {clean_content}, content = {content}, nested_patterns = {nested_patterns}")
			if f'P{pid}' in content:
				clean_content = re.sub(r'p' + pid + r'.*?q', '', content)
				print(f"clean content = {clean_content}")
				clean_content = re.sub( r'P' + pid, nested_patterns[pid], clean_content)
				print(f"clean content = {clean_content}")
			local_patterns.update(nested_patterns)
			local_patterns[pid] = clean_content
			i = j
		else:
			clean_code += code[i]
			i += 1
	nested_patterns = {**outer_patterns, **local_patterns}
	return clean_code, nested_patterns

def remove_patterns(code):
	pattern_calls = re.findall(r'P(\d+)', code)
	pattern_defs  = re.findall(r'p(\d+)', code)
	# no non-existent pattern should be invoked
	for pid in pattern_calls:
		if pid not in pattern_defs:
			raise Exception(f"Pattern {pid} called but not defined")
	def replace_pattern(match):
		pid = match.group(1)
		content = match.group(2)
		# removing empty patterns and not used patterns
		if content.strip() == '' or pid not in pattern_calls:
			return ''
		return match.group(0)
	pattern_regex = re.compile(r'p(\d+)(.*?)q')
	code = pattern_regex.sub(replace_pattern, code)
	# unmached parenthesis not allowed
	check_unmatched_parenthesis(code)
	# build toutes les patterns et les execute
	print(f"code = {code}")
	return expand_patterns(*build_patterns(code))

def full_string(code):
	return re.sub(r'(.)\d+', lambda m: m[1] * int(m[0][1:]), code)

def find_last_brackets(code):
	i = code.rfind('(')
	if i == -1:
		return None, None
	lvl = 1
	for j in range(i + 1, len(code)):
		if code[j] == '(':
			lvl += 1
		elif code[j] == ')':
			lvl -= 1
			if not lvl:
				return i, j
	return None, None

def RS2_decode(code):
	while '(' in code:
		i, j = find_last_brackets(code)
		if i == None:
			break
		k = j + 1
		while k < len(code) and code[k].isdigit():
			k += 1
		n = int(code[j+1:k] or 1)
		code = code[:i] + full_string(code[i+1:j]) * n + code[k:]
	return full_string(code)

class RSUProgram:
	def __init__(self, source: str):
		self.source = source
	
	def execute_raw(self, raw_cmd):
		code = ''.join(raw_cmd)
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

	# accepts 1 argument : tokens (array of tokens)
	def convert_to_raw(self, tokens):
		code = ''.join(tokens)
		i = len(code)
		while i > 0:
			i, j = find_last_brackets(code[:i])
			if i == None:
				break
			# removing (...)0
			if j + 1 < len(code) and code[j + 1] == '0':
				code = code[:i] + code[j + 2:]
			# verifying if pattern not declared in bracketed sequence
			elif 'p' in code[i + 1:j]:
				raise Exception("Pattern definitions cannot be nested inside bracketed sequences")
		# Empty bracketed repeat sequences is accepted, but useless so i remove them
		code = remove_useless_parenthesis(code)
		# removing patterns and managing pattern errors
		if 'p' in code or 'P' in code:
			raw = remove_patterns(code)
		# making raw code with F, L, R only
		raw = ''.join(c for c in RS2_decode(raw))
		print(f"raw = {raw}")
		# raw should contain F, L, R only
		if any(c not in "FLR" for c in raw):
			raise Exception('Raw command doesn\'t contains F, L and R only')
		# returns an array of raw commands from processing the tokens
		return list(raw)

	# accepts no arguments
	def get_tokens(self):
		# print(f"------ source :\n{self.source}\n")
		code = self.source
		n = len(code)
		i = 0
		# returns the tokens present in source in order as an array
		tokens = []
		while i < n:
			if code[i] in "FLRPp)":
				start = i
				i += 1
				while i < n and code[i].isdigit():
					i += 1
				str_int = code[start + 1:i]
				# invalid pattern declaration
				if code[start] in 'pP' and not str_int:
					raise Exception("pattern declaration without an identifier")
				# leading zeroes
				elif len(str_int) > 1 and str_int[0] == '0':
					raise Exception("integer postfixes with leading zeroes")
				# add valid token (F, L, R, Fn, Ln, Rn, ')', ')n', pn, Pn)
				tokens.append(code[start:i])
			elif code[i:i + 2] == '/*':
				i += 2
				# ignore double comment
				while i + 2 < n and code[i:i + 2] != '*/':
					# nested double comment
					if code[i:i + 2] == '/*':
						raise Exception("Nested double comment")
					i += 1
				# wrong double comments
				if i == n or (i + 2 < n and code[i:i + 2] != '*/'):
					raise Exception("Wrong comment")
				# ignore double comment
				i += 2
				# invalid token
				if i < n and code[i].isdigit():
					raise Exception("Comment within token")
			elif code[i:i + 2] == '//':
				i+= 2
				# ignore single comment
				while i < n and code[i] != '\n':
					i += 1
				# invalid token/wrong comment
				if i + 1 < n and code[i] == '\n' and code[i + 1].isdigit():
					raise Exception("Comment within token")
			elif code[i] == 'q' or code[i] == '(' or code[i].isspace():
				# ignore all whitespace, add valid token (q, '(')
				if not code[i].isspace():
					tokens.append(code[i])
				i += 1
			# number alone (also used for n after skipping whitespaces from 'F   n' expressions)
			elif code[i].isdigit():
				raise Exception("Stray number")
			# illegal character (negative number falls in this after exiting the first if because of '-')
			else:
				raise Exception(f"Illegal character : {code[i]}")
		return tokens
	
	def execute(self):
		return self.execute_raw(self.convert_to_raw(self.get_tokens()))

fail_on = """p1p1FRqF2P1q(F2P1)4"""
program = RSUProgram(fail_on)
tokens = program.get_tokens()
raw = program.convert_to_raw(tokens)
print(f"raw :\n{raw}")
expected = raw
if raw == expected:
	print("Congratulations ! it works as expected 🎉")
else:
	print("Wrong ❌")

	# longueur minimale comparable
	min_len = min(len(raw), len(expected))

	# trouver le premier index différent
	diff_index = None
	for i in range(min_len):
		if raw[i] != expected[i]:
			diff_index = i
			break

	if diff_index is None:
		print("Difference only in length")
		print(f"Expected length: {len(expected)}")
		print(f"Raw length     : {len(raw)}")
	else:
		context = 20  # nombre de caractères autour
		start = max(0, diff_index - context)
		end = diff_index + context

		print(f"First difference at index {diff_index}")
		print(f"Expected [{start}:{end}]: {expected[start:end]}")
		print(f"Raw      [{start}:{end}]: {raw[start:end]}")

	print(f"Total length difference: {len(raw) - len(expected)}")

exec = program.execute_raw(raw)
print(exec)
expected = program.execute_raw(expected)
if exec == expected:
	print("Congratulations ! it works as expected")
else:
	print(f"Wrong !\nexpecting :\n{expected}")

# print("-" * 20)
# exec = program.execute()
# print(exec)
# expected = exec
# if exec == expected:
# 	print("Congratulations ! it works as expected")
# else:
# 	print(f"Wrong !\nexpecting :\n{expected}")