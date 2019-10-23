import sys
import re
import random
import string


if len(sys.argv) != 2:
    print('Needs a command line argument')
    exit(1)

in_file = sys.argv[1]
if not in_file.endswith('.;'):
    print('Needs to be a semicolon file')
    exit(1)

out_file = in_file[:-2]
out_file += '_obfuscated.;'

try:
    with open(in_file, 'r') as f:
        s = f.read()
except:
    print('Error opening in file')
    exit(1)

s = re.findall(';+', s)


def rand_str():
    str_len = random.randint(1, 69)
    letters = string.printable.replace(';', '')
    return ''.join(random.choice(letters) for i in range(str_len))


obf = list()
for x in s:
    obf += x
    obf += [rand_str()]

try:
    with open(out_file, 'w+') as f:
        f.write(''.join(obf))
except:
    print('Error opening out file')
