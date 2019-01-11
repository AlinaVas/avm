#include "Parser.h"

Parser::Parser(std::vector<Token> &tokens) : _tokens(tokens) {}

Parser::Parser(Parser const &rhs) {
	*this = rhs;
}

Parser::~Parser() = default;

Parser &
Parser::operator=(Parser const &rhs) {
	if (this != &rhs) {
		_tokens = rhs._tokens;
		_stack = rhs._stack;
	}
	return *this;
}

