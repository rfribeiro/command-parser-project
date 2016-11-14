import unittest
import sys
from StringIO import StringIO
import command_parser_python

class Test_test1(unittest.TestCase):
    def setUp(self):
        self.output = StringIO()
        self.saved_stdout = sys.stdout
        sys.stdout = self.output
        pass

    def tearDown(self):
        self.output.close()
        sys.stdout = self.saved_stdout

    def test_01(self):
        command_parser_python.read_and_process("..\\test-files\\test_01.txt")
        output = sys.stdout.getvalue().strip()
        self.assertEqual(output, '50')

    def test_02(self):
        command_parser_python.read_and_process("..\\test-files\\test_02.txt")
        output = sys.stdout.getvalue().strip()
        self.assertEqual(output, '100')

    def test_03(self):
        command_parser_python.read_and_process("..\\test-files\\test_03.txt")
        output = sys.stdout.getvalue().strip()
        self.assertEqual(output, '50')

    def test_04(self):
        command_parser_python.read_and_process("..\\test-files\\test_04.txt")
        output = sys.stdout.getvalue().strip()
        self.assertEqual(output, '50\n60')

    def test_05(self):
        command_parser_python.read_and_process("..\\test-files\\test_05.txt")
        output = sys.stdout.getvalue().strip()
        self.assertEqual(output, '50\n60\n30\n50\n10')

    def test_06(self):
        command_parser_python.read_and_process("..\\test-files\\test_06.txt")
        output = sys.stdout.getvalue().strip()
        self.assertEqual(output, '50\n50\n10\n50\n91\n30\n50\n70')

    def test_07(self):
        command_parser_python.read_and_process("..\\test-files\\test_07.txt")
        output = sys.stdout.getvalue().strip()
        self.assertEqual(output, '50')

    def test_08(self):
        command_parser_python.read_and_process("..\\test-files\\test_08.txt")
        output = sys.stdout.getvalue().strip()
        self.assertEqual(output, 'Line:4:Error variable not found')

    def test_error_01(self):
        command_parser_python.read_and_process("..\\test-files\\test_error_01.txt")
        output = sys.stdout.getvalue().strip()
        self.assertEqual(output, 'Line:1:Error variable not a numeric value')

    def test_error_02(self):
        command_parser_python.read_and_process("..\\test-files\\test_error_02.txt")
        output = sys.stdout.getvalue().strip()
        self.assertEqual(output, 'Line:1:Error variable value overflow')

    def test_error_03(self):
        command_parser_python.read_and_process("..\\test-files\\test_error_03.txt")
        output = sys.stdout.getvalue().strip()
        self.assertEqual(output, 'Line:4:Error variable not found')

    def test_error_04(self):
        command_parser_python.read_and_process("..\\test-files\\test_error_04.txt")
        output = sys.stdout.getvalue().strip()
        self.assertEqual(output, 'Line:2:Error variable or command not valid')

    def test_error_05(self):
        command_parser_python.read_and_process("..\\test-files\\test_error_05.txt")
        output = sys.stdout.getvalue().strip()
        self.assertEqual(output, 'Line:4:Error variable or command not valid')

    def test_error_06(self):
        command_parser_python.read_and_process("..\\test-files\\test_error_06.txt")
        output = sys.stdout.getvalue().strip()
        self.assertEqual(output, 'Line:4:Error variable or command not valid')

    def test_error_07(self):
        command_parser_python.read_and_process("..\\test-files\\test_error_07.txt")
        output = sys.stdout.getvalue().strip()
        self.assertEqual(output, 'Line:4:Error variable not found')

    def test_error_file_not_found(self):
        command_parser_python.read_and_process("..\\test-files\\xxxx.txt")
        output = sys.stdout.getvalue().strip()
        self.assertEqual(output, 'Exception opening/reading/closing file')

if __name__ == '__main__':
    if len(sys.argv) != 2:
        sys.exit("ERRORommand-line parameter must be supplied for these tests")
    command_line_param = sys.argv[1]
    del sys.argv[1:]
    unittest.main()
