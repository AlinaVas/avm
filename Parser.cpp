#include "Parser.h"

Parser::Parser(std::vector<Token> tokens) : _tokens(std::move(tokens)) {}

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

void
Parser::initParsing() {

	for (size_t i = 0; i < _tokens.size(); i++) {

		if (_tokens[i].commandType == PUSH)
			push(i);
	}
}

void
Parser::push(size_t &i) {
	_stack.push_front(Factory().createOperand(_tokens[i].operandType, _tokens[i].operandValue));
}
