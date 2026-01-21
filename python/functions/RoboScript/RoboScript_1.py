import re

def highlight(code):
    """
        Highlight specific characters in a RoboScript command string using HTML <span> tags.

        args:
            code: A string representing a sequence of RoboScript commands and digits. 
                Specific characters are highlighted with different colors:
                - 'F': pink
                - 'L': red
                - 'R': green
                - digits '0'-'9': orange

        The function wraps consecutive occurrences of these characters in <span> tags 
        with the corresponding color style.

        returns:
            A string with the same commands, but with HTML <span> tags added for coloring.

        example:
            >>> highlight("FFFR345F2LL")
            '<span style="color: pink">FFF</span><span style="color: green">R</span>'
            '<span style="color: orange">345</span><span style="color: pink">F</span>'
            '<span style="color: orange">2</span><span style="color: red">LL</span>'
    """
    code = re.sub(r"(F+)", r'<span style="color: pink">\g<1></span>', code)
    code = re.sub(r"(L+)", r'<span style="color: red">\g<1></span>', code)
    code = re.sub(r"(R+)", r'<span style="color: green">\g<1></span>', code)
    code = re.sub(r"(\d+)", r'<span style="color: orange">\g<1></span>', code)
    return code

# print(highlight("FFFLL2(345)RRR324F"))