#ifndef OPERAND_TPP
# define OPERAND_TPP

# include <cmath>
# include "IOperand.hpp"
# include "OperandFactory.hpp"

template<typename T>
class Operand : public IOperand {
	public:
		Operand();
		Operand(eOperandType type, T value);
		Operand(Operand const &operand);
		virtual ~Operand();
		int getPrecision(void) const;
		eOperandType getType(void) const;
		eOperandType getPriorityType(eOperandType const & firstType, eOperandType const & secondType) const;
		IOperand const * operator+(IOperand const & rhs) const;
		IOperand const * operator-(IOperand const & rhs) const;
		IOperand const * operator*(IOperand const & rhs) const;
		IOperand const * operator/(IOperand const & rhs) const;
		IOperand const * operator%(IOperand const & rhs) const;
		std::string const & toString(void) const;

		class ArithmeticException : public std::exception {
			public:
				virtual ~ArithmeticException(void) throw() {
					return;
				}

				ArithmeticException(void) {
					return;
				}
				virtual const char *what() const throw() {
					return "division or modulo by zero not allowed.";
				}

			private:
				ArithmeticException(ArithmeticException const &arithmeticException) {
					*this = arithmeticException;
					return;
				}

				Operand::ArithmeticException & operator=(ArithmeticException const &arithmeticException) {
					(void)arithmeticException;
					return *this;
				}
		};

	private:
		Operand & operator=(Operand const &operand);
		eOperandType _type;
		T _value;
		std::string _sValue;
};

#endif
