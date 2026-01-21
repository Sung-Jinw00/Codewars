def dig_pow(n, p):
	"""
        Check if a number equals the sum of its digits raised to consecutive powers.

        args:
            n: An integer to test.
            p: The starting power for the first digit.

        Process:
            1. Represent `n` as a sequence of its digits.
               Example: n = 89 -> digits = [8, 9]
            2. Raise each digit to a consecutive power, starting at `p`.
               For n=89 and p=1:
                   8 ** 1 = 8
                   9 ** 2 = 81
            3. Sum these powered digits:
                   8 + 81 = 89
            4. Check if the sum is divisible by `n`:
                   89 / 89 = 1

        returns:
            The integer `k` if the sum of powered digits equals `n * k`, otherwise -1.
    """
	res = sum(int(digit) ** (p + i) for i, digit in enumerate(str(n)))
	return res // n if res % n == 0 else -1

# print(str(dig_pow(89, 1)))