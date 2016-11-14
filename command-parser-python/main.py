import sys
from command_parser_python import read_and_process

EXIT_SUCCESS = 0
EXIT_ERROR = 1

ret = EXIT_SUCCESS

if len(sys.argv) != 2:
    print("File name not found!\nPlease use: python main.py test.txt")
    exit(EXIT_ERROR)

filename = sys.argv[1]
try:
    ret = read_and_process(filename)
except Exception as ex:
    print(ex)
    ret = EXIT_ERROR

exit(ret)