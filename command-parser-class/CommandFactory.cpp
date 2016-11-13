#include "CommandFactory.h"
#include "CommandAverage.h"
#include "CommandSum.h"

/**
* getCommandList - Method that initialize and store all command supported
* @return std::vector<Command*> return a list with all commands supported
*/
std::vector<Command*> CommandFactory::getCommandList()
{
	std::vector<Command*> commandList;

	commandList.push_back(new CommandAverage());
	commandList.push_back(new CommandSum());

	return commandList;
}
