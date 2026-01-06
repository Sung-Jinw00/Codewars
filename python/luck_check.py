def luck_check(st):
	int(st)
	return not sum(int(a) - int(b) for a, b in zip(st[:len(st) // 2], st[::-1]))

print(luck_check("003111"))