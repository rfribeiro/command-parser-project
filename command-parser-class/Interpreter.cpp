#include "Interpreter.h"
#include "CommandFactory.h"

#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>

using namespace std;

#define VARIABLE_TOKEN		'='
#define COMMAND_START_TOKEN '('
#define COMMAND_END_TOKEN	')'
#define COMMAND_PARAMETERS_SEP ','
#define NUMBER_SEQUENCE "0123456789"

/**
* parseCommandParameters - Method that parse command parameters inside brackets
* @param text String containing parameters list separated by sep.
* @param sep Separator character that will split parameters list
* @return vector containing parameters list splitted
*/
std::vector<string> Interpreter::parseCommandParameters(const std::string &text, char sep)
{
	vector<std::string> tokens;
	std::size_t start = 0, end = 0;
	while ((end = text.find(sep, start)) != std::string::npos) 
	{
		tokens.push_back(text.substr(start, end - start));
		start = end + 1;
	}
	if (end != start) 
	{
		tokens.push_back(text.substr(start));
	}
	return tokens;
}

/**
* loadCommandList - Method that load all commands available calling command factory class
*/
void Interpreter::loadCommandList()
{
	commands_list = CommandFactory::getCommandList();
}

/**
* unloadCommandList - Method that unload all commands available and delete commands references
*/
void Interpreter::unloadCommandList()
{
	if (!commands_list.empty())
	{
		std::vector<Command*>::iterator it;
		for (it = commands_list.begin(); it != commands_list.end(); )
		{
			delete * it;
			it = commands_list.erase(it);
		}
	}
}

/**
* parseVariable - Method that try to parse string passed as a variable 
*					The variable format is: variable_name=variable_value
*					This method can throw some exceptions during process that are catch on run method
*					overflow_error:	this exception is raised when the variable_value has more than 31 character 
*									that is the maximum size of long type
*					domain_error:	this exception is raised when the variable_value does not have only numbers on it
* @param line String containing possible variable format.
* @return int value that tell if the string was parsed with success or not
*/
int Interpreter::parseVariable(std::string line)
{
	int response = EXIT_FAILURE;
	size_t var_index = 0;

	if ((var_index = line.find(VARIABLE_TOKEN)) != string::npos) 
	{
		// parse variable
		std::string s_var_name = line.substr(0, var_index);
		std::string s_var_value = line.substr(var_index + 1, line.length());

		if (s_var_value.length() >= std::numeric_limits<long>::digits) 
		{
			throw std::overflow_error("Error variable value overflow");
		}
		else if (s_var_value.find_first_not_of(NUMBER_SEQUENCE) != std::string::npos) 
		{
			throw std::domain_error("Error variable not a numeric value");
		}

		long l_var_value = std::atoi(s_var_value.c_str());

		variables_list[s_var_name] = l_var_value;

		response = EXIT_SUCCESS;
	}
	return response;
}

/**
* parseCommand - Method that try to parse string passed as a command that is search on command_list
*					The command format is: command_name(param1, param2, etc)
*					Also this method call execute method on command object
*					This method can throw some exceptions during process when call execute method from command object that are catch on run method
* @param line String containing possible command format.
* @return int value that tell if the string was parsed with success or not
*/
int Interpreter::parseCommand(std::string line)
{
	int response = EXIT_FAILURE;

	if (!commands_list.empty())
	{
		for (std::vector<Command*>::iterator itc = commands_list.begin(); itc != commands_list.end(); ++itc) 
		{
			if (line.find((*itc)->getName()) != string::npos
				&& line[(*itc)->getName().length()] == COMMAND_START_TOKEN
				&& line[line.length() - 1] == COMMAND_END_TOKEN) 
			{
				// parse command
				std::string command_parameters = line.substr((*itc)->getName().length() + 1, line.length() - (*itc)->getName().length() - 1 - 1);
				std::vector<std::string> command_parameters_list = parseCommandParameters(command_parameters, COMMAND_PARAMETERS_SEP);

				if (!command_parameters_list.empty()) 
				{
					return (*itc)->execute(command_parameters_list, variables_list);
				}
			}
		}
	}

	return response;
}

/**
* Contructor - Default constructor that call loadCommandList to load commands supported
*/
Interpreter::Interpreter()
{
	loadCommandList();
}

/**
* Destructor - Destructor that call unloadCommandList to unload all commands
*/
Interpreter::~Interpreter()
{
	unloadCommandList();
}

/**
* process - Method process the string line read from file and check if it is a valid command or variable
*					std::exception:	this exception is throw if line passed does not have a valid variable or command format
* @param line String containing possible command or variable format.
* @return int value that tell if the string is a valid command on variable or not
*/
int Interpreter::process(std::string line)
{
	// remove whitespaces from line
	line.erase(std::remove_if(line.begin(), line.end(), std::isspace), line.end());

	if (!line.empty())
	{
		if (parseVariable(line) == EXIT_FAILURE 
		&&	parseCommand(line) == EXIT_FAILURE)
		{
			throw std::exception("Error variable or command not valid");
		}
	}

	return EXIT_SUCCESS;
}

/**
* run - Main method that read filename parameter line by line and process line read.
*		It call process method to process line read from file
* @param filename String containing script file name that will be read.
* @return int That return if the file was read and processed with success or fail
*/
int Interpreter::run(std::string filename)
{
	std::ifstream in_stream;
	in_stream.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	unsigned int line_number = 0;
	std::string line;
	
	int response = EXIT_SUCCESS;
	
	try 
	{
		in_stream.open(filename);

		while (!in_stream.eof()) 
		{
			++line_number;

			// read line in file
			getline(in_stream, line);

			process(line);
		}

		in_stream.close();
	}
	catch (const std::ifstream::failure) 
	{
		cout << "Exception opening/reading/closing file" << endl;
		response = EXIT_FAILURE;
	}
	catch (const std::exception& e) 
	{
		cout << "Line:" << line_number << ":" << e.what() << endl;
		response = EXIT_FAILURE;
	}

	return response;
}
