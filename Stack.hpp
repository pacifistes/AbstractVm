#ifndef STACK_HPP
# define STACK_HPP

# include <iostream>
# include <stack>
# include "IOperand.hpp"

class Stack : public std::stack<const IOperand*> {

	public:

		Stack();
		~Stack();

		class StackSizeException : public std::exception {
			public:
				StackSizeException(void);				
				virtual ~StackSizeException(void) throw();
				virtual const char *what() const throw();
			private:
				Stack::StackSizeException & operator=(StackSizeException const &stackSizeException);
				StackSizeException(StackSizeException const &stackSizeException);
		};


		class StackAssertException : public std::exception {
			public:
				StackAssertException(bool isAssertInstruction);	
				virtual ~StackAssertException(void) throw();
				virtual const char *what() const throw();
			private:
				Stack::StackAssertException & operator=(StackAssertException const &stackAssertException);
				StackAssertException(void);
				StackAssertException(StackAssertException const &stackAssertException);
				bool _isAssertInstruction;
		};

	private:
		typedef std::stack<const IOperand*>::container_type::iterator	iterator;
		Stack(Stack const &stack);
		Stack		&operator=(Stack const &stack);
		iterator		begin();
		iterator		end();
		IOperand const & at(size_type pos);
		void			assert(IOperand const & iOperand);
		void			pop();
		void			dump();
		void			add();
		void			sub();
		void			mul();
		void			div();
		void			mod();
		void			print();
		void			insert(IOperand const *);
};

//REVOIR LE PRINT 

#endif 
