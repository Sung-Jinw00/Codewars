def add_to_average(current, points, add):
    """
        Update an average with a new value.

        args:
            current: Current average value.
            points: Number of values already included in the average.
            add: New value to add to the average.

        returns:
            The updated average including the new value.
    """
    return (current * points + add) / (current + 1)