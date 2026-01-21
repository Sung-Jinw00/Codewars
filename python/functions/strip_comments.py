def strip_comments(str, markers):
    """
        Remove comments from a multiline string based on given comment markers.

        args:
            str: A multiline string potentially containing comments.
            markers: A list of strings representing comment markers.

        Each line of the input string is processed independently. For each marker,
        everything following the marker on a line is removed. Trailing whitespace
        is also stripped from each processed line.

        returns:
            A string where all comments and trailing spaces have been removed.

        example:
            >>> strip_comments("apples, pears # and bananas\\ngrapes\\nbananas !apples", "#!")
            'apples, pears\\ngrapes\\nbananas'
    """
    sentences = str.split('\n')
    for marker in markers:
        sentences = [sentence.split(marker)[0].rstrip() for sentence in sentences]
    return '\n'.join(sentences)

# solution = 'apples, pears\ngrapes\nbananas'
# answer = strip_comments('apples, pears # and bananas\ngrapes\nbananas !apples', ['#', '!'])
# if answer != solution:
# 	print(f"Wrong, expected :\n\"{solution}\"\n\ngot\n\n\"{answer}\"")
# else:
# 	print(f"Successfully get \"{solution}\" !")