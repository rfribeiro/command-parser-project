#pragma once

#include <string>
#include <map>
#include <vector>

class Command
{
public:
	Command(std::string name);
	~Command();
	virtual bool execute(std::vector<std::string>& parameters_list, std::map<std::string, long>& variables_list) = 0;
	const std::string& getName();
	void setName(std::string name);
private:
	std::string m_name;
};

