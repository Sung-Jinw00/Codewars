def luck_check(st):
	"""
		Check if a string of digits is "lucky".

		A string is considered lucky if the sum of the first half of its digits
		equals the sum of the second half. Works only for strings with even length.

		args:
			st: A string containing digits (e.g., "003111").

		returns:
			True if the string is lucky, False otherwise.

		example:
			>>> luck_check("003111")
			True
			>>> luck_check("123321")
			True
			>>> luck_check("123456")
			False
		"""
	int(st)
	return not sum(int(a) - int(b) for a, b in zip(st[:len(st) // 2], st[::-1]))

# print(luck_check("003111"))