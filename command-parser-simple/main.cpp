#include <iostream>
#include "command-parser-simple.h"

int main(int argc, char *argv[]) {
	std::string file_name;
	try {
		if (argc > 1 && argv[1] != NULL) {
			file_name = argv[1];
		}
		else {
			std::cin >> file_name;
		}

		read_and_execute(file_name);
	}
	catch (const std::exception& e) {
		std::cout << "Error unknown file name" << " : " << e.what() << std::endl;
	}
}