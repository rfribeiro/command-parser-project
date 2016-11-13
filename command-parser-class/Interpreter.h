#pragma once

#include "Command.h"
#include <string>
#include <vector>
#include <map>

/**
 *	Class Interpreter
 *	This Interpreter class is responsible to read and process the script file provided
 */
class Interpreter
{
public:
	Interpreter();
	~Interpreter();
	int run(std::string filename);
private:
	void loadCommandList();
	void unloadCommandList();
	int process(std::string line);
	int parseVariable(std::string line);
	int parseCommand(std::string line);
	std::vector<std::string> parseCommandParameters(const std::string &text, char sep);

	std::map<std::string, long> variables_list;
	std::vector<Command*> commands_list;
};

