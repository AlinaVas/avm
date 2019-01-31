#include "Lexer.hpp"
#include "Parser.hpp"

int main(int ac, char **av) {

	Lexer lr;
	lr.getInput(ac, av);

	Parser pr(lr.getTokens());
	pr.initParsing();
}
