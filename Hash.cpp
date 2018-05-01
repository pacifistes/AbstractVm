#include "Hash.hpp"

Hash::Hash() {
	return;
}

Hash::Hash(Hash const &hash) {
	*this = hash;
}

Hash		&Hash::operator=(Hash const &hash) {
	(void)hash;
	return *this;
}

Hash::~Hash() {
	return;
}
