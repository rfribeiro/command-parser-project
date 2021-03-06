#pragma once
#include "Command.h"

/**
* CommandAverage
*	Class that calculates the average from all parameters passed
*/
class CommandAverage :
	public Command
{
public:
	CommandAverage();
	~CommandAverage();
	virtual int execute(std::vector<std::string>& parameters_list, std::map<std::string, long>& variables_list);
};

