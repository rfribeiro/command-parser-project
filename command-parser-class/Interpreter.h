#pragma once

#include "Command.h"
#include <string>
#include <vector>
#include <map>

//using namespace std;

class Interpreter
{
public:
	Interpreter();
	~Interpreter();
	int run(std::string filename);
private:
	void loadCommandList();
	void unloadCommandList();
	bool parseVariable(std::string line);
	bool parseCommand(std::string line);
	std::vector<std::string> parseCommandParameters(const std::string &text, char sep);

	std::map<std::string, long> variables_list;
	std::vector<Command*> commands_list;
};

