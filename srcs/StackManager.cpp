#include "StackManager.hpp"

StackManager::StackManager() {
	return;
}

StackManager::StackManager(StackManager const &stackManager) {
	*this = stackManager;
}

StackManager		&StackManager::operator=(StackManager const &stackManager) {
	(void)stackManager;
	return *this;
}

StackManager::~StackManager() {
	return;
}

IOperand const * StackManager::getIOperand(std::string type, std::string value) {
	return this->_operandFactory.createOperand(this->_mapEOperandType[type], value);
}

void	StackManager::push(std::string type, std::string value) {
	IOperand const * iOperand = this->getIOperand(type, value);
	this->_stack.push(iOperand);
}

void	StackManager::assert(std::string type, std::string value) {
	IOperand const * iOperand = this->getIOperand(type, value);
	this->_stack.assert(*iOperand);
}

void	StackManager::runInstruction(std::string instruction) {
	std::cmatch match;
	StackManager::lineIterator += 1;
	for(auto mapStackManager : this->_mapOfPointerToStackManagerMember) {
		if (std::regex_search(instruction.c_str(), match, std::regex(mapStackManager.first))) {
			try {
				(this->*mapStackManager.second)(match[1], match[2]);
			}
			catch (std::exception const & e) {
				std::cerr << "\e[1;1m" << "line:" << StackManager::lineIterator << ": "
				<< "\e[1;91m" << "error: " << "\e[0;0m" << "\e[1;1m" << e.what() << " : " << std::endl << "\e[0;0m" << "\e[1;32m" << "> "
				<< "\e[0;0m" << instruction << std::endl;
			}
			return;
		}
	}
	for (auto mapStack : this->_mapOfPointerToStackMember) {
		if (std::regex_match(instruction, std::regex(mapStack.first))) {
			try {
				(this->_stack.*(mapStack.second))();
			}
			catch (std::exception const & e) {
				std::cerr << "\e[1;1m" << "line:" << StackManager::lineIterator << ": "
				<< "\e[1;91m" << "error: " << "\e[0;0m"  << "\e[1;1m" << e.what() << " : " << std::endl << "\e[0;0m" << "\e[1;32m" << "> "
				<< "\e[0;0m" << instruction << std::endl;
			}
			return;
		}
	}
	if (!std::regex_match(instruction, std::regex("^(?:;.*)$"))) {
		std::cerr << "\e[1;1m" << "line:" << StackManager::lineIterator << ": "
		<< "\e[1;91m" << "error: " << "\e[0;0m" << "\e[1;1m" << "invalid instruction :" << std::endl
		<< "\e[0;0m" << "\e[1;32m" << "> " << "\e[0;0m" << instruction << std::endl;
	}
}

StackManager::mapStack StackManager::initMapStack() {
	StackManager::mapStack mapOfPointerToStackMember;
	mapOfPointerToStackMember["^pop\\s*(?:;.*)?$"] = &Stack::pop;
	mapOfPointerToStackMember["^dump\\s*(?:;.*)?$"] = &Stack::dump;
	mapOfPointerToStackMember["^vdump\\s*(?:;.*)?$"] = &Stack::vdump;
	mapOfPointerToStackMember["^add\\s*(?:;.*)?$"] = &Stack::add;
	mapOfPointerToStackMember["^sub\\s*(?:;.*)?$"] = &Stack::sub;
	mapOfPointerToStackMember["^mul\\s*(?:;.*)?$"] = &Stack::mul;
	mapOfPointerToStackMember["^div\\s*(?:;.*)?$"] = &Stack::div;
	mapOfPointerToStackMember["^mod\\s*(?:;.*)?$"] = &Stack::mod;
	mapOfPointerToStackMember["^max\\s*(?:;.*)?$"] = &Stack::max;
	mapOfPointerToStackMember["^min\\s*(?:;.*)?$"] = &Stack::min;
	mapOfPointerToStackMember["^drop\\s*(?:;.*)?$"] = &Stack::drop;
	mapOfPointerToStackMember["^print\\s*(?:;.*)?$"] = &Stack::print;
	mapOfPointerToStackMember["^exit\\s*(?:;.*)?$"] = &Stack::exit;
	return mapOfPointerToStackMember;
}

StackManager::mapStackManager StackManager::initMapStackManager() {
	StackManager::mapStackManager mapOfPointerToStackManagerMember;
	mapOfPointerToStackManagerMember["^push (int(?:8|16|32|64))\\(([-]?[\\d]+)\\)\\s*(?:;.*)?$"] = &StackManager::push;
	mapOfPointerToStackManagerMember["^push (float|double)\\(([-]?[\\d]+\\.[\\d]+)\\)\\s*(?:;.*)?$"] = &StackManager::push;
	mapOfPointerToStackManagerMember["^assert (int(?:8|16|32|64))\\(([-]?[\\d]+)\\)\\s*(?:;.*)?$"] = &StackManager::assert;
	mapOfPointerToStackManagerMember["^assert (float|double)\\(([-]?[\\d]+\\.[\\d]+)\\)\\s*(?:;.*)?$"] = &StackManager::assert;
	return mapOfPointerToStackManagerMember;
}

StackManager::mapEOperandType StackManager::initMapEOperandType() {
	StackManager::mapEOperandType mapEOperandType;
	mapEOperandType["int8"] = Int8;
	mapEOperandType["int16"] = Int16;
	mapEOperandType["int32"] = Int32;
	mapEOperandType["int64"] = Int64;
	mapEOperandType["float"] = Float;
	mapEOperandType["double"] = Double;
	return mapEOperandType;
}

int StackManager::lineIterator = 0;
StackManager::mapStack StackManager::_mapOfPointerToStackMember = initMapStack();
StackManager::mapStackManager StackManager::_mapOfPointerToStackManagerMember = initMapStackManager();
StackManager::mapEOperandType StackManager::_mapEOperandType = initMapEOperandType();