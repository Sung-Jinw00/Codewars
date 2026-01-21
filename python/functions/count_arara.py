def count_arara(n):
    """
        Count a number using the Arara indigenous language.

        args:
            n: An integer to represent in Arara binary counting.

        In this counting system:
        - "adak" represents 2
        - "anane" represents 1

        returns:
            A string representing the number `n` in Arara.
    """
    return " ".join(n // 2 * ['adak'] + n % 2 * ['anane'])