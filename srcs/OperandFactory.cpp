#include "OperandFactory.hpp"
#include <iostream>
#include <limits>
#include <iomanip>
#include <cstdint>
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
	IOperand const * (OperandFactory::*arrayOfPointer[6])(std::string const &value) const = { &OperandFactory::createInt8,
																						&OperandFactory::createInt16,
																						&OperandFactory::createInt32,
																						&OperandFactory::createInt64,
																						&OperandFactory::createFloat,
																						&OperandFactory::createDouble };
	return (this->*arrayOfPointer[static_cast<int>(type)])(value);
}

double OperandFactory::convertValue(eOperandType type, std::string const & value) {
	double doubleValue;
	std::ostringstream stream;
	stream << "OverflowException: the value must be an " << type << " value";
	std::string str =  stream.str();
	char const *error = str.c_str();
	try {
		doubleValue = std::stod(value);
	} catch(const std::out_of_range& e) {
		throw OverflowException(error);
	}
	if (doubleValue < OperandFactory::_mapMin[type] || doubleValue > OperandFactory::_mapMax[type]) {
		throw OverflowException(error);
	}
	return doubleValue;
}

IOperand const * OperandFactory::createInt8(std::string const & value) const {
	return new Operand<int8_t>(Int8, static_cast<int8_t>(this->convertValue(Int8, value)));
}

IOperand const * OperandFactory::createInt16(std::string const & value) const {
	return new Operand<int16_t>(Int16, static_cast<int16_t>(this->convertValue(Int16, value)));
}

IOperand const * OperandFactory::createInt32(std::string const & value) const {
	return new Operand<int32_t>(Int32, static_cast<int32_t>(this->convertValue(Int32, value)));
}

IOperand const * OperandFactory::createInt64(std::string const & value) const {
	return new Operand<int64_t>(Int64, static_cast<int64_t>(this->convertValue(Int64, value)));
}

IOperand const * OperandFactory::createFloat(std::string const & value) const {
	return new Operand<float>(Float, static_cast<float>(this->convertValue(Float, value)));
}

IOperand const * OperandFactory::createDouble(std::string const & value) const {
	return new Operand<double>(Double, this->convertValue(Double, value));
}


OperandFactory::OverflowException::OverflowException(char const *error) : runtime_error(error), _error(error) {
	return;
}

OperandFactory::OverflowException::~OverflowException(void) throw() {
	return;
}

OperandFactory::OverflowException::OverflowException(OverflowException const &overflowException) : runtime_error(overflowException._error) {
	*this = overflowException;
	return;
}

OperandFactory::OverflowException & OperandFactory::OverflowException::operator=(OverflowException const &overflowException) {
	(void)overflowException;
	return *this;
}

OperandFactory::OverflowException::OverflowException(void) : runtime_error("OverflowException : the value isn't good") {
	return;
}

std::map<eOperandType const, double const> OperandFactory::initMapMin() {
	std::map<eOperandType const, double const> mapMin = {
		{Int8, static_cast<double>(std::numeric_limits<int8_t>::lowest())},
		{Int16, static_cast<double>(std::numeric_limits<int16_t>::lowest())},
		{Int32, static_cast<double>(std::numeric_limits<int32_t>::lowest())},
		{Int64, static_cast<double>(std::numeric_limits<int64_t>::lowest())},
		{Float, static_cast<double>(std::numeric_limits<float>::lowest())},
		{Double, static_cast<double>(std::numeric_limits<double>::lowest())}
	};
	return mapMin;
}

std::map<eOperandType const, double const> OperandFactory::initMapMax() {
	std::map<eOperandType const, double const> mapMax = {
		{Int8, static_cast<double>(std::numeric_limits<int8_t>::max())},
		{Int16, static_cast<double>(std::numeric_limits<int16_t>::max())},
		{Int32, static_cast<double>(std::numeric_limits<int32_t>::max())},
		{Int64, static_cast<double>(std::numeric_limits<int64_t>::max())},
		{Float, static_cast<double>(std::numeric_limits<float>::max())},
		{Double, static_cast<double>(std::numeric_limits<double>::max())}
	};
	return mapMax;
}

std::map<eOperandType const, double const> OperandFactory::_mapMin = initMapMin();
std::map<eOperandType const, double const> OperandFactory::_mapMax = initMapMax();
