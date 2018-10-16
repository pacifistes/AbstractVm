#ifndef STACK_MANAGER_HPP
# define STACK_MANAGER_HPP

# include <string>
# include <regex>
# include <map>
# include <iostream>
# include <typeinfo>
# include <stdexcept>
# include "OperandFactory.hpp"
# include "IOperand.hpp"
# include "Stack.hpp"

class StackManager {

	public:
		StackManager();
		~StackManager();
		void	push(std::string type, std::string value);
		void	assert(std::string type, std::string value);
		void	runInstruction(std::string instruction);
	private:
		StackManager(StackManager const &stackManager);
		StackManager		&operator=(StackManager const &stackManager);
		IOperand const * getIOperand(std::string type, std::string value);
		OperandFactory _operandFactory;
		Stack _stack;
		typedef std::map<std::string, void (Stack::*)(void)> mapStack;
		typedef std::map<std::string, void (StackManager::*)(std::string, std::string)> mapStackManager;
		typedef std::map<std::string, eOperandType> mapEOperandType;
		static int lineIterator;
		static mapStack initMapStack();
		static mapStackManager initMapStackManager();
		static mapEOperandType initMapEOperandType();
		static mapStack _mapOfPointerToStackMember;
		static mapStackManager _mapOfPointerToStackManagerMember;
		static mapEOperandType _mapEOperandType;
};

#endif