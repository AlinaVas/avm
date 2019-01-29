#include "Lexer.h"
#include "Parser.h"

int main(int ac, char **av) {

	Lexer lr;
	lr.getInput(ac, av);

	Parser pr(lr.getTokens());
	pr.initParsing();
}
