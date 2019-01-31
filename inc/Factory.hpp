#ifndef AVM_FACTORY_H
#define AVM_FACTORY_H

#include "IOperand.hpp"
#include <vector>

class Factory {

	typedef IOperand const * (Factory::*funcPtr)(std::string const &) const;

public:

	Factory();

	IOperand const * createOperand(eOperandType type, std::string const & value) const;

	class OverflowErrorException : public std::runtime_error {

	public:
		OverflowErrorException() = delete;
		OverflowErrorException(char const *) noexcept;
		OverflowErrorException(OverflowErrorException const &) noexcept;
		virtual ~OverflowErrorException();
		OverflowErrorException &operator=(OverflowErrorException const &) noexcept;
		virtual const char *what() const noexcept;

	private:
		char const  *_msg;
	};

	class UnderflowErrorException : public std::range_error {

	public:
		UnderflowErrorException() = delete;
		UnderflowErrorException(char const *) noexcept;
		UnderflowErrorException(UnderflowErrorException const &) noexcept;
		virtual ~UnderflowErrorException();
		UnderflowErrorException &operator=(UnderflowErrorException const &) noexcept;
		virtual const char *what() const noexcept;

	private:
		char const  *_msg;
	};

private:

	IOperand const * createInt8(std::string const & value) const;
	IOperand const * createInt16(std::string const & value) const;
	IOperand const * createInt32(std::string const & value) const;
	IOperand const * createFloat(std::string const & value) const;
	IOperand const * createDouble(std::string const & value) const;

	std::vector<funcPtr> _vecOfFunc;
};

#endif