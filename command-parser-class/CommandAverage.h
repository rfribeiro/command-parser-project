#pragma once
#include "Command.h"
class CommandAverage :
	public Command
{
public:
	CommandAverage() : Command("average") {};
	~CommandAverage();
	virtual bool execute(std::vector<std::string>& parameters_list, std::map<std::string, long>& variables_list);
};

