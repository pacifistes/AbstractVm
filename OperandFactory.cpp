#include "OperandFactory.hpp"

OperandFactory::OperandFactory() {
	return;
}

OperandFactory::~OperandFactory() {
	return;
}

OperandFactory::OperandFactory(OperandFactory const &operandFactory) {
	*this = operandFactory;
	return;
}

OperandFactory & OperandFactory::operator=(OperandFactory const &operandFactory) {
	(void)operandFactory;
	return *this;
}

IOperand const * OperandFactory::createOperand(eOperandType type, std::string const & value) const {
	IOperand const * (OperandFactory::*arrayOfPointer[5])(std::string const &value) const = { &OperandFactory::createInt8,
																						&OperandFactory::createInt16,
																						&OperandFactory::createInt32,
																						&OperandFactory::createFloat,
																						&OperandFactory::createDouble };
	return (this->*arrayOfPointer[type])(value);//CAST MAYBE
}

IOperand const * OperandFactory::createInt8(std::string const & value) const {
	int intValue = 0;
	char const *error = "the value must be an int8 value";
	try {
		intValue = std::stoi(value);
	} catch(const std::out_of_range& e) {
		
		throw new OverflowException(error);
	}
	if (intValue < INT8_MIN || intValue > INT8_MAX)
		throw new OverflowException(error);
	eOperandType type = Int8;
	return new Operand<char>(type, static_cast<char>(intValue));
}

IOperand const * OperandFactory::createInt16(std::string const & value) const {
	int intValue = 0;
	char const *error = "the value must be an int16 value";
	try {
		intValue = std::stoi(value);
	} catch(const std::out_of_range& e) {
		throw new OverflowException(error);
	}
	if (intValue < INT16_MIN || intValue > INT16_MAX)
		throw new OverflowException(error);
	eOperandType type = Int16;
	return new Operand<short>(type, static_cast<short>(intValue));
}

IOperand const * OperandFactory::createInt32(std::string const & value) const {
	int intValue = 0;
	char const *error = "the value must be an int32 value";
	try {
		intValue = std::stoi(value);
	} catch(const std::out_of_range& e) {
		throw new OverflowException(error);
	}
	eOperandType type = Int32;
	return new Operand<int>(type, intValue);
}

IOperand const * OperandFactory::createFloat(std::string const & value) const {
	float floatValue = 0;
	char const *error = "the value must be a float value";
	try {
		floatValue = std::stof(value);
	} catch(const std::out_of_range& e) {
		throw new OverflowException(error);
	}
	eOperandType type = Float;
	return new Operand<float>(type, floatValue);
}

IOperand const * OperandFactory::createDouble(std::string const & value) const {
	double doubleValue = 0;
	char const *error = "the value must be a double value";
	try {
		doubleValue = std::stod(value);
	} catch(const std::out_of_range& e) {
		throw new OverflowException(error);
	}
	eOperandType type = Double;
	return new Operand<double>(type, doubleValue);
}


OperandFactory::OverflowException::OverflowException(char const *error) : _error(error) {
	return;
}

OperandFactory::OverflowException::~OverflowException(void) throw() {
	return;
}

OperandFactory::OverflowException::OverflowException(OverflowException const &overflowException) {
	*this = overflowException;
	return;
}

OperandFactory::OverflowException & OperandFactory::OverflowException::operator=(OverflowException const &overflowException) {
	(void)overflowException;
	return *this;
}

OperandFactory::OverflowException::OverflowException(void) {
	return;
}

const char *OperandFactory::OverflowException::what() const throw() {
	return this->_error;
}
