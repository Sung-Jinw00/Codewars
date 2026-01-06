def round(nb):	return set(nb[1:]) == {'0'}
def palindrome(nb):	return nb == nb[::-1]
def increment(nb): return nb in '1234567890'
def decrement(nb): return nb in '9876543210'

def is_interesting(nb, awesome_phrases):
	for n, answer in zip(range(nb, nb + 3), (2, 1, 1)):
		if n >= 100 and (any(test(str(n)) for test in (round, increment, decrement, palindrome)) or n in awesome_phrases):
			return answer
	return 0

tests = [	{'n': 100, 'interesting': [1337, 256], 'expected': 2},
			{'n': 1336, 'interesting': [1337, 256], 'expected': 1},
			{'n': 1337, 'interesting': [1337, 256], 'expected': 2},
			{'n': 11208, 'interesting': [1337, 256], 'expected': 0},
			{'n': 11209, 'interesting': [1337, 256], 'expected': 1},
			{'n': 11211, 'interesting': [1337, 256], 'expected': 2}]
for t in tests:
	result = is_interesting(t['n'], t['interesting'])
	assert result == t['expected'], f"Failed on {t['n']}: expected {t['expected']}, got {result}"
print("All tests passed ✅")