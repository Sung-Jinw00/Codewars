#                       F - Wrap this command around    <span style="color: pink"> and </span> tags so that it is highlighted pink in our editor
#                       L - Wrap this command around    <span style="color: red"> and </span> tags so that it is highlighted red in our editor
#                       R - Wrap this command around    <span style="color: green"> and </span> tags so that it is highlighted green in our editor
# Digits from 0 through 9 - Wrap these around           <span style="color: orange"> and </span> tags so that they are highlighted orange in our editor
# highlight("FFFR345F2LL"); // => "<span style=\"color: pink\">FFF</span><span style=\"color: green\">R</span><span style=\"color: orange\">345</span><span style=\"color: pink\">F</span><span style=\"color: orange\">2</span><span style=\"color: red\">LL</span>"

import re

def highlight(code):
    code = re.sub(r"(F+)", r'<span style="color: pink">\g<1></span>', code)
    code = re.sub(r"(L+)", r'<span style="color: red">\g<1></span>', code)
    code = re.sub(r"(R+)", r'<span style="color: green">\g<1></span>', code)
    code = re.sub(r"(\d+)", r'<span style="color: orange">\g<1></span>', code)
    return code

print(highlight("FFFLL2(345)RRR324F"))