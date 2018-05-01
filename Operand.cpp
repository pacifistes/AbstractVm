# include "Operand.hpp"

template<typename T> Operand<T>::Operand(eOperandType type, T value) : _type(type), _value(value), _sValue(std::to_string(value)) {
	return;
}

template<typename T> Operand<T>::~Operand() {
	return;
}

template<typename T> int Operand<T>::getPrecision(void) const {
	return this->_type;//a voir si je dois cast
}

template<typename T> eOperandType Operand<T>::getType(void) const {
	return this->_type;
}


template<typename T> eOperandType Operand<T>::getPriorityType(eOperandType const & firstType, eOperandType const & secondType) const {
	if (firstType < secondType)
		return firstType;
	return secondType;
}

template<typename T> IOperand const * Operand<T>::operator+(IOperand const & rhs) const {
	eOperandType type = getPriorityType(this->getType()	, rhs.getType());
	OperandFactory operandFactory;
	
	return operandFactory.createOperand(type, std::to_string(this->_value + std::stod(rhs.toString())));
}

template<typename T> IOperand const * Operand<T>::operator-(IOperand const & rhs) const {
	OperandFactory operandFactory;
	eOperandType type = getPriorityType(this->getType()	, rhs.getType());
	return operandFactory.createOperand(type, std::to_string(this->_value - std::stod(rhs.toString())));
}

template<typename T> IOperand const * Operand<T>::operator*(IOperand const & rhs) const {
	OperandFactory operandFactory;
	eOperandType type = getPriorityType(this->getType()	, rhs.getType());
	return operandFactory.createOperand(type, std::to_string(this->_value * std::stod(rhs.toString())));
}

template<typename T> IOperand const * Operand<T>::operator/(IOperand const & rhs) const {
	OperandFactory operandFactory;
	eOperandType type = getPriorityType(this->getType()	, rhs.getType());
	if (std::stod(rhs.toString()) == 0) {
		throw new ArithmeticException();
	}
	return operandFactory.createOperand(type, std::to_string(this->_value / std::stod(rhs.toString())));
}

template<typename T> IOperand const * Operand<T>::operator%(IOperand const & rhs) const {
	OperandFactory operandFactory;
	eOperandType type = getPriorityType(this->_type, rhs.getType());
	if (std::stod(rhs.toString()) == 0) {
		throw new ArithmeticException();
	}
	return operandFactory.createOperand(type, std::to_string(std::fmod(this->_value, std::stod(rhs.toString()))));
}

template<typename T> std::string const & Operand<T>::toString(void) const {
	
	return this->_sValue;
}


template<typename T> Operand<T>::Operand() : _type(Int32), _value(0) {
	return;
}

template<typename T> Operand<T>::Operand(Operand const &operand) {
	*this = operand;
	return;
}

template<typename T> Operand<T> & Operand<T>::operator=(Operand const &operand) {
	if (this == &operand)
		return (*this);
	this->_value = operand._value;
	this->_sValue = std::to_string(this->_value);
	return *this;
}

template class Operand<char>;
template class Operand<short>;
template class Operand<int>;
template class Operand<float>;
template class Operand<double>;