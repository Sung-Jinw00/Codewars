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
		print("Congratulation, got '{}' as expected".format(got))
	else:
		print("Got '{}', expected '{}'" % (got, expected))

def advanced_decode_morse(bits):
	"""
		Decode a string of bits into readable Morse code and then into English text.

		args:
			bits: A string containing '1' and '0' characters representing a Morse code signal.
				Consecutive '1's represent a signal (dot or dash), consecutive '0's represent
				pauses between signals, letters, or words.

		The process is as follows:
			1. `decode_bits(bits)` converts the raw bit string into Morse code symbols (dots, dashes, spaces)
			by normalizing timing based on the shortest sequences of '1's and '0's.
			2. `decode_morse(morseCode)` converts the Morse code symbols into readable letters
			using the `MORSE_CODE` dictionary.
			3. `advanced_decode_morse(bits)` combines these steps to directly decode a bit string
			into readable English text.

		returns:
			A string representing the decoded English text.

		example:
			>>> advanced_decode_morse('110011001100110000001...11110011001100000011')
			'HEY JUDE'
	"""
	return decode_morse(decode_bits(bits))

# bits = '1100110011001100000011000000111111001100111111001111110000000000000011001111110011111100111111000000110011001111110000001111110011001100000011'
# test_and_print(advanced_decode_morse(bits), 'HEY JUDE')
