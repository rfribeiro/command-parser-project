#include "CommandAverage.h"
#include <iostream>


CommandAverage::~CommandAverage()
{
}

bool CommandAverage::execute(std::vector<std::string>& parameters_list, std::map<std::string, long>& variables_list)
{
	bool response = false;

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
		response = true;
	}

	return response;
}