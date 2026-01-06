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

def decode_bits(bits):
	if not bits or set(bits).issubset({0, 1}):
		return ''
	bits = bits.strip('0')
	span = min(len(s) for s in findall(r'1+|0+', bits))
	return bits[::span].replace('111', '-').replace('1','.').replace('0000000','   ').replace('000',' ').replace('0','')

def decode_morse(morseCode):
	return ' '.join(''.join(MORSE_CODE[letter] for letter in word.split(' ')) for word in morseCode.strip().split('   '))

def test_and_print(got, expected):
	if got == expected:
		print("Congratulation, got '%s' as expected".format(got))
	else:
		print("<pre style='display:inline'>Got '%s', expected '%s'</pre>" % (got, expected))

test_and_print(decode_morse(decode_bits('1100110011001100000011000000111111001100111111001111110000000000000011001111110011111100111111000000110011001111110000001111110011001100000011')), 'HEY JUDE')
