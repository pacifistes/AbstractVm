#ifndef OPERAND_TPP
# define OPERAND_TPP

# include <cmath>
# include <sstream>
# include <iomanip>
# include <type_traits>
# include <stdexcept>
# include "IOperand.hpp"
# include "OperandFactory.hpp"

template<typename T>
class Operand : public IOperand {
	public:
		Operand();
		Operand(eOperandType type, T value);
		virtual ~Operand();
		int getPrecision(void) const;
		eOperandType getType(void) const;
		eOperandType getPriorityType(eOperandType const & firstType, eOperandType const & secondType) const;
		IOperand const * resultOperand(IOperand const & rhs, std::string const & value) const;
		IOperand const * operator+(IOperand const & rhs) const;
		IOperand const * operator-(IOperand const & rhs) const;
		IOperand const * operator*(IOperand const & rhs) const;
		IOperand const * operator/(IOperand const & rhs) const;
		IOperand const * operator%(IOperand const & rhs) const;
		std::string const & toString(void) const;

		class ArithmeticException : public std::exception {
			public:
				virtual ~ArithmeticException(void) throw();
				ArithmeticException(void);
				virtual const char *what() const throw();
				ArithmeticException(ArithmeticException const &arithmeticException);

			private:
				Operand::ArithmeticException & operator=(ArithmeticException const &arithmeticException);
		};

	private:
		Operand(Operand const &operand);
		Operand & operator=(Operand const &operand);
		static std::string const convertValueToString(T value);
		eOperandType const _type;
		T const _value;
		std::string const _sValue;
};

#endif
