#ifndef AVM_LEXER_H
#define AVM_LEXER_H

#include <regex>
#include <list>
#include <iostream>
#include "IOperand.hpp"

#define MAGENTA "\033[35;1m"
#define RESET   "\033[0m"

enum eCommandType {PUSH, POP, DUMP, ASSERT, ADD, SUB, MUL, DIV, MOD, PRINT, EXIT, EMPTY};

struct Token {
	int				lineNumber;
	eCommandType	commandType;
	std::string		operandValue;
	eOperandType 	operandType;
};

class Lexer {

public:
	Lexer();
	Lexer(const Lexer &);
	~Lexer();

	Lexer &operator=(Lexer const & rhs);

	void getInput(int, char **);
	void readFromFile(char *);
	void readFromStdIn();
	void validateToken(Token &);

	std::vector<Token> getTokens() const;

	class NoExitCommandException : public std::exception {

	public:
		NoExitCommandException() noexcept;
		NoExitCommandException(NoExitCommandException const &) noexcept;
		virtual ~NoExitCommandException();
		NoExitCommandException &operator=(NoExitCommandException const &) noexcept;
		virtual const char *what() const noexcept ;
	};

	class LexicalErrorException : public std::exception {

	public:
		LexicalErrorException() noexcept;
		LexicalErrorException(LexicalErrorException const &) noexcept;
		virtual ~LexicalErrorException();
		LexicalErrorException &operator=(LexicalErrorException const &) noexcept;
		virtual const char *what() const noexcept;
	};

private:
	std::vector<Token> 	_tokens;

	std::regex integerValuePattern;
	std::regex fractionalValuePattern;
	std::regex noValuePattern;
	std::regex emptyLinePattern;

	int _errorsCount;
};


#endif
