unchanded = "!\"#$%&'()*+/:;<=>@[\]^_`{|}~|"
sequence = " ,-./0123456789?ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"
def encode(s):
	  return s
# 	first_change = ""
# 	for c in s:
# 		if c in unchanded:
# 			first_change += c
# 			continue
# 		first_change += sequence[sequence.find(c) * 2]
# 	i = 0
# 	final = []
# 	while (i < 1):
# 		for c in first_change:
# 			if c in unchanded:
# 				final += c
# 				continue
# 			new_c = (sequence.find(c) * 2) % len(sequence)
# 			new_c = 1 if new_c == 0 else new_c
# 			final += sequence[new_c]
# 		i += 1
# 	return "".join(final)

def decode(s):
	a,b,c = "", "", ""
	print(encode(" !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~"))
	for w in "abcdefghijklmnopqrstuvwxyz":
		a += encode(  "" + w)[0]
		# b += encode( "_" + w)[1]
		# c += encode("__" + w)[2]
	print(f"\na = {a}")
	# print(f"b = {b}")
	# print(f"c = {c}")
	return s
#    "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789 ,-./?"
# a = bdfhjlnprtvxzBDFHJLNPRTVXZ13579, acegikmoqsuwyACEGIKMOQSUWY024?8-6/.
# a = bdfhjlnprtvxzBDFHJLNPRTVXZ
# b = dhlptxBFJNRVZ37,aeimquyCGK
# c = hpxFNV3,emuCKS08bjrzHPX5 g

sequence = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789? ,-/."
def gaps_between_strings(original, encoded):
	if len(original) != len(encoded):
		raise ValueError("Les strings doivent avoir la même longueur")
	span = []
	for i in range(len(original)):
		enc_i = sequence.find(encoded[i])
		ori_i = sequence.find(original[i])
		span.append((original[i], encoded[i], (enc_i - ori_i) % len(sequence)))
	return span
gaps = gaps_between_strings(sequence, "bdfhjlnprtvxzBDFHJLNPRTVXZ13579, acegikmoqsuwyACEGIKMOQSUWY024-86?/.")
decode("oui")
for o, e, g in sorted(gaps, key=lambda x: x[2]):
    print(f"{o} -> {e} : {g}")

# from itertools import permutations

# symbols = "-,. /?"

# all_combinations = []

# # longueur de 1 à len(symbols)
# for p in permutations(symbols, len(symbols)):
# 	all_combinations.append(''.join(p))

# print(f"Nombre total de combinaisons : {len(all_combinations)}")
# for i in range(0, len(all_combinations)):
# 	print(f"\"{all_combinations[i]}\"")
# 	i += 1