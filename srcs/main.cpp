#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include "StackManager.hpp"

std::vector<std::string> getLinesFromStdin() {
	std::vector<std::string> lines;
	std::string line;
	while (line != ";;") {
		std::getline(std::cin, line);
		if (std::cin.bad() || std::cin.eof() || std::cin.fail())
			return lines;
		if (line != ";;")
			lines.push_back(line);
	}
	return lines;	
}

std::vector<std::string> getLinesFromFile(char *fileName) {
	std::vector<std::string> lines;
	std::string line;
	std::ifstream file(fileName);

	if (file) {
		while (std::getline(file, line)) {
			lines.push_back(line);
		}
		file.close();
	}
	return lines;
}

int main(int ac, char **av) {
	StackManager *stackManager = new StackManager();
	std::vector<std::string> lines;
	switch (ac) {
		case 1:
			lines = getLinesFromStdin();
			break;
		case 2:
			lines = getLinesFromFile(av[1]);
			break;
		default:
			std::cerr << "Usage: ./abstract [file]." << std::endl;
			delete stackManager;
			return EXIT_FAILURE;
	}
	if (lines.empty()) {
		std::cerr << "\e[1;91m" << "error: " << "\e[0;0m" << "\e[1;1m" << " problem while reading the file or the input from terminal." <<  "\e[0;0m" << std::endl;
		return EXIT_FAILURE;
	}
	for (auto line : lines) {
		if (!line.empty()) {
			stackManager->runInstruction(line);
		}
	}
	std::cerr << "\e[1;91m" << "error: " << "\e[0;0m" << "\e[1;1m" << "No exit instruction found." << "\e[0;0m" << std::endl;
	delete stackManager;
	return EXIT_FAILURE;
}