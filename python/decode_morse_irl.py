import re

MORSE_CODE = {
	'.-': 'A', '-...': 'B', '-.-.': 'C', '-..': 'D', '.': 'E',
	'..-.': 'F', '--.': 'G', '....': 'H', '..': 'I', '.---': 'J',
	'-.-': 'K', '.-..': 'L', '--': 'M', '-.': 'N', '---': 'O',
	'.--.': 'P', '--.-': 'Q', '.-.': 'R', '...': 'S', '-': 'T',
	'..-': 'U', '...-': 'V', '.--': 'W', '-..-': 'X', '-.--': 'Y',
	'--..': 'Z',
	'-----': '0', '.----': '1', '..---': '2', '...--': '3', '....-': '4',
	'.....': '5', '-....': '6', '--...': '7', '---..': '8', '----.': '9',
	'.-.-.-': '.', '--..--': ',', '..--..': '?', '.----.': "'", '-.-.--': '!',
	'-..-.': '/', '-.--.': '(', '-.--.-': ')', '.-...': '&', '---...': ':',
	'-.-.-.': ';', '-...-': '=', '.-.-.': '+', '-....-': '-', '..--.-': '_',
	'.-..-.': '"', '...-..-': '$', '.--.-.': '@', '...---...': 'SOS'
}

from re import findall

def split_groups(lengths):
	groups = []
	for k, g in enumerate(lengths):
		if k == 0 or g == lengths[k-1]+1:
			if not groups: groups.append([g])
			else: groups[-1].append(g)
		else:
			groups.append([g])
	return  groups

def decodeBitsAdvanced(bits):
	if not set(bits).issubset({'0', '1'}) or not bits.strip('0'):
		return ''
	seqs = findall(r'1+|0+', bits.strip('0'))
	lengths_1 = sorted({len(s) for s in seqs if s[0] == '1'})
	lengths_0 = sorted({len(s) for s in seqs if s[0] == '0'})
	half = max(1, len(lengths_1) // 2)
	groups_1 = [lengths_1[:half], lengths_1[half:]]
	groups_0 = [g for i, g in enumerate(groups_1 + split_groups(lengths_0)) 
				if i < 2 or not any(j in groups_1[0] + groups_1[1] for j in g)]
	for i in range(len(groups_0) - 1, 1, -1):
		if any(j in groups_0[i] for j in groups_1[0]) or any(j in groups_0[i] for j in groups_1[1]):
			groups_0.pop(i)
	if len(groups_0) > 1 and groups_0[-1] and max(groups_0[-1]) < min(groups_0[0]):
		groups_0 = [groups_0[-1]] + groups_0[:-1]
		if not groups_1[1]:
			groups_1 = [groups_1[-1]] + groups_1[:-1]
	if len(groups_0) == 3 and not groups_0[1] and 6 > min(groups_0[2]) > max(groups_0[0]):
		groups_0.pop(1)
	if len(groups_0) > 3:
		groups_0 = groups_0[:2] + [sum(groups_0[2:], [])]
	return ''.join(('.' if len(s) in groups_1[0] else '-') if s[0]=='1'
		else '' if len(s) in groups_0[0] else '   ' if len(groups_0) > 2 and len(s) in groups_0[-1] else ' '
		for s in seqs)

def decodeMorse(morseCode):
	return ' '.join(''.join(MORSE_CODE.get(c, '') for c in word.split()) for word in morseCode.strip().split('   ')) if morseCode else ''

def test_and_print(got, expected):
	if got == expected:
		print("Congratulations, got '%s' as expected" % got)
	else:
		print("Wrong, got '%s', expected '%s'" % (got, expected))

bits = '00000000000111111100000011010001110111000000001110000000000000000001111111011111100001101111100000111100111100011111100000001011100000011111110010001111100110000011111100101111100000000000000111111100001111010110000011000111110010000011111110001111110011111110000010001111110001111111100000001111111101110000000000000010110000111111110111100000111110111110011111110000000011111001011011111000000000000111011111011111011111000000010001001111100000111110111111110000001110011111100011111010000001100001001000000000000000000111111110011111011111100000010001001000011111000000100000000101111101000000000000011111100000011110100001001100000000001110000000000000001101111101111000100000100001111111110000000001111110011111100011101100000111111000011011111000111111000000000000000001111110000100110000011111101111111011111111100000001111110001111100001000000000000000000000000000000000000000000000000000000000000'
decoded = decodeMorse(decodeBitsAdvanced(bits))
test_and_print(decoded, 'THE QUICK BROWN FOX JUMPS OVER THE LAZY DOG')
