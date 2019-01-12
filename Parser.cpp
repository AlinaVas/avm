#include "Parser.h"

Parser::Parser(std::vector<Token> tokens) : _tokens(std::move(tokens)) {

	_commands.push_back(&Parser::push);
	_commands.push_back(&Parser::pop);
	_commands.push_back(&Parser::dump);
	_commands.push_back(&Parser::asrt);
	_commands.push_back(&Parser::add);
	_commands.push_back(&Parser::sub);
	_commands.push_back(&Parser::mul);
	_commands.push_back(&Parser::div);
	_commands.push_back(&Parser::mod);
	_commands.push_back(&Parser::print);
	_commands.push_back(&Parser::quit);
}

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

		if (_tokens[i].commandType == EXIT)
			break;
		if (_tokens[i].commandType != EMPTY)
			(this->*_commands[_tokens[i].commandType])(i);

	}
	std::cout << GREEN << "[=== Program exit ===]" << RESET << std::endl;
}

void
Parser::push(size_t &i) {
	_stack.push_front(Factory().createOperand(_tokens[i].operandType, _tokens[i].operandValue));
}

void Parser::pop(size_t &) {}

void Parser::dump(size_t &) {}

void Parser::asrt(size_t &) {}

void Parser::add(size_t &) {}

void Parser::sub(size_t &) {}

void Parser::mul(size_t &) {}

void Parser::div(size_t &) {}

void Parser::mod(size_t &) {}

void Parser::print(size_t &) {}

void Parser::quit(size_t &) {


}
