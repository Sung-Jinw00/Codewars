def dig_pow(n, p):
	res = sum(int(digit) ** (p + i) for i, digit in enumerate(str(n)))
	return res // n if res % n == 0 else -1

print(str(dig_pow(89, 1)))