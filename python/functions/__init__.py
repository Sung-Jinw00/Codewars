""" all functions in functions directory """
# From files
from .add_binary import add_binary
from .add_to_average import add_to_average
from .count_arara import count_arara
from .decode import decode
from .dig_pow import dig_pow
from .high_and_low import high_and_low
from .is_interesting import is_interesting
from .luck_check import luck_check
from .range_extraction import range_extraction
from .strip_comments import strip_comments
from .unique_in_order import unique_in_order

# From directories
from . import morse
from . import RoboScript

# can do from functions import *
__all__ = [
    "add_binary",
    "add_to_average",
    "count_arara",
    "decode",
    "dig_pow",
    "high_and_low",
    "is_interesting",
    "luck_check",
    "range_extraction",
    "strip_comments",
    "unique_in_order",
    "morse",
    "RoboScript"
]
