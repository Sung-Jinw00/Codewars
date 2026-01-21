def add_binary(a, b):
	"""
        Add two integers and return the result in binary.

        args:
            a: First integer.
            b: Second integer.

        returns:
            A string representing the sum of `a` and `b` in binary.
    """
	return bin(a + b)[2:]