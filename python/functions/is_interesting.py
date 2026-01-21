def round(nb):	return set(nb[1:]) == {'0'}
def palindrome(nb):	return nb == nb[::-1]
def increment(nb): return nb in '1234567890'
def decrement(nb): return nb in '9876543210'

def is_interesting(nb, awesome_phrases):
	"""
		Determine if a number is "interesting".

		args:
			nb: An integer representing the number to check.
			awesome_phrases: A list of integers considered "interesting".

		A number is considered interesting if it meets one of the following criteria:
		- It is 100 or greater.
		- It is in the list `awesome_phrases`.
		- It has a special numeric pattern:
			* All zeros after the first digit (round number, e.g., 1000)
			* Every digit increments (e.g., 1234)
			* Every digit decrements (e.g., 4321)
			* The number is a palindrome (e.g., 1221)

		The function also checks the next two numbers to see if they will be
		interesting soon.

		returns:
			- 2 if `nb` is interesting.
			- 1 if an upcoming number (`nb`+1 or `nb`+2) is interesting.
			- 0 otherwise.
	"""
	for n, answer in zip(range(nb, nb + 3), (2, 1, 1)):
		if n >= 100 and (any(test(str(n)) for test in (round, increment, decrement, palindrome)) or n in awesome_phrases):
			return answer
	return 0

# tests = [	{'n': 100, 'interesting': [1337, 256], 'expected': 2},
# 			{'n': 1336, 'interesting': [1337, 256], 'expected': 1},
# 			{'n': 1337, 'interesting': [1337, 256], 'expected': 2},
# 			{'n': 11208, 'interesting': [1337, 256], 'expected': 0},
# 			{'n': 11209, 'interesting': [1337, 256], 'expected': 1},
# 			{'n': 11211, 'interesting': [1337, 256], 'expected': 2}]
# for t in tests:
# 	result = is_interesting(t['n'], t['interesting'])
# 	assert result == t['expected'], f"Failed on {t['n']}: expected {t['expected']}, got {result}"
# print("All tests passed ✅")