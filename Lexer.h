#ifndef AVM_LEXER_H
#define AVM_LEXER_H

#include <vector>
#include <iostream>
#include <regex>

//enum eTokenType {push, pop, dump, assert, add, sub, mul, div, mod, print, avmexit, comment, empty};

extern int lineNumber;

struct Token {
//	eTokenType	type;
	std::string	type;
	std::string	value;
};

class Lexer {

public:
	Lexer();
	Lexer(const Lexer &);
	~Lexer();

	Lexer &operator=(Lexer const & rhs);

	void readInput(int, char **);
	void readFromFile(char *);
	void readFromStdIn();
	void processInput();


private:
	std::vector<Token> 	_tokens;

	const std::regex	intValPattern;
	const std::regex 	fractValPattern;
	const std::regex 	nonValPattern;

};


#endif
