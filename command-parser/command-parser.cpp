#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>

using namespace std;

#define VARIABLE_TOKEN		'='
#define COMMAND_START_TOKEN '('
#define COMMAND_END_TOKEN	')'

int main(int argc, char *argv[]) {

	std::ifstream in_stream;
	in_stream.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	unsigned int line_number = 0;
	string line;
	vector<string> commands_list;
	map<string, long> variables_list;
	string file_name;

	string command = "average";
	
	try {
		if (argc > 1 && argv[1] != NULL) {
			file_name = argv[1];
		}
		else {
			cin >> file_name;
		}

		// open file
		in_stream.open(file_name);

		while (!in_stream.eof()) {
			size_t var_index = 0;
			++line_number;

			// read line in file
			getline(in_stream, line);

			// remove whitespaces from line
			line.erase(std::remove_if(line.begin(), line.end(), std::isspace), line.end());

			// check var_name=var_value
			if ((var_index = line.find(VARIABLE_TOKEN)) != string::npos) {

				// parse variable
				string s_var_name = line.substr(0, var_index);
				string s_var_value = line.substr(var_index + 1, line.length());

				if (s_var_value.length() >= std::numeric_limits<long>::digits) {
					throw std::overflow_error("");
				}

				long l_var_value = std::atoi(s_var_value.c_str());

				variables_list[s_var_name] = l_var_value;

				// check "command(...)"
			} else if (line.find(command) != string::npos
				&& line[command.length()] == COMMAND_START_TOKEN
				&& line[line.length() - 1] == COMMAND_END_TOKEN) {

				// parse command
				string command_variables_list = line.substr(command.length() + 1, line.length() - command.length() - 1 - 1);
				cout << command_variables_list;
			}
		}
		// close file
		in_stream.close();

	}
	catch (const std::overflow_error& o) {
		cerr << "Error variable value overflow" << " : " << line_number << endl;
	} catch (const std::out_of_range& o) {
		cerr << "Error parsing command string" << " : " << line_number  << endl;
	} catch (const std::ifstream::failure& e) {
		cerr << "Exception opening/reading/closing file" << endl;
	} catch (const std::exception& e) {
		cerr << "Error unknown" << endl;
	}
}