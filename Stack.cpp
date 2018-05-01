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
	return this->c.begin();
}

Stack::iterator		Stack::end() {
	return this->c.end();
}

IOperand const & Stack::at(size_type pos) {
	return *(this->c.at(pos));
}

void			Stack::pop() {
	if (this->empty() == true)
		throw new StackSizeException();
	this->pop();
}

void			Stack::dump() {
	for (Stack::iterator iterator = this->begin(); iterator != this->end(); iterator++) {
		std::cout << (*iterator)->toString() << std::endl;
	}
}

void			Stack::assert(IOperand const & iOperand) {
	if (this->empty() == true)
		throw new StackSizeException();
	if (this->at(0).getType() != iOperand.getType() || this->at(0).toString() != iOperand.toString())
		throw new StackAssertException(true);
}

void			Stack::print() {
	if (this->empty() == true)
		throw new StackSizeException();
	if (this->at(0).getType() != Int8)
		throw new StackAssertException(true);
	std::cout << this->at(0).toString() << std::endl;
}

void			Stack::add() {
	if (this->size() < 2)
		throw new StackSizeException();
	IOperand const * iOperand = this->at(0) + this->at(1);
	this->insert(iOperand);
}

void			Stack::sub() {
	if (this->size() < 2)
		throw new StackSizeException();
	IOperand const * iOperand = this->at(0) - this->at(1);
	this->insert(iOperand);
}

void			Stack::mul() {
	if (this->size() < 2)
		throw new StackSizeException();
	IOperand const * iOperand = this->at(0) * this->at(1);
	this->insert(iOperand);
}

void			Stack::div() {
	if (this->size() < 2)
		throw new StackSizeException();
	IOperand const * iOperand = this->at(0) / this->at(1);
	this->insert(iOperand);
}

void			Stack::mod() {
	if (this->size() < 2)
		throw new StackSizeException();
	IOperand const * iOperand = this->at(0) % this->at(1);
	this->insert(iOperand);
}

void			Stack::insert(IOperand const * iOperand) {
	this->pop();
	this->pop();
	this->push(iOperand);
}


Stack::StackSizeException::StackSizeException() {
	return;
}

Stack::StackSizeException::~StackSizeException() throw() {
	return;
}

const char *Stack::StackSizeException::what() const throw() {
	return "The number of element in the stack is too small for this action";
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
		return "The assert is false";
	return "The first element on the stack is not an int8 value";
}

Stack::StackAssertException & Stack::StackAssertException::operator=(StackAssertException const &stackAssertException) {
	(void)stackAssertException;
	return *this;
}

Stack::StackAssertException::StackAssertException(StackAssertException const &stackAssertException) {
	*this = stackAssertException;
	return;
}
