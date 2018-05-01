#ifndef HASH_HPP
# define HASH_HPP


class Hash {

	public:

		~Hash();

	private:
		std::string _regex;
		bool		_isNeedParameter;
		void ()
		void (Human::*arrayOfPointer[3])(std::string const &target) = {&Human::meleeAttack, &Human::rangedAttack, &Human::intimidatingShout};
		Hash();
		Hash(Hash const &src);
		Hash		&operator=(Hash const &rhs);
};

#endif 
