#ifndef OPERAND_FACTORY_HPP
# define OPERAND_FACTORY_HPP

# include <cstdint>
# include <cfloat>
# include <map>
# include <stdexcept>
# include "IOperand.hpp"
# include "Operand.hpp"

class OperandFactory {
	public:
		OperandFactory();
		virtual ~OperandFactory();
		IOperand const * createOperand(eOperandType type, std::string const & value) const;

		class OverflowException : public std::runtime_error {
			public:
				OverflowException(char const *error);
				virtual ~OverflowException() throw();
				OverflowException(OverflowException const &OverflowException);
			private:
				OverflowException(void);
				OperandFactory::OverflowException & operator=(OverflowException const &OverflowException);
				char const *_error;
		};

	private:
		OperandFactory(OperandFactory const &operandFactory);
		OperandFactory & operator=(OperandFactory const &operandFactory);
		IOperand const * createInt8(std::string const & value) const;
		IOperand const * createInt16(std::string const & value) const;
		IOperand const * createInt32(std::string const & value) const;
		IOperand const * createInt64(std::string const & value) const;
		IOperand const * createFloat(std::string const & value) const;
		IOperand const * createDouble(std::string const & value) const;
		static double convertValue(eOperandType type, std::string const & value);
		static std::map<eOperandType const, double const> initMapMin();
		static std::map<eOperandType const, double const> initMapMax();
		static std::map<eOperandType const, double const> _mapMin;
		static std::map<eOperandType const, double const> _mapMax;

};
 
#endif 