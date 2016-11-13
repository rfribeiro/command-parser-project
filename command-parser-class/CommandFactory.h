#pragma once
#include "Command.h"

class CommandFactory
{
public:
	static std::vector<Command*> getCommandList();
};

