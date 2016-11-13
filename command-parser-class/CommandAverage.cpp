#include "CommandAverage.h"
#include <iostream>

#define COMMAND_NAME "average"

/**
* CommandAverage default constructor that should call Command(std::string name) from base class with command name
*/
CommandAverage::CommandAverage() : Command(COMMAND_NAME)
{
}

/**
* ~CommandAverage default destructor
*/
CommandAverage::~CommandAverage()
{
}

/**
* execute - Method that process the average from all variables passed in parameters_list
* @param parameters_list vector containing all parameters from this command.
* @param variables_list map object that all variables loaded are stored
* @return int value telling if the command was executed correct or not
*/
int CommandAverage::execute(std::vector<std::string>& parameters_list, std::map<std::string, long>& variables_list)
{
	int response = EXIT_FAILURE;

	long average_sum = 0;
	int average_count = 0;
	for (std::vector<std::string>::iterator itp = parameters_list.begin(); itp != parameters_list.end(); ++itp) {
		if (variables_list.find(*itp) != variables_list.end()) {
			average_sum += variables_list[*itp];
			++average_count;
		}
		else {
			throw std::exception("Error variable not found");
		}
	}

	if (parameters_list.size() == average_count) {
		std::cout << average_sum / average_count << std::endl;
		response = EXIT_SUCCESS;
	}

	return response;
}