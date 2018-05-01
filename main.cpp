#include <vector>
#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include "OperandFactory.hpp"
// Rajoute un type
// Rajoute un operateur (pow)
// afficher toutes les erreurs

std::vector<std::string> getLinesFromStdin() {
	std::vector<std::string> lines = NULL;
	std::string line = NULL;
	while (line != ";;") {
		std::getline(std::cin, line);
		if (std::cin.bad() || std::cin.eof() || std::cin.fail())
			return NULL;
		if (line != ";;")
			lines.push_back(line);
	}
	return lines;	
}

std::vector<std::string> getLinesFromFile(char *fileName) {
	std::vector<std::string> lines = NULL;
	std::string line = NULL;
	std::ifstream file(fileName);

	if (file) {
		while (std::getline(file, line)) {
			lines.push_back(line);
		}
		file.close();
	}
	return lines;
}


// createOperant(string) {
// 	getType()
// 	create
// }

// Push(string) {
// 	createOperant()
// 	stack.insert
// }

// Assert() {
// 	createOperant()
// 	stackAssert()
// }

int main(int ac, char **av) {
	OperandFactory* operandFactory = new OperandFactory();
	std::vector<std::string> lines;
	std::vector<Hash> hashList;
	push_back();
	push_back();
	push_back();
	push_back();
	push_back();
	push_back();
	push_back();
	push_back();
	push_back();
	push_back();
	push_back();
	push_back();
	push_back();
	push_back();
	switch (ac) {
		case 1:
			lines = getLinesFromStdin();
			break;
		case 2:
			lines = getLinesFromFile(av[1]);
			break;
		default:
			std::cout << "usage: ./abstract [file]" << std::endl;
			return EXIT_FAILURE;
	}
	if (lines == NULL) {
		//Do something ...
		return EXIT_FAILURE;
	}
	for (std::vector<string>::iterator it = lines.begin(); it != lines.end(); it++) { //*it for the string

	}
	return EXIT_FAILURE;
	// return EXIT_SUCCESS;
}



	// std::string regexs { '/^push int8\([-]?[\d]+\)(?:;(.*))?$/',
	// 					'/^push int16\([-]?[\d]+\)(?:;(.*))?$/',
	// 					'/^push int32\([-]?[\d]+\)(?:;(.*))?$/',
	// 					'/^push float\([-]?[\d]+\.[\d]+\)(?:;(.*))?$/',
	// 					'/^push double\([-]?[\d]+\.[\d]+\)(?:;(.*))?$/',
	// 					'/^pop(?:;(.*))?$/', '/^dump(?:;(.*))?$/',
	// 					'/^add(?:;(.*))?$/', '/^sub(?:;(.*))?$/',
	// 					'/^mul(?:;(.*))?$/', '/^div(?:;(.*))?$/',
	// 					'/^mod(?:;(.*))?$/', '/^print(?:;(.*))?$/',
	// 					'/^exit(?:;(.*))?$/', '/^;;$/'}