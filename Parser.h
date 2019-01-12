#ifndef AVM_PARSER_H
#define AVM_PARSER_H

#include "Factory.hpp"
#include "Lexer.h"

#define RESET   "\033[0m"
#define GREEN	"\033[32m"
#define RED     "\033[31m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"

class Parser {

	typedef void (Parser::*funcPtr)(size_t &);

public:
	Parser() = delete;
	Parser(std::vector<Token>);
	Parser(Parser const &);
	~Parser();
	Parser &operator=(Parser const &);

	void	initParsing();
	void 	push(size_t &);
	void	pop(size_t &);
	void	dump(size_t &);
	void	asrt(size_t &);
	void	add(size_t &);
	void	sub(size_t &);
	void	mul(size_t &);
	void	div(size_t &);
	void	mod(size_t &);
	void	print(size_t &);
	void	quit(size_t &);


private:
	std::vector<Token>			_tokens;
	std::vector<funcPtr>		_commands;

	std::list<IOperand const*>	_stack;
};


#endif
