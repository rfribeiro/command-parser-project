#include <iostream>
#include <fstream>
#include <map>
#include <unordered_map>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>

using namespace std;

#define COMMAND_AVERAGE "average"
#define COMMAND_SUM "sum"

#define VARIABLE_TOKEN		'='
#define COMMAND_START_TOKEN '('
#define COMMAND_END_TOKEN	')'
#define COMMAND_PARAMETERS_SEP ','
#define NUMBER_SEQUENCE "0123456789"

typedef std::map<std::string, int (*)(std::vector<std::string>& command_parameters_list, map<string, long>& variables_list)> command_map;

/**
* calculateSum
*	Example Function that calculates the sum of all parameters passed at command_parameters_list based on variables_list
*/
int calculateSum(std::vector<std::string>& command_parameters_list, map<string, long>& variables_list)
{
	int ret = EXIT_SUCCESS;

	long average_sum = 0;
	for (std::vector<std::string>::iterator it = command_parameters_list.begin(); it != command_parameters_list.end(); ++it) {
		if (variables_list.find(*it) != variables_list.end()) {
			average_sum += variables_list[*it];
		}
		else
		{
			throw std::overflow_error("Error variable not found");
		}
	}
		
	cout << average_sum << endl;

	return ret;
}

/**
* calculateAverage
*	Function that calculates the average of all parameters passed at command_parameters_list based on variables_list
*/
int calculateAverage(std::vector<std::string>& command_parameters_list, map<string, long>& variables_list)
{
	int ret = EXIT_FAILURE;

	long average_sum = 0;
	int average_count = 0;
	for (std::vector<std::string>::iterator it = command_parameters_list.begin(); it != command_parameters_list.end(); ++it) {
		if (variables_list.find(*it) != variables_list.end()) {
			average_sum += variables_list[*it];
			++average_count;
		}
		else
		{
			throw std::overflow_error("Error variable not found");
		}
	}

	if (command_parameters_list.size() == average_count) {
		cout << average_sum / average_count << endl;
		ret = EXIT_SUCCESS;
	}

	return ret;
}

/**
* parseCommandParameters - Method that parse command parameters inside brackets
* @param text String containing parameters list separated by sep.
* @param sep Separator character that will split parameters list
* @return vector containing parameters list splitted
*/
std::vector<std::string> parseCommandParameters(const std::string &text, char sep) {
	std::vector<std::string> tokens;
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

/**
* parseVariable - Method that try to parse string passed as a variable
*					The variable format is: variable_name=variable_value
*					This method can throw some exceptions during process that are catch on run method
*					overflow_error:	this exception is raised when the variable_value has more than 31 character
*									that is the maximum size of long type
*					domain_error:	this exception is raised when the variable_value does not have only numbers on it
* @param line String containing possible variable format.
* @param variables_list map of all variables that are stored and will be stored if variable is valid
* @return int value that tell if the string was parsed with success or not
*/
int parseVariable(std::string line, map<string, long>& variables_list)
{
	int ret = EXIT_FAILURE;
	size_t var_index = 0;
	if ((var_index = line.find(VARIABLE_TOKEN)) != string::npos) {

		// parse variable
		string s_var_name = line.substr(0, var_index);
		string s_var_value = line.substr(var_index + 1, line.length());

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

		ret = EXIT_SUCCESS;
	}

	return ret;
}

/**
* parseCommand - Method that try to parse string passed as a command that is search on command_list
*					The command format is: command_name(param1, param2, etc)
*					Also this method call execute method on command object
*					This method can throw some exceptions during process when call execute method from command object that are catch on run method
* @param line String containing possible command format.
* @param variables_list list of all variables already loaded
* @param commands_list list of all commands that can be processed
* @return int value that tell if the string was parsed with success or not
*/
int parseCommand(std::string line, std::map<std::string, long>& variables_list, command_map commands_list)
{
	int ret = EXIT_FAILURE;

	if (!commands_list.empty())
	{
		for (command_map::iterator itc = commands_list.begin(); itc != commands_list.end(); ++itc)
		{
			if (line.find(itc->first) != string::npos
				&& line[itc->first.length()] == COMMAND_START_TOKEN
				&& line[line.length() - 1] == COMMAND_END_TOKEN) {

				// parse command
				string command_parameters = line.substr(itc->first.length() + 1, line.length() - itc->first.length() - 1 - 1);
				std::vector<std::string> command_parameters_list = parseCommandParameters(command_parameters, COMMAND_PARAMETERS_SEP);

				if (!command_parameters_list.empty())
				{
					return (*itc->second)(command_parameters_list, variables_list);
				}
				else {
					throw std::overflow_error("Error command parameters list");
				}
			}
		}
	}

	return ret;
}

int process(string filename) {
	std::ifstream in_stream;
	in_stream.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	unsigned int line_number = 0;
	string line;
	map<string, long> variables_list;
	int response = EXIT_SUCCESS;
	command_map commands_list;

	commands_list[COMMAND_AVERAGE] = &calculateAverage;
	commands_list[COMMAND_SUM] = &calculateSum;

	try {
		// open file
		in_stream.open(filename);

		while (!in_stream.eof()) {
			
			++line_number;

			// read line in file
			getline(in_stream, line);

			// remove whitespaces from line
			line.erase(std::remove_if(line.begin(), line.end(), std::isspace), line.end());

			// check var_name=var_value
			if (parseVariable(line, variables_list) == EXIT_FAILURE 
				&& parseCommand(line, variables_list, commands_list) == EXIT_FAILURE)
			{
				throw std::overflow_error("Error variable or command not valid");
			}
		}
		// close file
		in_stream.close();
	}
	catch (const std::ifstream::failure) {
		cout << "Exception opening/reading/closing file" << endl;
		response = EXIT_FAILURE;
	}
	catch (const std::exception& e) {
		cout << "Line:" << line_number << ":" << e.what() << endl;
		response = EXIT_FAILURE;
	}

	return response;
}