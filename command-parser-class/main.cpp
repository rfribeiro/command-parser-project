#include <iostream>
#include <string>

#include "Interpreter.h"

int main(int argc, char *argv[]) {
	std::string filename;
	try {
		if (argc > 1 && argv[1] != NULL) {
			filename = argv[1];
		}
		else {
			std::cin >> filename;
		}

		Interpreter i;
		i.run(filename);
	}
	catch (const std::exception& e) {
		std::cout << "Error unknown file name" << " : " << e.what() << std::endl;
	}
}