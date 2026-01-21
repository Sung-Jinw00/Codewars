def range_extraction(args):
	"""
		Summarize a list of integers by collapsing consecutive sequences into ranges.

		args:
			args: A list of integers sorted in ascending order.

		Consecutive numbers of length 3 or more are represented as "start-end".
		Numbers that are isolated or in pairs are left as individual numbers.

		returns:
			A string representing the summarized ranges, separated by commas.

		example:
			>>> solution([-10, -9, -8, -6, -3, -2, -1, 0, 1, 3, 4, 5])
			'-10--8,-6,-3-1,3-5'
			>>> solution([1, 2, 3, 5, 6])
			'1-3,5,6'
	"""
	if not args:
		return ""
	answer, start = [], 0
	while start < len(args):
		end = start
		while end + 1 < len(args) and args[end + 1] == args[end] + 1:
			end += 1
		if end - start >= 2:
			answer.append(f"{args[start]}-{args[end]}")
		else:
			answer.extend(map(str, args[start : end + 1]))
		start = end + 1
	return ",".join(answer)

# answer = range_extraction([-10, -9, -8, -6, -3, -2, -1, 0, 1, 3, 4, 5, 7, 8, 9, 10, 11, 14, 15, 17, 18, 19, 20])
# if answer != "-10--8,-6,-3-1,3-5,7-11,14,15,17-20":
# 	print(f"Wrong, expected :\n\"-10--8,-6,-3-1,3-5,7-11,14,15,17-20\"\ngot\n\"{answer}\"")
# else:
# 	print(f"Successfully get \"-10--8,-6,-3-1,3-5,7-11,14,15,17-20\" !")