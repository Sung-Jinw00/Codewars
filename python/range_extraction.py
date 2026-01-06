def solution(args):
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

answer = solution([-10, -9, -8, -6, -3, -2, -1, 0, 1, 3, 4, 5, 7, 8, 9, 10, 11, 14, 15, 17, 18, 19, 20])
if answer != "-10--8,-6,-3-1,3-5,7-11,14,15,17-20":
	print(f"Wrong, expected :\n\"-10--8,-6,-3-1,3-5,7-11,14,15,17-20\"\ngot\n\"{answer}\"")
else:
	print(f"Successfully get \"-10--8,-6,-3-1,3-5,7-11,14,15,17-20\" !")