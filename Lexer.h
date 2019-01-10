#ifndef AVM_LEXER_H
#define AVM_LEXER_H

#include <vector>
#include <iostream>
#include <regex>

//enum eTokenType {push, pop, dump, assert, add, sub, mul, div, mod, print, avmexit, comment, empty};

//extern int lineNumber;

struct Token {
//	eTokenType	type;
	int			lineNumber;
	std::string	type;
	std::string	value;
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

	class NoExitCommandExcepton : public std::exception {

	public:
		NoExitCommandExcepton() noexcept;
		NoExitCommandExcepton(NoExitCommandExcepton const &) noexcept;
		virtual ~NoExitCommandExcepton();
		NoExitCommandExcepton &operator=(NoExitCommandExcepton const &) noexcept;
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
	std::vector<Token> _tokens;

	std::regex integerValuePattern;
	std::regex fractionalValuePattern;
	std::regex noValuePattern;
	std::regex emptyLinePattern;

};


#endif
