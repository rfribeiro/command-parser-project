#include "CommandSum.h"
#include <iostream>

#define COMMAND_NAME "sum"

/**
* CommandSum default constructor that should call Command(std::string name) from base class with command name
*/
CommandSum::CommandSum() : Command(COMMAND_NAME)
{
}

/**
* ~CommandSum default destructor
*/
CommandSum::~CommandSum()
{
}

/**
* execute - Method that process the average from all variables passed in parameters_list
* @param parameters_list vector containing all parameters from this command.
* @param variables_list map object that all variables loaded are stored
* @return bool telling if the command was executed correct or not
*/
int CommandSum::execute(std::vector<std::string>& parameters_list, std::map<std::string, long>& variables_list)
{
	int response = EXIT_SUCCESS;

	long sum = 0;
	int average_count = 0;
	for (std::vector<std::string>::iterator itp = parameters_list.begin(); itp != parameters_list.end(); ++itp) {
		if (variables_list.find(*itp) != variables_list.end()) {
			sum += variables_list[*itp];
		}
		else {
			throw std::exception("Error variable not found");
		}
	}

	std::cout << sum << std::endl;

	return response;
}