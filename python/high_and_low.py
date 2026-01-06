def high_and_low(numbers):
	nums = [int(n) for n in numbers.split()]
	return f"{max(nums)} {min(nums)}"

print(high_and_low("8 3 -5 42 -1 0 0 -9 4 7 4 -4"))