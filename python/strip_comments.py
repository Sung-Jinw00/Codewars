def strip_comments(str, markers):
    sentences = str.split('\n')
    for marker in markers:
        sentences = [sentence.split(marker)[0].rstrip() for sentence in sentences]
    return '\n'.join(sentences)

solution = 'apples, pears\ngrapes\nbananas'
answer = strip_comments('apples, pears # and bananas\ngrapes\nbananas !apples', ['#', '!'])
if answer != solution:
	print(f"Wrong, expected :\n\"{solution}\"\n\ngot\n\n\"{answer}\"")
else:
	print(f"Successfully get \"{solution}\" !")