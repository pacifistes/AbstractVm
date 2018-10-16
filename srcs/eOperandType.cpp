#include "eOperandType.hpp"

std::ostream & operator<<(std::ostream & os, eOperandType type) {
	switch(type)
	{
		case Int8:
			os << "Int8";
			break;
		case Int16:
			os << "Int16";
			break;
		case Int32:
			os << "Int32";
			break;
		case Int64:
			os << "Int64";
			break;
		case Float:
			os << "Float";
			break;
		case Double:
			os << "Double";
			break;
		default:
			os << "type undifined";
			break;
	}
	return os;
}