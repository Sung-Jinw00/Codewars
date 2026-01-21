def high_and_low(numbers):
	"""
		Return the highest and lowest number from a string of numbers.

		args:
			numbers: A string containing space-separated integers. (e.g., "8 3 -5 42 -1 0 0 -9 4 7 4 -4")

		returns:
			A string in the format "max min" where max is the highest number
			and min is the lowest number.
	"""
	nums = [int(n) for n in numbers.split()]
	return f"{max(nums)} {min(nums)}"

# print(high_and_low("8 3 -5 42 -1 0 0 -9 4 7 4 -4"))