import sys
import os

MAX_NUMBER_SIZE = 30

EXIT_SUCCESS = 0
EXIT_ERROR = -1

variable_list = dict()
command_list = ['average']

def average(parameters, variables_list):
    sum = 0
    for param in parameters:
        if param in variables_list:
           sum += variables_list[param] 
        else:
            raise Exception("Error variable not found")

    print(sum/len(parameters))

    return EXIT_SUCCESS

def parse_command(line):
    for command in command_list:
        if line.startswith(command):
            parameters = line[len(command)+1:-1]
            parameters_list = parameters.split(",")

            return average(parameters_list, variable_list)
            
    return EXIT_ERROR

def parse_variable(line):
    variable_split = line.split("=")
    if len(variable_split) == 2:
        if not variable_split[1].isdigit():
            raise Exception("Error variable not a numeric value")
        elif len(variable_split[1]) > MAX_NUMBER_SIZE:
            raise Exception("Error variable value overflow")

        variable_list[variable_split[0]] = long(variable_split[1])
        return EXIT_SUCCESS

    return EXIT_ERROR

def read_and_process(filename):
    ret = EXIT_SUCCESS

    if not os.path.exists(filename):
        print("Exception opening/reading/closing file")
        return EXIT_ERROR


    line_count = 0
    with open(filename) as fp:
        try:
            for line in fp:
                line_count += 1
                line = line.strip()
                line = line.replace(" ", "")
                if parse_variable(line) != EXIT_SUCCESS and parse_command(line) != EXIT_SUCCESS:
                    raise Exception("Error variable or command not valid") 

        except Exception as ex:
            print("Line:" + str(line_count) + ":" + ex.message)
            ret = EXIT_ERROR

    return ret