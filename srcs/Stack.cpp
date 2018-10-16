#include "Stack.hpp"

Stack::Stack() {
	return;
}

Stack::Stack(Stack const &stack) {
	*this = stack;
}

Stack		&Stack::operator=(Stack const &stack) {
	this->c = stack.c;
	return *this;
}

Stack::~Stack() {
	return;
}

Stack::iterator		Stack::begin() {
	return this->c.rbegin();
}

Stack::iterator		Stack::end() {
	return this->c.rend();
}

IOperand const & Stack::at(size_type pos) {
	return *(this->c.at(this->size() - (pos + 1)));
}

void			Stack::pop() {
	if (this->empty() == true)
		throw StackSizeException();
	std::stack<const IOperand*>::pop();
}

void			Stack::dump() {
	for (Stack::iterator iterator = this->begin(); iterator != this->end(); iterator++) {
		std::cout << (*iterator)->toString() << std::endl;
	}
}

void			Stack::vdump() {
	for (Stack::iterator iterator = this->begin(); iterator != this->end(); iterator++) {
		std::cout << "type: " << (*iterator)->getType() << "\tvalue: " << (*iterator)->toString() << std::endl;
	}
}

void			Stack::assert(IOperand const & iOperand) {
	if (this->empty() == true)
		throw StackSizeException();
	if (this->at(0).getType() != iOperand.getType() || this->at(0).toString() != iOperand.toString()) {
		throw StackAssertException(true);
	}
}

void			Stack::print() {
	if (this->empty() == true)
		throw StackSizeException();
	if (this->at(0).getType() != Int8)
		throw StackAssertException(false);
	std::cout << static_cast<int8_t>(std::stoi(this->at(0).toString())) << std::endl;
}

void			Stack::add() {
	if (this->size() < 2)
		throw StackSizeException();
	IOperand const * iOperand = this->at(1) + this->at(0);
	this->insert(iOperand);
}

void			Stack::sub() {
	if (this->size() < 2)
		throw StackSizeException();
	IOperand const * iOperand = this->at(1) - this->at(0);
	this->insert(iOperand);
}

void			Stack::mul() {
	if (this->size() < 2)
		throw StackSizeException();
	IOperand const * iOperand = this->at(1) * this->at(0);
	this->insert(iOperand);
}

void			Stack::div() {
	if (this->size() < 2)
		throw StackSizeException();
	IOperand const * iOperand = this->at(1) / this->at(0);
	this->insert(iOperand);
}

void			Stack::mod() {
	if (this->size() < 2)
		throw StackSizeException();
	IOperand const * iOperand = this->at(1) % this->at(0);
	this->insert(iOperand);
}

void			Stack::max() {
	Stack::iterator finalIterator;
	double value;
	if (this->empty() == true) {
		throw StackSizeException();
	}
	finalIterator = this->begin();
	value = std::stod(this->at(0).toString());
	for (Stack::iterator iterator = this->begin() + 1; iterator != this->end(); iterator++) {
		if (std::stod((*iterator)->toString()) > value) {
			value = std::stod((*iterator)->toString());
			finalIterator = iterator;
		}
	}
	std::cout << (*finalIterator)->toString() << std::endl;
}

void			Stack::min() {
	Stack::iterator finalIterator;
	double value;
	if (this->empty() == true) {
		throw StackSizeException();
	}
	finalIterator = this->begin();
	value = std::stod(this->at(0).toString());
	for (Stack::iterator iterator = this->begin() + 1; iterator != this->end(); iterator++) {
		if (std::stod((*iterator)->toString()) < value) {
			value = std::stod((*iterator)->toString());
			finalIterator = iterator;
		}
	}
	std::cout << (*finalIterator)->toString() << std::endl;
}

void			Stack::drop() {
	while (this->empty() == false) {
		std::stack<const IOperand*>::pop();
	}
}

void			Stack::insert(IOperand const * iOperand) {
	this->pop();
	this->pop();
	std::stack<const IOperand*>::push(iOperand);
}

void			Stack::exit() {
	std::exit(EXIT_SUCCESS);
}

Stack::StackSizeException::StackSizeException() {
	return;
}

Stack::StackSizeException::~StackSizeException() throw() {
	return;
}

const char *Stack::StackSizeException::what() const throw() {
	return "StackSizeException: the number of element in the stack is too small for this action";
}

Stack::StackSizeException & Stack::StackSizeException::operator=(StackSizeException const &stackSizeException) {
	(void)stackSizeException;
	return *this;
}

Stack::StackSizeException::StackSizeException(StackSizeException const &stackSizeException) {
	*this = stackSizeException;
	return;
}


Stack::StackAssertException::StackAssertException() {
	return;
}

Stack::StackAssertException::StackAssertException(bool isAssertInstruction) : _isAssertInstruction(isAssertInstruction){
	return;
}

Stack::StackAssertException::~StackAssertException() throw() {
	return;
}

const char *Stack::StackAssertException::what() const throw() {
	if (this->_isAssertInstruction == true)
		return "StackAssertException: The assert is false";
	return "StackAssertException: The first element on the stack is not an int8 value";
}

Stack::StackAssertException & Stack::StackAssertException::operator=(StackAssertException const &stackAssertException) {
	(void)stackAssertException;
	return *this;
}

Stack::StackAssertException::StackAssertException(StackAssertException const &stackAssertException) {
	*this = stackAssertException;
	return;
}
