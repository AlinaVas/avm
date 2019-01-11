#include "Lexer.h"
#include "Parser.h"
//#include "AbstractVM.hpp"

int main(int ac, char **av) {

//	AbstractVM avm;
	Lexer lr;
//	try {
	lr.getInput(ac, av);
//	} catch (std::exception &e) {
//		std::cout << e.what() << std::endl;
//	}
	Parser pr(lr.getTokens());

}
