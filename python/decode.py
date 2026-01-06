import string

def encode(s):
	return s

def decode(s):
	p_ascii = string.printable
	table = {encode(c)[0]: c for c in p_ascii}
	result = []
	for i, c in enumerate(s):
		for j in range(i + 1):
			c = table.get(c, c)
			if j == i:
				result.append(c)
	return ''.join(result)
