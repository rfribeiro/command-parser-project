#include "Command.h"
#include <iostream>

/**
* Command 
* @param name that is the command name
*/
Command::Command(std::string name) : m_name(name)
{
}

/**
* ~Command default destructor
*/
Command::~Command()
{
}

/**
* getName return command name
* @return string containing the command name
*/
const std::string& Command::getName()
{
	return m_name;
}

/**
* setName set command name
* @param name name of the command
*/
void Command::setName(std::string name)
{
	m_name = name;
}


