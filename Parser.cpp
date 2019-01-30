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
	_commands.push_back(&Parser::min);
	_commands.push_back(&Parser::max);
	_commands.push_back(&Parser::sort);
	_commands.push_back(&Parser::reverse);
}
//TODO push_back, pop_back
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
		try {
			if (_tokens[i].commandType != EMPTY)
				(this->*_commands[_tokens[i].commandType])(i);
		}
		catch (std::exception &e) {
			std::cerr << RED << "Error: line " << i + 1 << ": " << e.what() << RESET << std::endl;
			quit(i);
		}
	}
	std::cout << GREEN << "..... Program exit ....." << RESET << std::endl;
}

void
Parser::displayOperand(IOperand const *it) {
	std::string typeName[5] = {"int8", "int16", "int32", "float", "double"};
	std::string val(it->toString());

	if (it->getType() != Float && it->getType() != Double && val.find('.') != std::string::npos) {
		val.erase(val.begin() + val.find('.'), val.end());
	} else if (it->getType() == Float || it->getType() == Double) {
		val.erase(val.begin() + val.find_last_not_of('0') + 1, val.end());
		(*(val.end() - 1) == '.' ) ? val.append("0") : 0;
	}
	std::cout << YELLOW << typeName[it->getType()] << "(" << val << ")" << RESET << std::endl;
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
	if (_stack.empty())
		std::cout << YELLOW << "... Stack is empty! ...." << RESET << std::endl;
	else {
		std::cout << YELLOW << "... Content of stack ..." << RESET << std::endl;
		for (auto &it : _stack)
			displayOperand(it);
		std::cout << YELLOW << "........................" << RESET << std::endl;
	}
}

void
Parser::assrt(size_t &i) {
    if (_stack.empty())
        throw Parser::ParsingErrorException("assertion on empty stack!");
	if (_stack.front()->getType() != _tokens[i].operandType)
		throw Parser::ParsingErrorException("assertion failed!");
	if (std::stod(_stack.front()->toString()) != std::stod(_tokens[i].operandValue))
		throw Parser::ParsingErrorException("assertion failed!");
	std::cout << GREEN << "Assertion succeeded!" << RESET << std::endl;
}

void Parser::add(size_t &) {
	if (_stack.size() < 2)
		throw ParsingErrorException("not enough operands to perform addition");
	auto op1 = _stack.front();
	_stack.pop_front();
	auto op2 = _stack.front();
	_stack.pop_front();
	_stack.push_front(*op1 + *op2);
	delete op1;
	delete op2;
}

void Parser::sub(size_t &) {
	if (_stack.size() < 2)
		throw ParsingErrorException("not enough operands to perform subtraction");
	auto op1 = _stack.front();
	_stack.pop_front();
	auto op2 = _stack.front();
	_stack.pop_front();
	_stack.push_front(*op2 - *op1);
	delete op1;
	delete op2;
}

void Parser::mul(size_t &) {
	if (_stack.size() < 2)
		throw ParsingErrorException("not enough operands to perform multiplication");
	auto op1 = _stack.front();
	_stack.pop_front();
	auto op2 = _stack.front();
	_stack.pop_front();
	_stack.push_front(*op1 * *op2);
	delete op1;
	delete op2;
}

void Parser::div(size_t &) {
	if (_stack.size() < 2)
		throw ParsingErrorException("not enough operands to perform division");
	auto op1 = _stack.front();
	_stack.pop_front();
	auto op2 = _stack.front();
	_stack.pop_front();
	try {
		_stack.push_front(*op2 / *op1);
		if (_stack.front() == nullptr)
			throw ParsingErrorException("division by 0");
	} catch (std::exception &e) {
		delete op1;
		delete op2;
		throw ParsingErrorException(e.what());
	}
	delete op1;
	delete op2;
}

void Parser::mod(size_t &) {
	if (_stack.size() < 2)
		throw ParsingErrorException("not enough operands to perform division");
	auto op1 = _stack.front();
	_stack.pop_front();
	auto op2 = _stack.front();
	_stack.pop_front();
	try {
		_stack.push_front(*op2 % *op1);
		if (_stack.front() == nullptr)
			throw ParsingErrorException("modulo by 0");
	} catch (std::exception &e) {
		delete op1;
		delete op2;
		throw ParsingErrorException(e.what());
	}
	delete op1;
	delete op2;
}

void Parser::print(size_t &) {
	if (_stack.front()->getType() != Int8)
		throw ParsingErrorException("value at the top is not int8");
	int value = std::stoi(_stack.front()->toString());
	std::cout << BLUE << "ascii symbol: '" << static_cast<char>(value) << "'" << RESET << std::endl;
}

/* among candidates with same value - one with the highest precision is chosen*/
void Parser::min(size_t &) {
	if (_stack.empty())
		throw Parser::ParsingErrorException("stack is empty!");
	auto min = _stack.front();
	for (auto &i : _stack) {
		if (std::stold(i->toString()) < std::stold(min->toString()))
			min = i;
		else if (std::stold(i->toString()) == std::stold(min->toString()) && i->getType() > min->getType())
			min = i;
	}
	std::cout << YELLOW << "minimum: ";
	displayOperand(min);
}

/* among candidates with same value - one with the highest precision is chosen*/
void Parser::max(size_t &) {
	if (_stack.empty())
		throw Parser::ParsingErrorException("stack is empty!");
	auto max = _stack.front();
	for (auto &i : _stack) {
		if (std::stold(i->toString()) > std::stold(max->toString()))
			max = i;
		else if (std::stold(i->toString()) == std::stold(max->toString()) && i->getType() > max->getType())
			max = i;
	}
	std::cout << YELLOW << "maximum: ";
	displayOperand(max);
}

void Parser::sort(size_t &) {
	_stack.sort([](IOperand const *a, IOperand const *b) {
		return std::stold(a->toString()) < std::stold(b->toString()) ||
				(std::stold(a->toString()) == std::stold(b->toString()) && a->getType() < b->getType());
	});
}

void Parser::reverse(size_t &) {
	_stack.reverse();
}

void Parser::quit(size_t &i) {
	for (auto i = _stack.begin(); i != _stack.end(); i++) {
		if (*i)
            delete *i;
	}
	i ? exit(-1) : exit(0);
}

/************************ EXCEPTIONS ****************************/

Parser::ParsingErrorException::ParsingErrorException(char const *msg) noexcept : _msg(msg) {}

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
