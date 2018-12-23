#pragma once

#include "IOperand.hpp"
#include <vector>

class Factory {

	typedef IOperand const * (Factory::*funcPtr)(std::string const &);

public:

	Factory();

	IOperand const * createOperand(eOperandType type, std::string const & value) const;

private:

	IOperand const * createInt8(std::string const & value) const;
	IOperand const * createInt16(std::string const & value) const;
	IOperand const * createInt32(std::string const & value) const;
	IOperand const * createFloat(std::string const & value) const;
	IOperand const * createDouble(std::string const & value) const;

	std::vector<funcPtr> _vecOfFunc;
};