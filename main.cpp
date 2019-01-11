#include "Lexer.h"
#include "Parser.h"

int main(int ac, char **av) {

//	AbstractVMExceptions avm;
	Lexer lr;
//	try {
	lr.getInput(ac, av);
//	} catch (std::exception &e) {
//		std::cout << e.what() << std::endl;
//	}
	Parser pr(lr.getTokens());

	pr.initParsing();
}
