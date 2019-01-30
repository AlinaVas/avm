#ifndef AVM_PARSER_H
#define AVM_PARSER_H

#include "Factory.hpp"
#include "Lexer.h"

#define RESET   "\033[0m"
#define GREEN	"\033[32;1m"
#define RED     "\033[31;1m"
#define YELLOW  "\033[33;1m"
#define BLUE    "\033[34;1m"



class Parser {

	typedef void (Parser::*funcPtr)(size_t &);

public:
	Parser() = delete;
	Parser(std::vector<Token>);
	Parser(Parser const &);
	~Parser();
	Parser &operator=(Parser const &);

	void	initParsing();
	void	displayOperand(IOperand const*);
	void 	push(size_t &);
	void	pop(size_t &);
	void	dump(size_t &);
	void	assrt(size_t &);
	void	add(size_t &);
	void	sub(size_t &);
	void	mul(size_t &);
	void	div(size_t &);
	void	mod(size_t &);
	void	print(size_t &);
	void	quit(size_t &);
	void	min(size_t &);
	void	max(size_t &);
	void	sort(size_t &);
	void	reverse(size_t &);

	class ParsingErrorException : public std::exception {

	public:
		ParsingErrorException() noexcept = delete;
		ParsingErrorException(char const *) noexcept;
		ParsingErrorException(ParsingErrorException const &) noexcept;
		virtual ~ParsingErrorException();
		ParsingErrorException &operator=(ParsingErrorException const &) noexcept;
		virtual const char *what() const noexcept;

	private:
		char const  *_msg;
	};


private:
	std::vector<Token>			_tokens;
	std::vector<funcPtr>		_commands;

	std::list<IOperand const*>	_stack;
};


#endif
