#include "Interpreter.h"
#include "CommandAverage.h"

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

std::vector<string> Interpreter::parseCommandParameters(const std::string &text, char sep)
{
	vector<std::string> tokens;
	std::size_t start = 0, end = 0;
	while ((end = text.find(sep, start)) != std::string::npos) {
		if (end != start) {
			tokens.push_back(text.substr(start, end - start));
		}
		start = end + 1;
	}
	if (end != start) {
		tokens.push_back(text.substr(start));
	}
	return tokens;
}

void Interpreter::loadCommandList()
{
	commands_list.push_back(new CommandAverage());
}

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

bool Interpreter::parseVariable(std::string line)
{
	bool response = false;
	size_t var_index = 0;

	if ((var_index = line.find(VARIABLE_TOKEN)) != string::npos) 
	{
		// parse variable
		std::string s_var_name = line.substr(0, var_index);
		std::string s_var_value = line.substr(var_index + 1, line.length());

		if (s_var_value.length() >= std::numeric_limits<long>::digits) {
			throw std::overflow_error("Error variable value overflow");
		}
		else if (s_var_value.find_first_not_of(NUMBER_SEQUENCE) != std::string::npos) {
			throw std::domain_error("Error variable not a numeric value");
		}

		long l_var_value = std::atoi(s_var_value.c_str());

		variables_list[s_var_name] = l_var_value;

		response = true;
	}
	return response;
}

bool Interpreter::parseCommand(std::string line)
{
	bool response = false;

	if (!commands_list.empty())
	{
		for (std::vector<Command*>::iterator itc = commands_list.begin(); itc != commands_list.end(); ++itc) 
		{
			if (line.find((*itc)->getName()) != string::npos
				&& line[(*itc)->getName().length()] == COMMAND_START_TOKEN
				&& line[line.length() - 1] == COMMAND_END_TOKEN) {

				// parse command
				std::string command_parameters = line.substr((*itc)->getName().length() + 1, line.length() - (*itc)->getName().length() - 1 - 1);
				std::vector<std::string> command_parameters_list = parseCommandParameters(command_parameters, COMMAND_PARAMETERS_SEP);

				if (!command_parameters_list.empty()) {

					// command.execute(parameters_list, variable_list)
					(*itc)->execute(command_parameters_list, variables_list);
				}
			}
		}
	}

	return response;
}

Interpreter::Interpreter()
{
	loadCommandList();
}

Interpreter::~Interpreter()
{
	unloadCommandList();
}

int Interpreter::run(std::string filename)
{
	std::ifstream in_stream;
	in_stream.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	unsigned int line_number = 0;
	std::string line;
	vector<std::string> commands_list;
	
	int response = EXIT_SUCCESS;
	
	try 
	{
		// open file
		in_stream.open(filename);

		while (!in_stream.eof()) 
		{
			++line_number;

			// read line in file
			getline(in_stream, line);

			// remove whitespaces from line
			line.erase(std::remove_if(line.begin(), line.end(), std::isspace), line.end());

			if (!parseVariable(line) && !parseCommand(line))
			{
				throw std::exception("Error variable or command not valid");
			}
		}
		// close file
		in_stream.close();
	}
	catch (const std::exception& e) 
	{
		cout << "Line:" << line_number << e.what() << endl;
		response = EXIT_FAILURE;
	}

	return response;
}
