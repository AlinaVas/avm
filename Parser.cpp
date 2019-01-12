#include "Parser.h"

Parser::Parser(std::vector<Token> tokens) : _tokens(std::move(tokens)) {

	_commands.push_back(&Parser::push);
	_commands.push_back(&Parser::pop);
	_commands.push_back(&Parser::dump);
	_commands.push_back(&Parser::assrt);
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

void
Parser::pop(size_t &) {
	if (_stack.empty())
		throw Parser::ParsingErrorException("pop from empty stack");
	_stack.pop_front();
}

void
Parser::dump(size_t &) {
	std::string typeName[5] = {"int8", "int16", "int32", "float", "double"};
	if (_stack.empty())
		std::cout << YELLOW << "[=== Stack is empty! ===]" << RESET << std::endl;
	else {
		std::cout << YELLOW << "[=== Content of stack ===]" << RESET << std::endl;
		for (auto &it : _stack) {
			std::cout << YELLOW << typeName[it->getType()] << "(" << it->toString() << ")" << RESET << std::endl;
		}
		std::cout << YELLOW << "[========================]" << RESET << std::endl;
	}
}

void
Parser::assrt(size_t &i) {
	if (_stack.front()->getType() != _tokens[i].operandType)
		throw Parser::ParsingErrorException("assertion failed!");
	if (std::stod(_stack.front()->toString()) != std::stod(_tokens[i].operandValue))
		throw Parser::ParsingErrorException("assertion failed!");
	std::cout << GREEN << "Assertion succeeded!" << RESET << std::endl;
}

void Parser::add(size_t &) {}

void Parser::sub(size_t &) {}

void Parser::mul(size_t &) {}

void Parser::div(size_t &) {}

void Parser::mod(size_t &) {}

void Parser::print(size_t &) {}

void Parser::quit(size_t &) {


}

/************************ EXCEPTIONS ****************************/

Parser::ParsingErrorException::ParsingErrorException(char const *msg) noexcept : _msg(msg);

Parser::ParsingErrorException::ParsingErrorException(ParsingErrorException const &rhs) noexcept {
	*this = rhs;
}

Parser::ParsingErrorException::~ParsingErrorException() = default;

Parser::ParsingErrorException
&Parser::ParsingErrorException::operator=(Parser::ParsingErrorException const &rhs) noexcept {
	(void)rhs;
	return *this;
}

const char *Parser::ParsingErrorException::what() const noexcept {
	return _msg;
}
