#ifndef AVM_PARSER_H
#define AVM_PARSER_H

#include "Factory.hpp"
#include "Lexer.h"


class Parser {

public:
	Parser() = delete;
	Parser(std::vector<Token>);
	Parser(Parser const &);
	~Parser();
	Parser &operator=(Parser const &);

	void	initParsing();
	void 	push();

private:
	std::vector<Token>		_tokens;
	std::list<IOperand*>	_stack;
};


#endif
