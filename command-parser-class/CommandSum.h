#pragma once
#include "Command.h"

/**
* CommandSum
*	Class that calculates the sum from all parameters passed
*/
class CommandSum :
	public Command
{
public:
	CommandSum();
	~CommandSum();
	virtual int execute(std::vector<std::string>& parameters_list, std::map<std::string, long>& variables_list);
};

