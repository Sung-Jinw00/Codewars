from itertools import groupby

def unique_in_order(iterable):
    """
        Return a list of items without consecutive duplicates.

        args:
            iterable: An iterable containing elements that may repeat consecutively.

        Each consecutive duplicate in the input iterable is removed, keeping only
        the first occurrence.

        returns:
            A list containing the elements of `iterable` with consecutive duplicates removed.

        example:
            >>> unique_in_order("AAAABBBCCDAABBB")
            ['A', 'B', 'C', 'D', 'A', 'B']
            >>> unique_in_order([1, 2, 2, 3, 3])
            [1, 2, 3]
    """
    return [k for (k, _) in groupby(iterable)]
