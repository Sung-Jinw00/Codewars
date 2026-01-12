import re
BLUE  = "\033[36m"
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

def check_unmatched_parenthesis_and_patterns(code):
	lvl_pat = lvl_par = 0
	for c in code:
		if c == '(':
			lvl_par += 1
		elif c == 'p':
			lvl_pat += 1
		elif c == ')':
			lvl_par -= 1
			if lvl_par < 0:
				raise Exception("Unmatched closing parenthesis")
		elif c == 'q':
			lvl_pat -= 1
			if lvl_pat < 0:
				raise Exception("Unmatched closing pattern")
	if lvl_par != 0:
		raise Exception("Unmatched opening parenthesis")
	elif lvl_pat != 0:
		raise Exception("Unmatched opening pattern")

def print_content(content, v):
	print(content, end='')
	i = 0
	lvl = 0
	while i < len(v):
		if v[i] == 'p':
			print(f"\n{'\t' * lvl}{GREEN}{v[i]}{RESET}", end='')
			lvl += 1
			i += 1
			while i < len(v) and v[i].isdigit():
				print(f"{GREEN}{v[i]}{RESET}", end='')
				i += 1
			print('(\n', '\t' * lvl, end='')
		elif v[i] == 'P':
			print(f"{BLUE}{v[i]}{RESET}", end='')
			i += 1
			while i < len(v) and v[i].isdigit():
				print(f"{BLUE}{v[i]}{RESET}", end='')
				i += 1
		elif v[i] == 'q':
			lvl -= 1
			print(f"\n{'\t' * lvl}{RED}{v[i]}{RESET})", end='')
			i += 1
		else:
			print(v[i], end='')
			i += 1
	print('\n')

def print_dict(content, d):
	print(content)
	i = 0
	if not d:
		print(f"{RED}Empty dictionnary.{RESET}")
		return
	for pid, content in d.items():
		print(f"{GREEN}p{pid}{RESET} = ", end='')
		print_content('', content)

def build_patterns(code, outer_patterns=None, scope_lvl=1):
	# if patterns have been declared before and got called in a deeper scope
	if outer_patterns is None:
		outer_patterns = {}
	i = 0
	n = len(code)
	# current patterns find in the scope
	local_patterns = {}
	clean_code = ''
	while i < n:
		# get all the pattern declarations at current scope level
		if code[i] == 'p':
			j = i + 1
			while j < n and code[j].isdigit():
				j += 1
			pid = code[i+1:j]
			# don't miss the closing level of pattern
			lvl = 1
			start_content = j
			while j < n and lvl > 0:
				if code[j] == 'p':
					lvl += 1
				elif code[j] == 'q':
					lvl -= 1
				j += 1
			# preparing for the next pattern in the same scope
			i = j
			# get the content in between
			content = code[start_content:j-1]
			print_content(f"content in p{pid} = ", content)
			# Pattern redefinition in the same scope is not allowed and should throw an error
			if pid in local_patterns:
				raise Exception(f"Pattern {pid} redefined in the same scope")
			# if pattern declarations in a pattern declaration content, build patterns in the scope, remove local patterns further
			if content.find('p') != -1:
				print(f'{'-' * 20} go in scope {scope_lvl} {'-' * 20}')
				# get the pattern's clean content only, pattern declarations can only be used in their local scope or if they're from parent scopes
				content, _ = build_patterns(content, {**outer_patterns, **local_patterns}, scope_lvl + 1)
				print(f'{'-' * 20} back from scope {scope_lvl} {'-' * 20}')
				print_content(f"local_patterns[{pid}] (previous scope) = ", content)
				# new clear content associate with pid
				local_patterns[pid] = content
				print_dict(f"local_patterns :", local_patterns)
			# removing remaining matching patterns with our local definitions 
			for pattern in local_patterns:
				pos = content.rfind(f'P{pattern}')
				end = pos + 1 + len(pattern)
				if pos != -1 and (end >= len(content) or not content[end].isdigit()):
					print_content("", f"P{pattern} in {content}")
					# clean_content = re.sub(r'p' + pattern + r'.*?q', '', content)
					# print_content("clean content = ", clean_content)
					content = re.sub( r'P' + pattern, local_patterns[pattern], content)
					print_content("clean content = ", content)
			print_content(f"local_patterns[{pid}] = ", content)
			# giving the cleanest pid declaration so far
			local_patterns[pid] = content
			print_content("remaining code = ", code[i:])
			print_dict(f"actual patterns definitions :", local_patterns)
		else:
			# gathering clean code without declaractions in the current scope
			clean_code += code[i]
			i += 1
	# fusing outer patterns with patterns in current scope
	nested_patterns = {**outer_patterns, **local_patterns}
	# final check of pattern calls on the clean code
	for pattern in nested_patterns:
		pos = clean_code.rfind(f'P{pattern}')
		end = pos + 1 + len(pattern)
		if pos != -1 and (end >= len(clean_code) or not clean_code[end].isdigit()):
			print_content("", f"P{pattern} in {clean_code}")
			# clean_content = re.sub(r'p' + pattern + r'.*?q', '', content)
			# print_content("clean content = ", clean_content)
			clean_code = re.sub( r'P' + pattern, nested_patterns[pattern], clean_code)
			print_content('clean code = ', clean_code)
	if scope_lvl == 1:
		print_content("final clean_code = ", clean_code)
	print_dict("nested_patterns : ", nested_patterns)
	# return the cleanest code we can give so far
	return clean_code, nested_patterns

def clear_empty_patterns(code):
	i = 0
	n = len(code)
	lvl = 0
	while i < n:
		if code[i] == 'p':
			lvl += 1
			s = i
			i += 1
			curr_lvl = lvl
			while lvl >= curr_lvl:
				if code[i] == 'P':
					break
				elif code[i] == 'p':
					lvl += 1
				elif code[i] == 'q':
					lvl -= 1
				i += 1
			if lvl < curr_lvl:
				code = code[:s] + code[i:]
		elif code[i] == 'q':
			lvl -= 1
		i += 1
	return code
			

def remove_patterns(code):
	# unmached parenthesis not allowed
	check_unmatched_parenthesis_and_patterns(code)
	#code = clear_empty_patterns(code)
	pattern_calls = re.findall(r'P(\d+)', code)
	pattern_defs  = re.findall(r'p(\d+)', code)
	unused_patterns = set(pattern_defs) - set(pattern_calls)
	for pid in unused_patterns:
		p_pos = code.rfind(f'p{pid}')
		while p_pos != -1:
			if not code[p_pos + 1 + len(pid)].isdigit():
				end_p = p_pos + 1
				lvl = 1
				while end_p < len(code) and lvl > 0:
					if code[end_p] == 'p':
						lvl += 1
					elif code[end_p] == 'q':
						lvl -= 1
					end_p += 1
				code = code[:p_pos] + code[end_p:]
			remaining = code[:p_pos]
			p_pos = remaining.rfind(f'p{pid}')
	pattern_calls = re.findall(r'P(\d+)', code)
	# no non-existent pattern should be invoked
	for pid in pattern_calls:
		if pid not in pattern_defs:
			raise Exception(f"Pattern {pid} called but not defined")
	# build toutes les patterns et les execute
	print_content("code = ", code)
	if code.find('p') == -1:
		return code
	return expand_patterns(*build_patterns(code))

def full_string(code):
	return re.sub(r'(.)\d+', lambda m: m[1] * int(m[0][1:]), code)

def find_last_brackets(code, last=-10):
	if last == -10:
		last = len(code)
	i = code[:last].rfind('(')
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
	i = len(code)
	while '(' in code:
		print("i = ", i)
		i, j = find_last_brackets(code, i)
		if i == None:
			break
		k = j + 1
		while k < len(code) and code[k].isdigit():
			k += 1
		n = int(code[j+1:k] or 1)
		print("code in parenthesis : ", code[i+1:j])
		code = code[:i] + code[i+1:j] * n + code[k:]
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
			i, j = find_last_brackets(code, i)
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
		print_content("code = ", code)
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
	
# -----------------------------------------------------------------------------------------------------------------

fail_on = """LLF8LR5P441LR4LR1R5RP345L4RP441L5(F0)p9LFL2RL8p868L(R)L6LLp382Rqp7RLF5R0FRF9qLF6LRqp9(()7)RL3RL0p9RRF()1qqqp441FL3p834p25p834qLFP6L()R5qFLp25FF4qF6RR3L8P915Lp915RL1F6FR4RqqR4p25FFLF7RR5(L4RL8F5)F4LF7R9qqp6p6L4FR4LP441p693()LP345P345LFL6R4P6LF1()3FRFFF6LL0qqqRP6R7(LP441F5R7)F6L(R)9p345(L)3R3qp392LF1F9FP441R9RL7p345LL4F0L2Rp712FFRFR0R0qp104P9FL5qqp392F(RP9L)R6p6p9qP441L9R()5FP441P392R4R7F2qR9RR5RP9qF5F4L5P441P345qRP392F8L3F(R)R2RP345RF5(F6F3)LP345RL(L5F6(LL6(RL5)P9F9))RP345P345R2(L6)2L2"""
program = RSUProgram(fail_on)
tokens = program.get_tokens()
raw = program.convert_to_raw(tokens)
print(f"raw :\n{raw}")
expected = ['R', 'L', 'R', 'R', 'R', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'L', 'F', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'R', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'R', 'R', 'R', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'L', 'F', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'R', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'R', 'R', 'R', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'L', 'F', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'R', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'R', 'R', 'R', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'L', 'F', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'R', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'R', 'R', 'R', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'L', 'F', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'R', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'R', 'R', 'R', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'L', 'F', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'R', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'R', 'R', 'R', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'L', 'F', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'R', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'R', 'R', 'R', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'L', 'F', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'R', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'R', 'R', 'R', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'L', 'F', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'R', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'R', 'R', 'R', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'L', 'F', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'R', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'R', 'R', 'R', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'L', 'F', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'R', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'R', 'R', 'R', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'L', 'F', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'R', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'R', 'R', 'R', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'L', 'F', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'R', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'R', 'R', 'R', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'L', 'F', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'R', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'R', 'R', 'R', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'L', 'F', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'R', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'R', 'R', 'R', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'L', 'F', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'R', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'L', 'R', 'F', 'F', 'L', 'F', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'L', 'R', 'F', 'F', 'L', 'F', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'L', 'R', 'F', 'F', 'L', 'F', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'L', 'R', 'F', 'F', 'L', 'F', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'L', 'R', 'F', 'F', 'L', 'F', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'L', 'R', 'F', 'F', 'L', 'F', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'L', 'R', 'F', 'F', 'L', 'F', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'L', 'R', 'F', 'F', 'L', 'F', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'L', 'R', 'F', 'F', 'L', 'F', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'F', 'F', 'F', 'L', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'R', 'R', 'R', 'R', 'R', 'R', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'R', 'L', 'L', 'L', 'F', 'R', 'F', 'F', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'F', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'F', 'F', 'F', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'R', 'F', 'F', 'F', 'F', 'F', 'F', 'R', 'R', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'R', 'F', 'F', 'F', 'F', 'F', 'R', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'R', 'R', 'R', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'F', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'F', 'F', 'F', 'F', 'L', 'L', 'L', 'L', 'L', 'L', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'L', 'F', 'R', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'L', 'L', 'F', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'F', 'F', 'R', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'R', 'R', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'L', 'L', 'F', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'F', 'F', 'R', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'R', 'R', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'L', 'L', 'F', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'F', 'F', 'R', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'R', 'R', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'L', 'L', 'F', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'F', 'F', 'R', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'R', 'R', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'L', 'L', 'F', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'F', 'F', 'R', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'R', 'R', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'L', 'L', 'F', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'F', 'F', 'R', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'R', 'R', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'L', 'L', 'F', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'F', 'F', 'R', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'R', 'R', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'L', 'L', 'F', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'F', 'F', 'R', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'R', 'R', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'L', 'L', 'F', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'F', 'F', 'R', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'R', 'R', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'L', 'L', 'F', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'F', 'F', 'R', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'R', 'R', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'L', 'L', 'F', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'F', 'F', 'R', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'R', 'R', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'L', 'L', 'F', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'F', 'F', 'R', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'R', 'R', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'L', 'L', 'F', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'F', 'F', 'R', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'R', 'R', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'L', 'L', 'F', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'F', 'F', 'R', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'R', 'R', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'L', 'L', 'F', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'F', 'F', 'R', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'R', 'R']
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

# exec = program.execute_raw(raw)
# print(exec)
# expected = program.execute_raw(expected)
# if exec == expected:
# 	print("Congratulations ! it works as expected")
# else:
# 	print(f"Wrong !\nexpecting :\n{expected}")

# print("-" * 20)
# exec = program.execute()
# print(exec)
# expected = exec
# if exec == expected:
# 	print("Congratulations ! it works as expected")
# else:
# 	print(f"Wrong !\nexpecting :\n{expected}")