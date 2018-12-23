#pragma once

#include "IOperand.hpp"
#include "Factory.hpp"

template <typename T>
class Operand : public IOperand {

public:

	Operand() = delete;
	Operand(std::string & value, eOperandType type, Factory * ptr);
	Operand(Operand const & rhs);
	~Operand();

	eOperandType		getType() const;
	int					getPrecision() const;
	std::string const 	&toString() const;

	Operand				&operator=(Operand const & rhs);

	IOperand const * operator+(IOperand const & rhs) const;
	IOperand const * operator-(IOperand const & rhs) const;
	IOperand const * operator*(IOperand const & rhs) const;
	IOperand const * operator/(IOperand const & rhs) const;
	IOperand const * operator%(IOperand const & rhs) const;

private:

	std::string		_value;
	eOperandType	_type;
	Factory*		_ptr;
};

#include "Operand.cpp"