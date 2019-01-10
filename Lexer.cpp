#include "Lexer.h"
#include <fstream>

//int lineNumber = 0;

Lexer::Lexer() {
	integerValuePattern = "^(push|assert) (int16|int8|int32)\\([-]?\\d+\\)\\s*(;.*)?$";
	fractionalValuePattern = "^(push|assert) (float|double)\\([-]?\\d+\\.\\d+\\)\\s*(;.*)?$";
	noValuePattern = "^(pop|dump|add|sub|mul|div|mod|print|exit)\\s*(;.*)?$";
	emptyLinePattern = "^ *$";
};

Lexer::Lexer(const Lexer &rhs) {

	*this = rhs;
}

Lexer::~Lexer() = default;

Lexer &
Lexer::operator=(Lexer const &rhs) {

	if (this != &rhs) {
		_tokens = rhs._tokens;
		integerValuePattern = rhs.integerValuePattern;
		fractionalValuePattern = rhs.fractionalValuePattern;
		noValuePattern = rhs.noValuePattern;
		emptyLinePattern = rhs.emptyLinePattern;
	}
	return *this;
}

void
Lexer::getInput(int ac, char **av) {

	try
	{
		(ac == 1) ? readFromStdIn() : readFromFile(av[1]);
	}
	catch (std::exception const &e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
	}

	bool exitCommand = false;
	for (auto &t : _tokens) {

		try
		{
			validateToken(t);
		}
		catch (std::exception const &e)
		{
			std::cerr << "Error: line " << t.lineNumber << ": " << e.what() << std::endl;
		}
		if (t.type == "exit")
			exitCommand = true;
		try
		{
			if (&t == &_tokens.back() && !exitCommand)
				throw Lexer::NoExitCommandExcepton();
		}
		catch (std::exception const &e)
		{

			std::cerr << "Error: " << e.what() << std::endl;
			exit(-1);
		}

		//delete empty tokens???
		std::cout << t.value << std::endl;
	}
}

void
Lexer::readFromFile(char *fileName) {

	std::ifstream	file(fileName);
	if (!file)
		throw std::system_error(errno, std::system_category(), "failed to open " + std::string(fileName));
	std::string line;
	for (int i = 0; std::getline(file, line); i++)
	{
		_tokens.emplace_back();
		_tokens[i].value = line;
		_tokens[i].lineNumber = i + 1;
	}
	file.close();
}

void
Lexer::readFromStdIn() {

	//TODO error handling
	std::string line;
	for (int i = 0; std::getline(std::cin, line) && line != ";;"; i++)
	{
		_tokens.emplace_back();
		_tokens[i].value = line;
		_tokens[i].lineNumber = i + 1;
	}
}

void
Lexer::validateToken(Token &token) {

	/* remove comment if exists */
	if (token.value.find(';') != std::string::npos)
		token.value.erase(token.value.find(';'));

	if (std::regex_match(token.value, integerValuePattern) || std::regex_match(token.value, fractionalValuePattern)) {
		if (token.value[0] == 'p')
			token.type = "push";
		if (token.value[0] == 'a')
			token.type = "assert";
		token.value.erase(0, token.type.size() + 1);
	}
	else if (std::regex_match(token.value, noValuePattern)) {
		token.value.swap(token.type);
	}
	else if (!std::regex_match(token.value, emptyLinePattern)) {
		throw Lexer::LexicalErrorException();
	}

	/* trim token type string */
	token.type.erase(token.type.find_last_not_of(' ') + 1);
}


/************************ EXCEPTIONS ****************************/

Lexer::NoExitCommandExcepton::NoExitCommandExcepton() noexcept = default;

Lexer::NoExitCommandExcepton::NoExitCommandExcepton(NoExitCommandExcepton const &rhs) noexcept {
	*this = rhs;
}

Lexer::NoExitCommandExcepton::~NoExitCommandExcepton() = default;

Lexer::NoExitCommandExcepton
&Lexer::NoExitCommandExcepton::operator=(Lexer::NoExitCommandExcepton const &rhs) noexcept {
	(void)rhs;
	return *this;
}

const char *Lexer::NoExitCommandExcepton::what() const noexcept {
	return ("no exit command");
}

/*****************************************************************/

Lexer::LexicalErrorException::LexicalErrorException() noexcept = default;

Lexer::LexicalErrorException::LexicalErrorException(LexicalErrorException const &rhs) noexcept {
	*this = rhs;
}

Lexer::LexicalErrorException::~LexicalErrorException() = default;

Lexer::LexicalErrorException
&Lexer::LexicalErrorException::operator=(Lexer::LexicalErrorException const &rhs) noexcept {
	(void)rhs;
	return *this;
}

const char *Lexer::LexicalErrorException::what() const noexcept {
	return ("lexical error");
}