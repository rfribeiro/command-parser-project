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
#define COMMAND_PARAMETERS_SEP ','
#define NUMBER_SEQUENCE "0123456789"

std::vector<std::string> split(const std::string &text, char sep) {
	std::vector<std::string> tokens;
	std::size_t start = 0, end = 0;
	while ((end = text.find(sep, start)) != std::string::npos) {
		if (end != start) {
			tokens.push_back(text.substr(start, end - start));
		}
		start = end + 1;
	}
	if (end != start) {
		tokens.push_back(text.substr(start));
	}
	return tokens;
}

string command = "average";

int read_and_execute(string filename) {
	std::ifstream in_stream;
	in_stream.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	unsigned int line_number = 0;
	string line;
	vector<string> commands_list;
	map<string, long> variables_list;
	int response = EXIT_SUCCESS;

	try {
		// open file
		in_stream.open(filename);

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
				} else if (s_var_value.find_first_not_of(NUMBER_SEQUENCE) != std::string::npos) {
					throw std::domain_error("");
				}

				long l_var_value = std::atoi(s_var_value.c_str());

				variables_list[s_var_name] = l_var_value;

				// check "command(...)"
			}
			else if (line.find(command) != string::npos
				&& line[command.length()] == COMMAND_START_TOKEN
				&& line[line.length() - 1] == COMMAND_END_TOKEN) {

				// parse command
				string command_parameters = line.substr(command.length() + 1, line.length() - command.length() - 1 - 1);
				std::vector<std::string> command_parameters_list = split(command_parameters, COMMAND_PARAMETERS_SEP);

				if (!command_parameters_list.empty()) {
					long average_sum = 0;
					int average_count = 0;
					for (std::vector<std::string>::iterator it = command_parameters_list.begin(); it != command_parameters_list.end(); ++it) {
						if (variables_list.find(*it) != variables_list.end()) {
							average_sum += variables_list[*it];
							++average_count;
						}
						else {
							cout << "Line:" << line_number << ":Error variable not found" << endl;
							response = EXIT_FAILURE;
							break;
						}
					}

					if (command_parameters_list.size() == average_count) {
						cout << average_sum / average_count << endl;
					}
					else {
						break;
					}
				}
				else {
					cout << "Line:" << line_number << ":Error command parameters list" << endl;
					response = EXIT_FAILURE;
					break;
				}
			}
			else {
				cout << "Line:" << line_number << ":Error variable or command not valid" << endl;
				response = EXIT_FAILURE;
				break;
			}
		}
		// close file
		in_stream.close();
	}
	catch (const std::domain_error) {
		cout << "Line:" << line_number << ":Error variable not a numeric value" << endl;
		response = EXIT_FAILURE;
	}
	catch (const std::overflow_error) {
		cout << "Line:" << line_number << ":Error variable value overflow" << endl;
		response = EXIT_FAILURE;
	}
	catch (const std::out_of_range) {
		cout << "Line:" << line_number << ":Error parsing command string" << endl;
		response = EXIT_FAILURE;
	}
	catch (const std::ifstream::failure) {
		cout << "Exception opening/reading/closing file" << endl;
		response = EXIT_FAILURE;
	}
	catch (const std::exception& e) {
		cout << "Error unknown" << endl;
		cout << "Details: " << e.what() << endl;
		response = EXIT_FAILURE;
	}

	return response;
}