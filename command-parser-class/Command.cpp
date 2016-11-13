#include "Command.h"
#include <iostream>

Command::Command(std::string name) : m_name(name)
{
}

Command::~Command()
{
}

const std::string& Command::getName()
{
	return m_name;
}

void Command::setName(std::string name)
{
	m_name = name;
}


