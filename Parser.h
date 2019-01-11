#ifndef AVM_PARSER_H
#define AVM_PARSER_H

#include "Lexer.h"
#include "Operand.hpp"

class Parser {

public:
	Parser() = delete;
	Parser(std::vector<Token> &);
	Parser(Parser const &);
	~Parser();
	Parser &operator=(Parser const &);



private:
	std::vector<Token>		_tokens;
	std::vector<IOperand*>	_stack;
};


#endif
