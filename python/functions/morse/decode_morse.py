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

def decode_morse(morseCode):
    """
		Decode a string of Morse code into English text.

		args:
			morseCode: A string containing Morse code symbols (dots `.` and dashes `-`),
					with letters separated by a single space and words by three spaces.

		Each Morse code letter is mapped to its corresponding character
		using the `MORSE_CODE` dictionary. Words are separated by three spaces,
		letters by one space.

		returns:
			A string representing the decoded English text.

		example:
			>>> decode_morse('.... . -.--   .--- ..- -.. .')
			'HEY JUDE'
			>>> decode_morse('.-')
			'A'
			>>> decode_morse('...---...')
			'SOS'
			>>> decode_morse('...   ---   ...')
			'S O S'
	"""
    return ' '.join(''.join(MORSE_CODE[letter] for letter in word.split(' ')) for word in morseCode.strip().split('   '))

# def assert_equals(actual, expected):
# 	if actual == expected:
# 		print(f"✅ PASS: {actual}")
# 	else:
# 		print(f"❌ FAIL: expected {expected}, got {actual}")


# # --------------------
# # Squelette pour les tests
# # --------------------
# def tests():
		
# 	print("Should obtain correct decoding of Morse code from the description")
# 	assert_equals(decode_morse('.... . -.--   .--- ..- -.. .'), 'HEY JUDE')

# 	print("Should obtain correct decoding of Morse code for basic examples")
# 	assert_equals(decode_morse('.-'), 'A')
# 	assert_equals(decode_morse('--...'), '7')
# 	assert_equals(decode_morse('...-..-'), '$')
# 	assert_equals(decode_morse('.'), 'E')
# 	assert_equals(decode_morse('..'), 'I')
# 	assert_equals(decode_morse('. .'), 'EE')
# 	assert_equals(decode_morse('.   .'), 'E E')
# 	assert_equals(decode_morse('...-..- ...-..- ...-..-'), '$$$')
# 	assert_equals(decode_morse('----- .---- ..--- ---.. ----.'), '01289')
# 	assert_equals(decode_morse('.-... ---...   -..-. --...'), '&: /7')
# 	assert_equals(decode_morse('...---...'), 'SOS')
# 	assert_equals(decode_morse('... --- ...'), 'SOS')
# 	assert_equals(decode_morse('...   ---   ...'), 'S O S')
		
# 	print("Should obtain correct decoding of Morse code for examples with extra spaces")
# 	assert_equals(decode_morse(' . '), 'E')
# 	assert_equals(decode_morse('   .   . '), 'E E')

# 	print("Should obtain correct decoding of Morse code for a complex example, and should ignore leading and trailing whitespace")
# 	assert_equals(decode_morse('      ...---... -.-.--   - .... .   --.- ..- .. -.-. -.-   -... .-. --- .-- -.   ..-. --- -..-   .--- ..- -- .--. ...   --- ...- . .-.   - .... .   .-.. .- --.. -.--   -.. --- --. .-.-.-  '), 'SOS! THE QUICK BROWN FOX JUMPS OVER THE LAZY DOG.')


# if __name__ == "__main__":
# 	tests()
