#ifndef STACK_HPP
# define STACK_HPP

# include <iostream>
# include <stack>
# include <stdexcept>
# include "IOperand.hpp"

class Stack : public std::stack<const IOperand*> {

	public:

		Stack();
		~Stack();
		void			assert(IOperand const & iOperand);
		void			pop();
		void			dump();
		void			vdump();
		void			add();
		void			sub();
		void			mul();
		void			div();
		void			mod();
		void			max();
		void			min();
		void			drop();
		void			print();
		void			exit();
		void			insert(IOperand const *);

		class StackSizeException : public std::exception {
			public:
				StackSizeException(void);				
				virtual ~StackSizeException(void) throw();
				virtual const char *what() const throw();
				StackSizeException(StackSizeException const &stackSizeException);
			private:
				Stack::StackSizeException & operator=(StackSizeException const &stackSizeException);
		};


		class StackAssertException : public std::exception {
			public:
				StackAssertException(bool isAssertInstruction);	
				virtual ~StackAssertException(void) throw();
				virtual const char *what() const throw();
				StackAssertException(StackAssertException const &stackAssertException);
			private:
				Stack::StackAssertException & operator=(StackAssertException const &stackAssertException);
				StackAssertException(void);
				bool _isAssertInstruction;
		};

	private:
		typedef std::stack<const IOperand*>::container_type::reverse_iterator	iterator;
		Stack(Stack const &stack);
		Stack		&operator=(Stack const &stack);
		iterator		begin();
		iterator		end();
		IOperand const & at(size_type pos);
};

#endif 
