README

This file describes the implementation process and steps to run the code for the proposed exercise.

1. Project proposed
The propose of the exercise is described below:

Write a program that reads from a text file line by line. 
Each line can either assign a value: 
	<VALUE_NAME> = <INTEGER> 

Or it can be a command to calculate the mean average of any previously defined values: 
	average (<VALUE_NAME1>, <VALUE_NAME2,…) 

Your program should write the results of these average commands to the standard output, rounded down to the nearest integer value. 

So for example, your program should be able to read in the following file: 
restpower=10 
activepower=50 
peakpower=91 
average (restpower, activepower, peakpower) 

The output from the program for this example should be the average of 10, 50 and 90: 
50 

The project was developed using C++ (0x98) and can be compiled and execute on Windows and Linux in x86 and x64 platforms
I choosed Visual Studio 2015 Community IDE for development using Windows environment.


2. Project assumptions
	- The command names and variables names are case sensitive
	- If the variable have more than one entry the new entry will overload value from old entry
	- All whitespaces will be removed from commands before processing
	- If a command has invalid parameters an error will be shown
	- If a parameter of a command is not in the variable loaded list an error will be shown
	- The variables will only accept numeric values, if any value different from numbers was processed an error will be shown
	- The variables value cannot exceed 30 digits, to avoid number overflow


3. Project details and files structure
The project is subdivided in 4 minor projects:

- command-parser-class

	This is the main project
	And it solves the problem proposed using object oriented programming.

- command-parser-simple

	This is a simple version that solves the problem too
	It uses a non oriented object approach

- command-parser-tests
	
	This is a unit test project
	It is responsible to check if the code was implemented correctly using some predefined samples files.
	This project has dependency of BOOST test library that should be on C:\boost path

- command-parser-python

	This is another implementation of the exercise using Python language.
	And it has a unit test inside it for validation

- test-files

	This folder has many examples to use and validate the implemented solutions
	It has many success cases and others error cases


4. Project execution

	After compile you can execute programs:
	Normally after compilation for x86 platform a new folder called "Debug" or "Release" is created at project

	 - command-parser-class
	 >cd Release
	 >command-parser-class.exe ..\\test-files\\test_01.txt


	- command-parser-simple
	>cd Release
	>command-parser-simple.exe ..\\test-files\\test_01.txt

	
	- command-parser-tests
	>cd Release
	>command-parser-tests.exe

	
	- command-parser-python
	>python main.py ..\\test-files\\test_01.txt


5. Project new command extension	

	This project solution was designed thinking to add new commands to the command list.
	This section will show the steps you should follow to insert a new command to execution command list
	For a example we include "sum" command in the command list

	 - command-parser-class
	 	1. Create a new class "CommandXXX" that extend from "Command" base class

	 	2. In "CommandXXX" constructor call the constructor of base class passing command name that will be read from file "Command(XXX)"

	 	3. Implement pure virtual method from base class "execute", that will process your new command

	 	4. Add your new command in the method "getCommandList" from "CommandFactory" class 

	- command-parser-simple
	 	1. Create a new function on "command-parser-simple.cpp" with below signature:
	 	int your_function(std::vector<std::string>& command_parameters_list, map<string, long>& variables_list)

	 	2. Insert your new function to the command list in function "loadCommands"
	 	commands_list["your_function"] = &your_function;
	
	- command-parser-python
		 1. Create a new function on "command_parser_python.py" with below signature:
	 	def your_function(parameters, variables_list)

	 	2. Insert your new function to the command dictionary in function "load_commands"
	 	command_list['your_function'] = your_function