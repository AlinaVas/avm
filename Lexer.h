#ifndef AVM_LEXER_H
#define AVM_LEXER_H

#include <vector>
#include <iostream>

enum eTokenType {push, pop, dump, assert, add, sub, mul, div, mod, print, vmexit};

extern int lineNumber;

struct Token {
	eTokenType	type;
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
	std::vector<Token> _tokens;
};


#endif
