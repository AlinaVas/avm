#include "Lexer.h"
#include <fstream>

int lineNumber = 0;

Lexer::Lexer() = default;

Lexer::Lexer(const Lexer &rhs) {

	*this = rhs;
}

Lexer::~Lexer() = default;

Lexer &
Lexer::operator=(Lexer const &rhs) {

	if (this != &rhs)
		_tokens = rhs._tokens;
	return *this;
}

void
Lexer::readInput(int ac, char **av) {

	try
	{
		(ac == 1) ? readFromStdIn() : readFromFile(av[1]);
	}
	catch (std::exception const &e)
	{
		if (!lineNumber)
			std::cerr << "Error: " << e.what() << std::endl;
		else
			std::cerr << "Error: line " << lineNumber << ": " << e.what() << std::endl;
	}
}

void
Lexer::readFromFile(char *fileName) {

	std::ifstream	file(fileName);
	if (!file)
		throw std::system_error(errno, std::system_category(), "failed to open " + std::string(fileName));
	for (std::string line; std::getline(file, line);)
	{
		_tokens.emplace_back();
		_tokens[lineNumber].value = line;
		lineNumber++;
		std::cout << line << std::endl;
	}
	file.close();
}

void
Lexer::readFromStdIn() {

	//TODO error handling
	for (std::string line; std::getline(std::cin, line) && line != ";;";)
	{
		_tokens.emplace_back();
		_tokens[lineNumber].value = line;
		lineNumber++;
		std::cout << line << std::endl;
	}
}

void
Lexer::processInput() {

	for (auto i = 0; i != _tokens.size(); i++)
	{
		if ((i == _tokens.size() - 1) && (_tokens[i].value != "exit"))
			std::cout << "no exit instruction" << std::endl; //make exception class
		try
		{

		}
		catch ()
		{

		}

	}
}