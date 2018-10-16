# include "Operand.hpp"

template<typename T> Operand<T>::Operand(eOperandType type, T value) : _type(type), _value(value), _sValue(convertValueToString(value)) {
	return;
}

template<typename T> Operand<T>::~Operand() {
	return;
}

template<typename T> std::string const Operand<T>::convertValueToString(T value) {
	std::ostringstream out;
	if (std::is_same<T, int8_t>::value) {
		out << std::setprecision(std::numeric_limits<int16_t>::max_digits10) << static_cast<int16_t>(value);
	}
	else {
		out << std::setprecision(std::numeric_limits<T>::max_digits10) << value;
	}
	return out.str();
}

template<typename T> int Operand<T>::getPrecision(void) const {
	return static_cast<int>(this->_type);
}

template<typename T> eOperandType Operand<T>::getType(void) const {
	return this->_type;
}


template<typename T> eOperandType Operand<T>::getPriorityType(eOperandType const & firstType, eOperandType const & secondType) const {
	if (firstType < secondType)
		return secondType;
	return firstType;
}
template<typename T> IOperand const * Operand<T>::resultOperand(IOperand const & rhs, std::string const & value) const {
	OperandFactory operandFactory;	
	return operandFactory.createOperand(getPriorityType(this->getType()	, rhs.getType()), value);
}

template<typename T> IOperand const * Operand<T>::operator+(IOperand const & rhs) const {
	return this->resultOperand(rhs, std::to_string(this->_value + std::stod(rhs.toString())));
}

template<typename T> IOperand const * Operand<T>::operator-(IOperand const & rhs) const {
	return this->resultOperand(rhs, std::to_string(this->_value - std::stod(rhs.toString())));
}

template<typename T> IOperand const * Operand<T>::operator*(IOperand const & rhs) const {
	return this->resultOperand(rhs, std::to_string(this->_value * std::stod(rhs.toString())));
}

template<typename T> IOperand const * Operand<T>::operator/(IOperand const & rhs) const {
	if (std::stod(rhs.toString()) == 0) {
		throw ArithmeticException();
	}
	return this->resultOperand(rhs, std::to_string(this->_value / std::stod(rhs.toString())));
}

template<typename T> IOperand const * Operand<T>::operator%(IOperand const & rhs) const {
	if (std::stod(rhs.toString()) == 0) {
		throw ArithmeticException();
	}
	return this->resultOperand(rhs, std::to_string(std::fmod(this->_value, std::stod(rhs.toString()))));
}

template<typename T> std::string const & Operand<T>::toString(void) const {
	return this->_sValue;
}


template<typename T> Operand<T>::Operand() : _type(Int32), _value(0) {
	return;
}

template<typename T> Operand<T>::Operand(Operand const &operand) : _type(operand._type), _value(operand._value), _sValue(operand._sValue) {
	*this = operand;
	return;
}

template<typename T> Operand<T> & Operand<T>::operator=(Operand const &operand) {
	if (this == &operand)
		return (*this);
	return *this;
}

template<typename T> Operand<T>::ArithmeticException::~ArithmeticException(void) throw() {

}

template<typename T> Operand<T>::ArithmeticException::ArithmeticException(void) {

}

template<typename T> const char *Operand<T>::ArithmeticException::what() const throw() {
	return "ArithmeticException: division or modulo by zero not allowed.";
}

template<typename T> Operand<T>::ArithmeticException::ArithmeticException(ArithmeticException const &arithmeticException) {
	*this = arithmeticException;
	return;
}

template<typename T> typename Operand<T>::ArithmeticException & Operand<T>::ArithmeticException::operator=(ArithmeticException const &arithmeticException) {
	(void)arithmeticException;
	return *this;
}

template class Operand<int8_t>;
template class Operand<int16_t>;
template class Operand<int32_t>;
template class Operand<int64_t>;
template class Operand<float>;
template class Operand<double>;