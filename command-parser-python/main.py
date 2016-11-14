import sys
from command_parser_python import read_and_process

if len(sys.argv) != 2:
    exit(EXIT_ERROR)

filename = sys.argv[1]
try:
    ret = read_and_process(filename)
except Exception as ex:
    print(ex)
    ret = EXIT_ERROR

exit(ret)