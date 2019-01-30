#include "Lexer.h"
#include <fstream>

//int lineNumber = 0;

Lexer::Lexer() {
	integerValuePattern = R"delim(^(push|assert|pushb) (int16|int8|int32)(\([-]?[[:digit:]]+\))[[:blank:]]*(;.*)?$)delim";
	fractionalValuePattern = R"delim(^(push|assert|pushb) (float|double)(\([-]?[[:digit:]]+\.[[:digit:]]+\))[[:blank:]]*(;.*)?$)delim";
	noValuePattern = R"delim(^(pop|dump|add|sub|mul|div|mod|print|exit|min|max|avg|sort|reverse|popb)[[:blank:]]*(;.*)?$)delim";
	emptyLinePattern = "^ *$";
	_errorsCount = 0;
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
		_errorsCount = rhs._errorsCount;
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
		_errorsCount++;
		std::cerr << MAGENTA << "Error: " << e.what() << RESET << std::endl;
	}

	bool exitCommand = false;
	for (auto &t : _tokens) {

		try
		{
			validateToken(t);
		}
		catch (std::exception const &e)
		{
			_errorsCount++;
			std::cerr << MAGENTA << "Error: line " << t.lineNumber << ": " << e.what() << RESET << std::endl;
		}
		if (t.commandType == EXIT)
			exitCommand = true;
		try
		{
			if (&t == &_tokens.back() && !exitCommand)
				throw Lexer::NoExitCommandException();
		}
		catch (std::exception const &e)
		{
			_errorsCount++;
			std::cerr << MAGENTA << "Error: " << e.what() << RESET << std::endl;
		}
//		std::cout <<t.lineNumber << ": command " << t.commandType << " | opType " << t.operandType << " | opVal " << t.operandValue << std::endl;
	}
	if (_errorsCount)
		exit(-1);
}

void
Lexer::readFromFile(char *fileName) {

	if (!strcmp(fileName, "-help") || !strcmp(fileName, "-h")) {
		provideUsageInfo();
	}

	std::ifstream	file(fileName);
	if (!file)
		throw std::system_error(errno, std::system_category(), "failed to open " + std::string(fileName));

	std::cout << "\033[37;1m" << "======================== file: " << fileName << "\033[0m" << std::endl;
	std::string line;
	for (int i = 0; std::getline(file, line); i++)
	{
		_tokens.emplace_back();
		_tokens[i].operandValue = line;
		_tokens[i].lineNumber = i + 1;
	}
	file.close();
}

void
Lexer::provideUsageInfo() {

	std::ifstream file("UsageInfo.txt");
	if (file.is_open())
		std::cout << file.rdbuf() << std::endl;
	exit(0);
}

void
Lexer::readFromStdIn() {

	std::string line;
	for (int i = 0; std::getline(std::cin, line) && line != ";;"; i++)
	{
		_tokens.emplace_back();
		_tokens[i].operandValue = line;
		_tokens[i].lineNumber = i + 1;
	}
}

void
Lexer::validateToken(Token &token) {

	/* remove comment if exists */
	if (token.operandValue.find(';') != std::string::npos)
		token.operandValue.erase(token.operandValue.find(';'));

	if (std::regex_match(token.operandValue, integerValuePattern) || std::regex_match(token.operandValue, fractionalValuePattern)) {
		if (!token.operandValue.compare(0, 4, "push"))
			token.commandType = PUSH;
		if (!token.operandValue.compare(0, 6, "assert"))
			token.commandType = ASSERT;
		if (!token.operandValue.compare(0, 5, "pushb"))
			token.commandType = PUSHB;
		token.operandValue.erase(0, token.operandValue.find(' ') + 1);
		if (!token.operandValue.compare(0, 4, "int8"))
			token.operandType = Int8;
		if (!token.operandValue.compare(0, 5, "int16"))
			token.operandType = Int16;
		if (!token.operandValue.compare(0, 5, "int32"))
			token.operandType = Int32;
		if (!token.operandValue.compare(0, 5, "float"))
			token.operandType = Float;
		if (!token.operandValue.compare(0, 6, "double"))
			token.operandType = Double;
		token.operandValue.erase(0, token.operandValue.find('(') + 1);
		token.operandValue.erase(token.operandValue.find(')'));
	}
	else if (std::regex_match(token.operandValue, noValuePattern)) {
		if (!token.operandValue.compare(0, 3, "pop"))
			token.commandType = POP;
		if (!token.operandValue.compare(0, 4, "dump"))
			token.commandType = DUMP;
		if (!token.operandValue.compare(0, 3, "add"))
			token.commandType = ADD;
		if (!token.operandValue.compare(0, 3, "sub"))
			token.commandType = SUB;
		if (!token.operandValue.compare(0, 3, "mul"))
			token.commandType = MUL;
		if (!token.operandValue.compare(0, 3, "div"))
			token.commandType = DIV;
		if (!token.operandValue.compare(0, 3, "mod"))
			token.commandType = MOD;
		if (!token.operandValue.compare(0, 5, "print"))
			token.commandType = PRINT;
		if (!token.operandValue.compare(0, 4, "exit"))
			token.commandType = EXIT;
		if (!token.operandValue.compare(0, 3, "min"))
			token.commandType = MIN;
		if (!token.operandValue.compare(0, 3, "max"))
			token.commandType = MAX;
		if (!token.operandValue.compare(0, 4, "sort"))
			token.commandType = SORT;
		if (!token.operandValue.compare(0, 7, "reverse"))
			token.commandType = REVERSE;
		if (!token.operandValue.compare(0, 4, "popb"))
			token.commandType = POPB;
		token.operandValue.clear();
	}
	else if (std::regex_match(token.operandValue, emptyLinePattern))
		token.commandType = EMPTY;
	else
		throw Lexer::LexicalErrorException();
}

std::vector<Token>
Lexer::getTokens() const { return _tokens; }

/************************ EXCEPTIONS ****************************/

Lexer::NoExitCommandException::NoExitCommandException() noexcept = default;

Lexer::NoExitCommandException::NoExitCommandException(NoExitCommandException const &rhs) noexcept {
	*this = rhs;
}

Lexer::NoExitCommandException::~NoExitCommandException() = default;

Lexer::NoExitCommandException
&Lexer::NoExitCommandException::operator=(Lexer::NoExitCommandException const &rhs) noexcept {
	(void)rhs;
	return *this;
}

const char *Lexer::NoExitCommandException::what() const noexcept {
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