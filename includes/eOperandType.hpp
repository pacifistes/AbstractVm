#ifndef EOPERAND_TYPE_HPP
# define EOPERAND_TYPE_HPP

#include <iostream>

enum eOperandType {
	Int8,
	Int16,
	Int32,
	Int64,
	Float,
	Double
};

std::ostream & operator<<(std::ostream & os, eOperandType type);

#endif