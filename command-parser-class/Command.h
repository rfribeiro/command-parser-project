#pragma once

#include <string>
#include <map>
#include <vector>

/**
* Command
*	Base virtual class implements the interface of supported commands
*/
class Command
{
public:
	Command(std::string name);
	~Command();
	/**
	* execute
	*	pure virtual method that should be implemented by childs
	* @param parameters_list vector containing all parameters from this command.
	* @param variables_list map object that all variables loaded are stored
	* @return bool telling if the command was executed correct or not
	*/
	virtual int execute(std::vector<std::string>& parameters_list, std::map<std::string, long>& variables_list) = 0;
	const std::string& getName();
	void setName(std::string name);
private:
	std::string m_name;
};

